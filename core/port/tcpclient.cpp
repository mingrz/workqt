//By realfan   2015.1
#include "tcpclient.h"
#include "csvpoc.h"
#include <QThread>
#include <QTcpSocket>
#ifdef QT_DEBUG
#include <QDebug>
#include <QDateTime>
#endif
#ifndef WIN32
#define DATA_FILE
#endif

CTcpClient::CTcpClient(const QString strComName)
               : m_strComName(strComName),
                 m_iLen(-1), m_bOpen(false),
				 m_deviceData( 2*1024*1024 ),
                 m_bEchoRegExp(false), m_bEchoFlag(false)
{
	m_bStop=false;

    m_pThread = new QThread(this);
    m_pCom = new QTcpSocket(this);
    m_pCom->moveToThread(m_pThread);
    this->moveToThread(m_pThread);
    m_pThread->start();
    connect(m_pCom, &QTcpSocket::readyRead, this, &CTcpClient::slotDataReady, Qt::DirectConnection);
	connect(m_pCom, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    connect(this, &CTcpClient::sigSetCOM, this, &CTcpClient::slotSetCOM);
    connect(this, &CTcpClient::sigClose, this, &CTcpClient::slotClose);
    connect(this, &CTcpClient::sigClear, this, &CTcpClient::slotClear);
    connect(this, &CTcpClient::sigWrite, this, &CTcpClient::slotWrite);
}
CTcpClient::~CTcpClient()
{
	m_deviceData.Clear();

#ifdef QT_DEBUG
    qDebug() << "~CTcpClient:" << QThread::currentThreadId() <<"\n";
#endif
    close();
    m_pThread->quit();
    m_pThread->wait();
    delete m_pCom; m_pCom = 0;
    delete m_pThread; m_pThread = 0;
}
bool CTcpClient::isOpen() const
{
    return m_bOpen;
}
bool CTcpClient::setCOM(const QString strCOM /*=""*/,
                          const int iPort /*=9600*/)
{
    m_lockSetCOM.lock();
	m_nPort=iPort;
    emit sigSetCOM(strCOM,iPort);
    bool bWait = m_waitSetCOM.wait(&m_lockSetCOM, iPort);
    m_lockSetCOM.unlock();
    return bWait ? m_bOpen : false;
}
qint64 CTcpClient::write(const QByteArray & byteArray)
{
    return write(byteArray.data(), byteArray.size());
}

qint64 CTcpClient::write(const char * data, qint64 maxSize/* = -1*/)
{
    if(!m_bOpen) return -1;
    m_lockWrite.lock();
    emit sigWrite(data, maxSize);
    bool bWait = m_waitWrite.wait(&m_lockWrite, 5000);
    m_lockWrite.unlock();
    QMutexLocker lk(&m_lockWriteLen);
    qint64 iRet = bWait ? m_iLen : 0;
    return iRet;
}
void CTcpClient::close()
{
    m_lockClose.lock();
    emit sigClose();
    m_waitClose.wait(&m_lockClose, 5000);
    m_lockClose.unlock();
}
void CTcpClient::clear()
{
    m_lockClear.lock();
    emit sigClear();
    m_waitClear.wait(&m_lockClear, 5000);
    m_lockClear.unlock();
}

bool CTcpClient::EchoCommand(const QString & strCmd, const QString & strExpectReply /* ="" */, QString * pstrReply /* =0 */)
{
    QMutexLocker lk(&m_lockEcho);
    m_bEchoRegExp = false;
    m_strExpectReply = strExpectReply;
    setEchoFlag(true);

    const QByteArray ba = (strCmd + "\n").toLatin1();
    const int iLen = ba.length();
    if(write(ba) < iLen)
    {
        setEchoFlag(false);
        return false;
    }

	return true;
}
//====================================================


void CTcpClient::slotWrite(const char* pch, qint64 maxSize)
{
    //qDebug() << QDateTime::currentDateTime().toString("HH:mm:ss.zzz") << " write begin\n";
    m_lockWriteLen.lock();
    m_iLen = 0;
    if(m_pCom->isOpen())
    {
		m_iLen=m_pCom->write(pch, maxSize);

		m_pCom->waitForBytesWritten();

		//QAbstractSocket::SocketState st=m_pCom->state();
		//m_pCom->flush();
        //m_iLen = (maxSize < 0) ? m_pCom->write(pch) : m_pCom->write(pch, maxSize);
		//m_pUdp->writeDatagram(pch,maxSize,QHostAddress::Broadcast,m_nPort);
    }
    m_lockWriteLen.unlock();
    m_waitWrite.wakeAll();
    //qDebug() << QDateTime::currentDateTime().toString("HH:mm:ss.zzz") << " write OK\n";
}

void CTcpClient::slotSetCOM(const QString strCOM,const int iPort)
{
    m_pCom->close();
    m_bOpen = false;
    if(strCOM.length() > 0)
    {
        m_strComName = strCOM;
    }
    if(m_strComName.length() < 1)
    {
        m_waitSetCOM.wakeAll();
        return;
    }

    if(false == (m_bOpen=m_pCom->isOpen()))
    {
        //if(false == m_pCom->open(QIODevice::ReadWrite))
		m_pCom->connectToHost(strCOM,iPort);
		m_bOpen=m_pCom->waitForConnected(1000);

		//QAbstractSocket::SocketState st=m_pCom->state();
	}

	if( m_bOpen )
		m_bStop=false;

    //slotDataReady();

    m_waitSetCOM.wakeAll();
}
void CTcpClient::slotClose()
{
    //qDebug() << "slotClose:" << QThread::currentThreadId() <<"\n";
    m_pCom->close();
    m_bOpen = false;
    m_waitClose.wakeAll();
}
void CTcpClient::slotClear()
{
    m_pCom->disconnectFromHost();

    m_lockInBuffer.lock();
    m_strInBuffer.clear();
    m_strReply.clear();
    m_lockInBuffer.unlock();
    m_waitClear.wakeAll();
}
void CTcpClient::slotDataReady()
{
    //const static int iDelay = 20;
    QTcpSocket * const pCom = m_pCom;
    //if(getEchoFlag())

    //qDebug()<<m_bOpen<<"\n";

	if(!m_bStop)
    {
        QMutexLocker lk(&m_lockInBuffer);
        //m_strInBuffer.push_back(pCom->readAll());
        //m_strReply = m_strInBuffer;

		QByteArray strContext=pCom->readAll();
        //strContext="$SP,-60,88.2,K,M*C476$SP,-60,92.2,K,M*C476";

#ifdef DATA_FILE
        CCSVProc csvproc;
         QString strFilePath="/sdcard/TrueSpeed/log.txt";
         csvproc.SetFileDir_Dst(strFilePath);
         csvproc.WriteFile(strContext,false,false,false);

         //qDebug() << strContext <<"\n";
#endif

		if( strContext.indexOf("$SP")>=0 ){
			m_strInBuffer+=strContext;
			CLaserParser::dataParser_TrueSpeed(m_deviceData,m_strInBuffer);
		}
    }
    /*else
    {
        emit sigDataReady(pCom->readAll());
    }*/
}

#if 0
bool CTcpClient::EchoCommand(const QString & strCmd, const QRegExp& rx /* ="" */, QString * pstrReply /* =0 */)
{
    m_strReply = "";
    m_bEchoRegExp = true;
    m_rxExpectReply = rx;
    m_lockInBuffer.lock();
    m_strInBuffer.clear();
    m_lockInBuffer.unlock();
    m_bEchoFlag = true;
    if(write((strCmd + "\r\n").toLatin1()) < strCmd.length() + 2)
    {
        return false;
    }

    QMutexLocker lk(&m_lockEcho); //.lock();
    bool bRet = (m_waitEcho.wait(&m_lockEcho, 5000));
    m_bEchoFlag = false;
    m_bEchoRegExp = false;
    if(pstrReply)
    {
        *pstrReply = bRet ? m_strReply : "";
    }

    return bRet;
}
#endif

void CTcpClient::displayError(QAbstractSocket::SocketError)
{
	QString strError=m_pCom->errorString();
	m_pCom->close();
}

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "CRingBuffer.h"
#include "laserparser.h"

#include <QObject>
#include <QWaitCondition>
#include <QMutex>
#include <QRegExp>
#include <QThread>
#include <QTcpSocket>
#include <QUdpSocket>

class CTcpClient : public QObject
{
    Q_OBJECT
public:
    explicit CTcpClient(const QString strComName = "");
    ~CTcpClient();
    bool isOpen() const;
    bool setCOM(const QString strCOM="", const int iPort=9600);
    qint64 write(const QByteArray & byteArray);
    qint64 write(const char * data, qint64 maxSize = -1);
    void close();
    void clear();
    //bool EchoCommand(const QString & strCmd, const QRegExp& rx = QRegExp(""), QString * pstrReply = 0);
    bool EchoCommand(const QString & strCmd, const QString& strExpectReply ="", QString * pstrReply = 0);
    //==================================================
protected:
	int		m_nPort;
    QString m_strComName;
    //========================
    QThread * m_pThread;
    QTcpSocket * m_pCom;
    //=========================
    //write
    QMutex m_lockWrite;
    QWaitCondition m_waitWrite;
    QMutex m_lockWriteLen;
    qint64 m_iLen;
    //openCom
    QMutex m_lockSetCOM;
    QWaitCondition m_waitSetCOM;
    bool m_bOpen;
    //close
    QMutex m_lockClose;
    QWaitCondition m_waitClose;
    //clear
    QMutex m_lockClear;
    QWaitCondition m_waitClear;
    //=========================
    QMutex m_lockInBuffer;
    QByteArray m_strInBuffer;
    QByteArray m_strReply;

    QMutex m_lockExpect;
    QString m_strExpectReply;
    QRegExp m_rxExpectReply;

    QMutex m_lockEcho;
    QWaitCondition m_waitEcho;
    bool m_bEchoRegExp;
private:
    bool m_bEchoFlag;
    mutable QMutex m_lockEchoFlag;
    void setEchoFlag(bool b)
    {
        QMutexLocker lk(&m_lockEchoFlag);
        m_bEchoFlag = b;
    }
    bool getEchoFlag() const
    {
        QMutexLocker lk(&m_lockEchoFlag);
        return m_bEchoFlag;
    }

signals:
    void sigDataReady(QByteArray);
    void sigWrite(const char *, qint64);
    void sigSetCOM(const QString,  const int);
    void sigClose();
    void sigClear();
private slots:
    void slotDataReady();
    void slotWrite(const char * pch, qint64);
    void slotSetCOM(const QString strCOM,const int iPort);
    void slotClose();
    void slotClear();

	void displayError(QAbstractSocket::SocketError); //œ‘ æ¥ÌŒÛ–≈œ¢

public:
	bool			m_bStop;
	CRingBuffer		m_deviceData;
};

#endif // CTcpClient_H

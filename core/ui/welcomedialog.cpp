#include "welcomedialog.h"
#include "csvpoc.h"
#include <QObject>
#include <QBitmap>
#include <QLineEdit>
#include <QSlider>
#include <QCheckBox>
#include <QTextCodec>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>

#include "ui-util.h"
#include "mainwindow.h"

int CWelcomeDialog::m_nID=-1;

CWelcomeDialog::CWelcomeDialog( QMainWindow *parent /* = 0 */ )
{
	m_bInitFlag=true;
    m_bFirstStart=true;
	m_parent=parent;
	setupUi(parent);

	/*tableWidget->horizontalHeader()->setVisible(true);
	tableWidget->verticalHeader()->setVisible(false);

	checkBoxInterfence->setChecked(true);
	checkBoxTurnType->setChecked(true);

	pushButtonPause->setEnabled(false);
	pushButtonStop->setEnabled(false);
    pushButtonQuit->setEnabled(false);

	connect(checkBoxInterfence,SIGNAL(clicked(bool)),this,SLOT(onCarTypeClick(bool)));
	connect(checkBoxTurnType,SIGNAL(clicked(bool)),this,SLOT(onTurnTypeClick(bool)));
	connect(pushButtonStart,SIGNAL(clicked()),this,SLOT(onStart()));
	connect(pushButtonStop,SIGNAL(clicked()),this,SLOT(onStop()));
	connect(pushButtonPause,SIGNAL(clicked()),this,SLOT(onPause()));*/
    //connect(pushButtonQuit,SIGNAL(clicked()),this,SLOT(onQuit()));
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

CWelcomeDialog::~CWelcomeDialog()
{
	m_parent = NULL;
}

void CWelcomeDialog::initWidgets(QMainWindow *parent)
{
	QRect rectCentral = parent->centralWidget()->geometry();
    //QSize sizeCentral = parent->centralWidget()->size();
	
	if( m_centralRect != rectCentral )
	{
		if( m_bInitFlag )
		{
			m_bInitFlag = false;
		}
		else
		{
			m_centralRect=rectCentral;

			float nXScale,nYScale;
			rectCentral=frame->frameGeometry();
            nXScale = (float)qAbs(rectCentral.width()-m_centralRect.width())/(float)rectCentral.width();
            nYScale = (float)qAbs(rectCentral.height()-m_centralRect.height())/(float)rectCentral.height();

			((MainWindow*)m_parent)->setWindowScale(nXScale,nYScale);

			QObjectList frameList = frame->children();
	
			CUIUtil::reInitWidgetsLayout(frameList,nXScale,nYScale);

			frame->resize(m_centralRect.width(),m_centralRect.height());
		}

        labelStation->setText(QApplication::applicationName());
	}
}

void CWelcomeDialog::onStart()
{
    /*if( m_bFirstStart ){
        WriteHeader();
        m_bFirstStart=false;
    }

    if( comboBoxInterfence->isEnabled() )
		m_param.m_nInterference=comboBoxInterfence->currentText().toInt();
	else
		m_param.m_nInterference=0;

	if ( comboBoxTurnType->isEnabled() )
		m_param.m_strTurnType=comboBoxTurnType->currentText(); 
	else
		m_param.m_strTurnType="直行";

	m_param.m_nFixedDis=lineEditFixedPoint->text().toInt();
	m_param.m_nDataRangSt=lineEditDataRangSt->text().toInt();
	m_param.m_nDataRangEd=lineEditDataRangEd->text().toInt();
	m_param.m_strCarType=comboBoxCarType->currentText();
	m_param.m_strTurnType=comboBoxTurnType->currentText();

	pushButtonPause->setEnabled(true);
	pushButtonStop->setEnabled(true);
    pushButtonStart->setEnabled(false);
    //pushButtonQuit->setEnabled(true);

	CLaserParser::setParam(m_param);

    QString strConn=lineEditConn->text();
	int nInd=strConn.indexOf(":");
	m_tcpClient.setCOM(strConn.mid(0,nInd),strConn.mid(nInd+1,strConn.length()-nInd-1).toInt());
	//m_tcpClient.setCOM("127.0.0.1",6666);
	//m_tcpClient.EchoCommand("aaa");

	m_timer.start();

    m_nID++;*/
}

void CWelcomeDialog::onStop()
{
    /*pushButtonQuit->setEnabled(true);
    pushButtonStart->setEnabled(true);
    pushButtonStop->setEnabled(false);

    WriteContext();

    m_tcpClient.m_bStop=true;
    m_tcpClient.m_deviceData.Clear();
    m_vecDeviceData.clear();*/
}

void CWelcomeDialog::onPause()
{
   /* pushButtonQuit->setEnabled(true);
    pushButtonStart->setEnabled(true);
    pushButtonPause->setEnabled(false);

    m_tcpClient.m_bStop=true;
    m_tcpClient.m_deviceData.Clear();
    m_vecDeviceData.clear();*/
}

void CWelcomeDialog::WriteHeader()
{
     QTextCodec *tc;
	 QString strFilePath;
#ifdef WIN32
	 tc=QTextCodec::codecForLocale();
	 strFilePath += QApplication::applicationDirPath()+"/";
	 strFilePath += QApplication::applicationName();
	 strFilePath += ".csv";
#else
	 tc=QTextCodec::codecForName("GB2312");
	 strFilePath="/sdcard/TrueSpeed/";
	 QDate date=QDateTime::currentDateTime().date();

	 strFilePath+=date.toString("yyyy-MM-dd");
	 //strFilePath+="_"+lineEditPointID->text();
	 strFilePath+=".csv";
#endif

     CCSVProc csvproc;
     csvproc.SetFileDir_Dst(strFilePath);

     int iRangS,iRangE,iFixed;
     QByteArray strHeader;
     strHeader=tc->toUnicode("交叉编号,车辆编号,车辆类型,转弯情况,干扰情况").toLocal8Bit();

     //iFixed=lineEditFixedPoint->text().toInt();
     //iRangS=lineEditDataRangSt->text().toInt();
     //iRangE=lineEditDataRangEd->text().toInt();
     for ( int i=iRangS-iFixed;i<=iRangE-iFixed;i++ )
     {
         strHeader+=",";
         strHeader+=QString::number(i);
     }

     csvproc.WriteHeader(strHeader);
}

void CWelcomeDialog::WriteContext()
{
	QString strFilePath;
#ifdef WIN32
	strFilePath += QApplication::applicationDirPath()+"/";
	strFilePath += QApplication::applicationName();
	strFilePath += ".csv";
#else
    strFilePath="/sdcard/TrueSpeed/";
    QDate date=QDateTime::currentDateTime().date();

    strFilePath+=date.toString("yyyy-MM-dd");
    //strFilePath+="_"+lineEditPointID->text();
    strFilePath+=".csv";
#endif

    CCSVProc csvproc;
    csvproc.SetFileDir_Dst(strFilePath);

    int iID=-1;
    QByteArray strContex;

    //for ( int i=0;i<m_listDevicedata.size();i++ )
    //{
        QByteArray strValue;
        //QVector<tagTrueSpeedData> &vecDevicedata=m_listDevicedata[i];

        for(int j=0;j<m_vecDeviceData.size();j++)
        {
            tagTrueSpeedData &devicedata=m_vecDeviceData[j];

            if( strlen(devicedata.m_strDateTime) > 0  ){
                iID=devicedata.m_nID;
                strValue+=QString::number((int)devicedata.m_dSpeed);
            }

                strValue+=",";
        }

        //if( iID!=-1 ) // you diu shi shu ju
        {
           /* strContex=lineEditPointID->text().toLocal8Bit()+",";
            strContex+=QString::number(iID).toLocal8Bit()+",";
            strContex+=comboBoxCarType->currentText().toLocal8Bit()+",";
            if( checkBoxTurnType->isChecked() )
                strContex+=comboBoxTurnType->currentText().toLocal8Bit()+",";
            else
                strContex+=" ,";

            if( checkBoxInterfence->isChecked() )
                strContex+=comboBoxInterfence->currentText().toLocal8Bit()+",";
            else
                strContex+=" ,";

            strContex+=strValue;

            csvproc.WriteFile(strContex);*/
        }
    //}
}

//int oldID=-1;
QList<tagTrueSpeedData> listDeviceData;
void CWelcomeDialog::onTimerOut()
{
    int dis=0,iInd=0;
    tagTrueSpeedData devicedata;
    m_tcpClient.m_deviceData.PreRead1((char*)&devicedata,sizeof(tagTrueSpeedData));

    if( strlen(devicedata.m_strDateTime) > 0  )
    {
        devicedata.m_nID=m_nID;

        m_vecDeviceData.resize(m_param.m_nDataRangEd-m_param.m_nDataRangSt+1);

        dis=devicedata.m_dDis+0.5;
        iInd=dis-m_param.m_nDataRangSt;
        if( iInd>=0 && iInd<m_vecDeviceData.size() ){
            m_vecDeviceData[iInd]=devicedata;
            Interpolation(m_vecDeviceData,iInd);
        }


        //if( listDeviceData.size()>=tableWidget->rowCount() )
        //    listDeviceData.pop_back();

        listDeviceData.push_front(devicedata);

        //InsertTableValue(tableWidget,listDeviceData);
    }
}
//void CWelcomeDialog::onTimerOut()
//{
//    int dis=0,iInd=0;
//    tagTrueSpeedData devicedata;
//    m_tcpClient.m_deviceData.PreRead1((char*)&devicedata,sizeof(tagTrueSpeedData));

//    if( strlen(devicedata.m_strDateTime) > 0  )
//    {
//        devicedata.m_nID=m_nID;

//        if( oldID!=devicedata.m_nID ){
//            QVector<tagTrueSpeedData> vecDevicedata;
//            vecDevicedata.resize(m_param.m_nDataRangEd-m_param.m_nDataRangSt+1);
//            m_listDevicedata.push_back(vecDevicedata);
//            oldID=devicedata.m_nID;
//        }

//        dis=devicedata.m_dDis+0.5;
//        iInd=dis-m_param.m_nDataRangSt;
//        QVector<tagTrueSpeedData> &vecDevicedata=m_listDevicedata.back();
//        if( iInd>=0 && iInd<vecDevicedata.size() ){
//            vecDevicedata[iInd]=devicedata;
//            Interpolation(vecDevicedata,iInd);
//        }


//        if( listDeviceData.size()>=tableWidget->rowCount() )
//            listDeviceData.pop_back();

//        listDeviceData.push_front(devicedata);

//        InsertTableValue(tableWidget,listDeviceData);
//    }
//}

void CWelcomeDialog::onCarTypeClick(bool checked)
{
	//comboBoxInterfence->setEnabled(checked);
}

void CWelcomeDialog::onTurnTypeClick(bool checked)
{
	//comboBoxTurnType->setEnabled(checked);
}

/*
void CWelcomeDialog::InsertTableValue(QTableWidget* tableWidget,QList<tagTrueSpeedData> &devicedata)
{
    int nRowCount;
	nRowCount=tableWidget->rowCount();

	if( nRowCount<devicedata.size() ){
		tableWidget->insertRow(0);
	}

	for ( int i=0;i<devicedata.size();i++ )
	{
		tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(devicedata[i].m_nID)));
		tableWidget->setItem(i,1,new QTableWidgetItem(devicedata[i].m_strDateTime));
		tableWidget->setItem(i,2,new QTableWidgetItem(comboBoxCarType->currentText()));
		if( checkBoxTurnType->isChecked() )
			tableWidget->setItem(i,3,new QTableWidgetItem(comboBoxTurnType->currentText()));
		if( checkBoxInterfence->isChecked() )
			tableWidget->setItem(i,4,new QTableWidgetItem(comboBoxInterfence->currentText()));
		tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(devicedata[i].m_dSpeed)));
		tableWidget->setItem(i,6,new QTableWidgetItem(QString::number((int)(devicedata[i].m_dDis+0.5))));
		//tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(devicedata[devicedata.size()-i-1])));
	}
}*/

void CWelcomeDialog::Interpolation(QVector<tagTrueSpeedData> &vecDevicedata,int nInd)
{
    if( nInd==0 )
        return;

    //qDebug() <<"nInd"<< nInd <<"\n";
    int i,iValInd=-1;
    for( i=nInd-1;i>0;i-- )
    {
        //if(strlen(vecDevicedata[i].m_strDateTime)>0)
        //    qDebug() <<i<<vecDevicedata[i].m_strDateTime<<","<<vecDevicedata[i].m_dDis<<","<<strlen(vecDevicedata[i].m_strDateTime) <<"\n";

         if( strlen(vecDevicedata[i].m_strDateTime) > 0  ){
            iValInd=i;
            break;
         }
    }

    if( iValInd > -1 && (nInd-iValInd)>1 ){
        //qDebug() <<"iValInd"<< iValInd <<"\n";
        int nOff=(vecDevicedata[nInd].m_dSpeed-vecDevicedata[iValInd].m_dSpeed)/(nInd-iValInd);
        for( i=iValInd+1;i<nInd;i++ ){
            vecDevicedata[i].m_dSpeed=vecDevicedata[iValInd].m_dSpeed+(i-iValInd)*nOff;
            memcpy(vecDevicedata[i].m_strDateTime,vecDevicedata[iValInd].m_strDateTime,strlen(vecDevicedata[iValInd].m_strDateTime));
        }
    }
}

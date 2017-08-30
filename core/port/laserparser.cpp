#include "laserparser.h"
#include <QFile>
#include <QDateTime>
//#include <SerialPortError>

#define PORT_TIMEOUT	50
#define ORDER_SUCCESS	"OK"
#define ORDER_END		"\r\n"

#ifdef FILE_MODE
QFile  g_file("D:/LaserDeviceData.txt");
#endif

tagParam CLaserParser::m_Param=tagParam();

CLaserParser::CLaserParser( )
{
	
}

CLaserParser::~CLaserParser( )
{

}

void CLaserParser::dataParser_Laser(CRingBuffer& ringbuffer,QByteArray &strValue)
{
	char    cF='A',cS='B',cEnd='\n';
	qint32 nIndF=0,nIndS=0,nIndEndF=0,nIndEndS=0;

	//static tagDeviceData olddevicedata;

	if (strValue.length()>0){
		tagDeviceData devicedata,olddevicedata;
		devicedata.strDateTime[DATETIME_LENGTH-1]=0;

		while( nIndF>=0 && nIndEndF>=0 && nIndS>=0 && nIndEndS>=0 ){
			if( (nIndF=strValue.indexOf(cF,nIndF)) >=0 && (nIndEndF=strValue.indexOf(cEnd,nIndF)) >=0 &&
				(nIndS=strValue.indexOf(cS,nIndEndF)) >=0 && (nIndEndS=strValue.indexOf(cEnd,nIndS)) >=0)
			{
				if( strValue.indexOf(',',nIndS+2) >=0 )
				{
					devicedata.sADis=strValue.mid(nIndF+2,strValue.indexOf(',',nIndF+2)-nIndF-2).toInt();
					devicedata.sBDis=strValue.mid(nIndS+2,strValue.indexOf(',',nIndS+2)-nIndS-2).toInt();

					QString strT=strValue.mid(nIndF,nIndEndS-nIndF);

					memcpy(devicedata.strDateTime,
						(char*)QDateTime::currentDateTime().toString("yyyyMMddhh:mm:ss").toLocal8Bit().data(),
						DATETIME_LENGTH-1);

					if( olddevicedata.sADis<0||olddevicedata.sBDis<0 )
					{
						olddevicedata=devicedata;
						ringbuffer.Write((char*)&devicedata,sizeof(tagDeviceData));
					}

					if( abs(devicedata.sADis-olddevicedata.sADis)<=30 && 
						abs(devicedata.sBDis-olddevicedata.sBDis)<=30 ){
					}else{
						ringbuffer.Write((char*)&devicedata,sizeof(tagDeviceData));
						olddevicedata=devicedata;
					}

					nIndF=nIndEndS+1;nIndEndF=nIndF;
					nIndS=nIndF;nIndEndS=nIndF;
				}
				else
					break;
			}
		}

		strValue=strValue.right(strValue.length()-strValue.lastIndexOf(cF));
	}
}

void CLaserParser::dataParser_TrueSpeed(CRingBuffer& ringbuffer,QByteArray &strValue)
{
    //char cEnd='\n';
	QString strA="$SP";
    qint32 nIndF=0,nIndEndF=0;

	if (strValue.length()>0){
        tagTrueSpeedData devicedata;
		devicedata.m_strDateTime[DATETIME_LENGTH-1]=0;

		while( (nIndF=strValue.indexOf(strA,nIndF)) >=0 /*&& (nIndEndF=strValue.indexOf(cEnd,nIndF)) >=0*/){
			nIndF=strValue.indexOf(',',nIndF)+1;
            devicedata.m_dSpeed=abs(strValue.mid(nIndF,strValue.indexOf(',',nIndF)-nIndF).toFloat());

			nIndF=strValue.indexOf(',',nIndF)+1;
			devicedata.m_dDis=strValue.mid(nIndF,strValue.indexOf(',',nIndF)-nIndF).toFloat();

			nIndEndF=nIndF;

			//if(devicedata.m_dDis>=m_Param.m_nDataRangSt && devicedata.m_dDis<=m_Param.m_nDataRangEd)
			{
				//devicedata.m_dDis=m_Param.m_nFixedDis-devicedata.m_dDis;

				memcpy(devicedata.m_strDateTime,
                    (char*)QDateTime::currentDateTime().toString("hh:mm:ss dd-MM-yyyy").toLocal8Bit().data(),
					DATETIME_LENGTH-1);

				memcpy(devicedata.m_strCarType,m_Param.m_strCarType.data(),m_Param.m_strCarType.length());
				memcpy(devicedata.m_strTurnType,m_Param.m_strTurnType.data(),m_Param.m_strTurnType.length());

				ringbuffer.Write((char*)&devicedata,sizeof(tagTrueSpeedData));
			}

			nIndF=nIndEndF+1;
		}

		strValue=strValue.right(strValue.length()-nIndEndF);
	}
}

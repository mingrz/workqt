#ifndef DATA_CABLE_H
#define DATA_CABLE_H

#include "CRingBuffer.h"
#include <QString>
#include <QDateTime>
//#define FILE_MODE

struct tagParam 
{
	int m_nDataRangSt;
	int m_nDataRangEd;
	int m_nFixedDis;
	int m_nInterference;
	int m_nDataQuality;
	QString m_strCarType;
	QString m_strTurnType;
};

#define DATETIME_LENGTH 24
#define TYPE_LENGTH		8

struct tagTrueSpeedData 
{
	int   m_nID;
	float m_dDis;
	float m_dSpeed;
	char  m_strDateTime[DATETIME_LENGTH];
	char m_strCarType[TYPE_LENGTH];
	char m_strTurnType[TYPE_LENGTH];

	tagTrueSpeedData(){
		memset(this,0,sizeof(tagTrueSpeedData));
	}
};

struct tagDeviceData{
	qint16 sADis;
	qint16 sBDis;
	char strDateTime[DATETIME_LENGTH];

	tagDeviceData(){
		sADis=-1,sBDis=-1;
	}
};


class CLaserParser
{
public:
	CLaserParser( );
	~CLaserParser();
	void static setParam(tagParam &pm){m_Param=pm;}
	void static dataParser_Laser(CRingBuffer& ringbuffer,QByteArray &strValue);
	void static dataParser_TrueSpeed(CRingBuffer& ringbuffer,QByteArray &strValue);
private:
	static tagParam m_Param;
};

#endif // DATA_CABLE_H
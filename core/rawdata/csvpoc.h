#ifndef _CSV_PROC_H_
#define _CSV_PROC_H_

#include <QThread>
#include <QDomDocument> 
#include <QDomElement> 
#include <QDomAttr> 
#include <QDir>
#include <QVector>
#include <QByteArray>

typedef struct tagFieldFlag
{
	bool bFlag;
	tagFieldFlag(){ bFlag=false; }
}FieldFlag;

struct tagRawData{
	unsigned int		 unID;
    QVector<QString>		 arrRow;

	tagRawData()
	{
		unID = 0;
		arrRow.clear();
	}
};

typedef QVector<tagRawData>		ArrValues;

class CCSVProc //: public QThread
{
public:
	CCSVProc( );
	~CCSVProc( );
	
	void LoadRoadData( );
    bool PareseData(QByteArray &strData,QVector<QString> &arrRow,QString strSpan );

	void SetFieldFlag( int nIndex );
	void SetFieldNum( int size );
	int  GetFieldNum(){ return m_arrFieldFlag.size();}

    void SetFileDir_Src(QString &strFileDir){ m_strFileDir = strFileDir; }
    void SetFileDir_Dst(QString &strFilePath){ m_strSaveFile = strFilePath; }

	void WriteHeader(QByteArray &DataBuf);
    void WriteFile(QByteArray &DataBuf, bool bFlag=false,bool bMidFileFlag=false,bool bRetrun=true);
private:
	QString				m_strSpan;
    QVector<FieldFlag>	m_arrFieldFlag;

    QString				m_strFileDir;
    QString				m_strSaveFile;

public:
	ArrValues			m_arrValues;
};

#endif

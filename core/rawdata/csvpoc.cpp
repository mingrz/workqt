#include "csvpoc.h"
#include "ASSERT.h"
#include <QMessageBox>
#include <QTextStream>

CCSVProc::CCSVProc()
{
}

CCSVProc::~CCSVProc()
{
	
}

void CCSVProc::LoadRoadData(  )
{
    QString strDir = m_strFileDir;
	QFile file( strDir );

	if(!file.open(QFile::ReadOnly | QFile::Text))
		return;

	m_arrValues.clear();
	
	int nLineNum=0;
	while ( !file.atEnd() ){
		tagRawData rawdata;
		QByteArray line = file.readLine();

		if((nLineNum++)>0){
			/*if( nLineNum == 11 )
				int ab=0;*/

			if(PareseData(line,rawdata.arrRow,QString(",")))
				m_arrValues.push_back(rawdata);
		}
	}

	file.close();


}

bool CCSVProc::PareseData(QByteArray &strData,QVector<QString> &arrRow,QString strSpan)
{
	int nIndex=0;
	int pos = 0, newPos = 0;
    QString strq=strData.data();
    QString sp1="<LineString>",sp2="</LineString>";
	QByteArray str;

	//strData="<LineString><coordinates>113.000574,28.066330,0.0 112.992000,28.063820,0.0</coordinates></LineString>";
    if( (newPos = strData.indexOf(sp1,pos)) >=0 )
	{
		strq=strData.mid(pos,newPos-pos).data();

		pos=newPos;
        newPos=strData.indexOf(sp2,pos)+sp2.length();
		str=strData.mid(pos,newPos-pos);
		str.replace(",",";");

		pos=newPos;
		strq+=str.data();
		strq+=strData.mid(newPos,strData.length()-newPos);
	}

	pos=0;
    str=strq.toLocal8Bit();

	while( ( newPos = str.indexOf(strSpan, pos ) ) >= 0 ){
		if( nIndex<m_arrFieldFlag.size() ){
			if( m_arrFieldFlag[nIndex].bFlag ){
				arrRow.push_back(str.mid(pos, newPos-pos).data());
			}

			pos = newPos + 1;
			nIndex++;
		}
		else
			break;
	}

	if( nIndex == m_arrFieldFlag.size() )
		return true;
	else if( pos < str.length() && m_arrFieldFlag[nIndex].bFlag ){
		arrRow.push_back(str.mid(pos, str.length()-pos).data());
		nIndex++;
	}

	if( nIndex !=m_arrFieldFlag.size() )
		return false;

	return true;
}

void CCSVProc::SetFieldNum( int size )
{
	if( size > 0 )
		m_arrFieldFlag.resize(size);
}

void CCSVProc::SetFieldFlag( int nIndex )
{
	m_arrFieldFlag[nIndex].bFlag=true;
}

void CCSVProc::WriteFile(QByteArray &DataBuf, bool bFlag,bool bMidFileFlag,bool bRetrun)
{
	QString strDir; 

    if( bMidFileFlag )
	{
        int nInd = m_strFileDir.lastIndexOf("/")+1;
        strDir= QString(m_strSaveFile)+QString(m_strFileDir.mid(nInd,m_strFileDir.length()-nInd));
	}
	else
        strDir = m_strSaveFile;

    QFile file( strDir );

	if(!file.open(QFile::WriteOnly|QFile::Append| QFile::Text))
		return;

    if( bFlag )
    {
        file.resize(0);
    }

#ifdef WIN32
    file.write(DataBuf);
    file.write("\r");
#else
    QTextStream in(&file);
    in.setCodec("GB2312"); //请注意这行
    in<<(DataBuf);
    if( bRetrun )
        in<<("\r");
    in.flush();
#endif

	file.close();
}

void CCSVProc::WriteHeader(QByteArray &DataBuf)
{
    if(QFile::exists(m_strSaveFile))
        WriteFile(DataBuf);
    else
        WriteFile(DataBuf,true);
}

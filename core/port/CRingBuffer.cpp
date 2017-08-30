#include "CRingBuffer.h"
#include <math.h>
#include <QFile>
CRingBuffer::CRingBuffer( unsigned long ulMaxSize )
{
	m_pData	= NULL;

	if( ulMaxSize > 0 )
	{
		/*	扩展2的N次冥 */
		if( ulMaxSize & (ulMaxSize-1) )
		{
			int iTemp = (int)log((long double)ulMaxSize);
			ulMaxSize = 1 << (iTemp+1);
		}

		m_pData = (char*)malloc( ulMaxSize );
		memset(m_pData,0,ulMaxSize);
		m_ulMaxSize		= ulMaxSize;
	}

	m_ulWritePos	= 0;
	m_ulReadPos		= 0;
}

CRingBuffer::~CRingBuffer()
{
	if( m_pData )
		free( m_pData );
}

void CRingBuffer::Clear(){
	m_ulWritePos		= 0;
	m_ulReadPos		= 0;
}

void CRingBuffer::ReSize( unsigned long iMaxSize ){
	if( iMaxSize == m_ulMaxSize )
		return;

	if( iMaxSize > 0 )
	{
		if( iMaxSize & (iMaxSize-1) )
		{
			int iTemp = (int)log((long double)iMaxSize);
			iMaxSize = 1 << (iTemp+1);
		}

		m_pData = (char*)realloc( m_pData, iMaxSize );
		m_ulMaxSize	= iMaxSize;
	}

	m_ulWritePos	= 0;
	m_ulReadPos		= 0;
}

unsigned long CRingBuffer::Write( char* pData, unsigned long ulSize,char flag )
{
	unsigned long ulMinSize = qMin( ulSize, m_ulMaxSize - m_ulWritePos + m_ulReadPos );
	if(ulMinSize < ulSize )
	{
		return 0;
	}
	int i=0;
	if( m_ulWritePos==0 && flag > 0 ){
		for ( ;i<ulSize;i++ ){
			if( *(pData+i) == flag )
				break;
		}

		ulMinSize -=i;
	}

#ifdef FILE_MODE
QFile  file("D:/LaserDeviceData.txt");
if( file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append) )
{
	file.write(pData);
	file.close();
}
#endif

	/* first put the data starting from fifo->in to buffer end */
	unsigned long temp = qMax(ulMinSize, m_ulMaxSize - (m_ulWritePos & (m_ulMaxSize - 1)));
	memcpy( m_pData + (m_ulWritePos & (m_ulMaxSize - 1)), pData+i, ulMinSize);

	/* then put the rest (if any) at the beginning of the buffer */
	//memcpy( m_pData, pData+temp, ulMinSize - temp);

	m_ulWritePos += ulMinSize;
	return ulMinSize;
}

unsigned long CRingBuffer::Read( char*& pBuf,int nSize)
{
	unsigned long ulSize = PreRead(pBuf,nSize);
	Skip(ulSize);
	return ulSize;
}

unsigned long CRingBuffer::PreRead(char*& pBuf,char flag,int nSize)
{
	unsigned long ulSize = m_ulWritePos - m_ulReadPos;
	if( ulSize > 0 ){
		if( nSize<-1 )
			return 0;
		else if( nSize<=ulSize )
			ulSize=nSize;

		pBuf = (char*)malloc(ulSize+1);
		if(NULL == pBuf)
		{
			return 0;
		}
		memset(pBuf,0,ulSize+1);
		/* first get the data from fifo->out until the end of the buffer */
		unsigned long ulToEnd = qMin(ulSize, m_ulMaxSize - (m_ulReadPos & (m_ulMaxSize - 1)));

		int n=0,i=ulToEnd;
		for( ;i>=0;i--,n++ ){
			if( *(m_pData+i)==flag )
				break;
		}

		ulToEnd-=n;
		memcpy(pBuf, m_pData + (m_ulReadPos & (m_ulMaxSize - 1)), ulToEnd);

		memmove(m_pData,m_pData+ulToEnd,m_ulMaxSize-ulToEnd);
		m_ulWritePos-=ulToEnd;
		m_ulReadPos=0;

		/* then get the rest (if any) from the beginning of the buffer */
		//memcpy(pBuf+ulToEnd, m_pData, ulSize-ulToEnd);
	}else
		pBuf = NULL;
	return ulSize;
}

unsigned long CRingBuffer::PreRead1(char* pBuf,int nSize)
{
	unsigned long ulSize = m_ulWritePos - m_ulReadPos;
	if( ulSize > 0 ){
		if( nSize<-1 )
			return 0;
		else if( nSize<=ulSize )
			ulSize=nSize;

		/* first get the data from fifo->out until the end of the buffer */
		unsigned long ulToEnd = qMin(ulSize, m_ulMaxSize - (m_ulReadPos & (m_ulMaxSize - 1)));
		memcpy(pBuf, m_pData + (m_ulReadPos & (m_ulMaxSize - 1)), ulToEnd);

		memmove(m_pData,m_pData+ulToEnd,m_ulMaxSize-ulToEnd);
		m_ulWritePos-=ulToEnd;
		m_ulReadPos=0;
		/* then get the rest (if any) from the beginning of the buffer */
		//memcpy(pBuf+ulToEnd, m_pData, ulSize-ulToEnd);

		//Skip(ulSize);
	}

	return ulSize;
}

void CRingBuffer::Skip( unsigned long ulSize)
{
	if(m_ulReadPos+ulSize <= m_ulWritePos)
	{
		m_ulReadPos += ulSize;
	}
};

unsigned long CRingBuffer::GetBufSize()
{
	return m_ulMaxSize;
};

unsigned long CRingBuffer::GetReadSize()
{
	return m_ulWritePos-m_ulReadPos;
};

void CRingBuffer::ReleaseBuffer( char* pBuf )
{
	if( pBuf )
		free(pBuf);
}

CGPSBuffer::CGPSBuffer( int iMaxSize ): CRingBuffer(iMaxSize) {
}

CGPSBuffer::~CGPSBuffer(){
}

QString CGPSBuffer::ReadGPS( ){
	QString	strGPS	= "";
	int iStart = -1, iEnd = -1;
	char	cStart	= '$';
	char	cEnd		= '\n';

	unsigned long	ulRet	= 0;
	char*	pPreRead	= NULL;
	unsigned long ulSize = PreRead(pPreRead);
	if( ulSize > 0 ){
		char* pTemp = pPreRead;
		for( int i = 0; i < ulSize; i ++, pTemp ++ ){
			if( iStart < 0 && *pTemp == cStart )
				iStart = i;

			if( iStart >= 0 && i > iStart && 
				(*pTemp == cEnd || *pTemp == cStart )){
					iEnd = i;
					break;
			}
		}

		if( iStart >= 0 && iEnd > 0 && iEnd > iStart ){
			pPreRead[iEnd]	= 0;
			strGPS	=  ( pPreRead + iStart );
			Skip(iEnd);
		}
	}

	ReleaseBuffer(pPreRead);

	return strGPS;
}

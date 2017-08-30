#ifndef _CRINGBUFFER_H_
#define _CRINGBUFFER_H_

#include <QString>

class CRingBuffer
{
public:
	CRingBuffer( unsigned long iMaxSize );
	virtual ~CRingBuffer();

	void Clear();

	void ReSize( unsigned long iMaxSize );

	unsigned long Write( char* pData, unsigned long lSize, char flag=0 );

	unsigned long Read( char*& pBuf,int nSize=-1);

	unsigned long PreRead(char*& pBuf,char flag=0,int nSize=-1);
	unsigned long PreRead1(char* pBuf,int nSize=-1);

	void Skip( unsigned long lSize);

	unsigned long GetBufSize();

	unsigned long GetReadSize();

	void ReleaseBuffer( char* pBuf );

private:
	char*			m_pData;				
	unsigned long	m_ulMaxSize;		

	unsigned long	m_ulReadPos;	
	unsigned long 	m_ulWritePos;	
};

//	GPS BUFFER - 重载读的操作
class CGPSBuffer	: public CRingBuffer
{
public:
	CGPSBuffer( int iMaxSize );
	~CGPSBuffer();

	QString ReadGPS( );
};
#endif /* _CRINGBUFFER_H_ */

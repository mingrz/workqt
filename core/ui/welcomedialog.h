#ifndef WELCOME_H
#define WELCOME_H

#include "ui_welcomedialog.h"
#include "tcpclient.h"

#include <QTimer>

/*#include <vector>
#include <list>
using namespace std;*/

typedef QMap<int,tagTrueSpeedData> MapTrueSpeedData;
typedef QMap<int,tagTrueSpeedData>::Iterator ItrTrueSpeedData;

class CWelcomeDialog: public QObject,public Ui_welcomedialog
{
	Q_OBJECT
public:
	CWelcomeDialog( QMainWindow *parent = 0 );
	~CWelcomeDialog();

	void initWidgets(QMainWindow *parent);

private:
	//void InsertTableValue(QTableWidget* tableWidget,QList<tagTrueSpeedData> &devicedata);
    void WriteHeader();
    void WriteContext();
    void Interpolation(QVector<tagTrueSpeedData> &vecDevicedata,int nInd);

public slots:
	void onStart();
	void onStop();
	void onPause();
	void onTimerOut();
	void onCarTypeClick(bool checked);
	void onTurnTypeClick(bool checked);

private:
	bool		 m_bInitFlag;
    bool         m_bFirstStart;
	QRect		 m_centralRect;
	QMainWindow *m_parent;
	static int	 m_nID;
	tagParam	 m_param;
	CTcpClient	 m_tcpClient;
		
	QTimer			m_timer;
    QList< QVector<tagTrueSpeedData> > m_listDevicedata;
    QVector<tagTrueSpeedData>          m_vecDeviceData;
public:
	
};
#endif // WELCOME_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "welcomedialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void setWindowScale(float &nXScale,float &nYScale){
		m_nXScale=nXScale;m_nYScale=nYScale;
	}
private:
	void initMainWindow();
	void loadStyleSheet(const QString &sheetName);
	void writeProperty();
	void readProperty();

	void showEvent(QShowEvent *);
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);
	void closeEvent(QCloseEvent *event);

private slots:
	void onTimerOut();
	
public:
    CWelcomeDialog *dialogWelcome;

	float			m_nXScale;
	float			m_nYScale;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include <QFile>
#include <QDesktopWidget>
#include <QApplication>
#include <QDomDocument>
#include <QDomElement>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent)
{
	initMainWindow();
    loadStyleSheet("coffee");
    //readProperty();

	//QMetaObject::Connection ab  = connect(dialogAdjust.axWidget, SIGNAL(Click()), this, SLOT(dialogAdjust.onClick()));

	//connect((QObject*)dialogWelcome->webView->page()->mainFrame(),SIGNAL(loadFinished(bool)),dialogWelcome,SLOT(onLoadFinished(bool)));
}

MainWindow::~MainWindow()
{
	/*if( dialogWelcome!=NULL )
		delete dialogWelcome;*/
}

void MainWindow::initMainWindow()
{
    dialogWelcome =  new CWelcomeDialog(this);

    //readProperty();

    setWindowTitle("TrueSpeed");
	setWindowIcon( QIcon("./pic/Nanosense.jpg"));
	//setWindowFlags(Qt::WindowCloseButtonHint);
	//showFullScreen();
	showMaximized();
}

void MainWindow::loadStyleSheet(const QString &sheetName)
{
	QFile file("./qss/" + sheetName.toLower() + ".qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = QString::fromLatin1(file.readAll());

	qApp->setStyleSheet(styleSheet);
}

void MainWindow::showEvent(QShowEvent *)
{
	
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    dialogWelcome->initWidgets(this);
}

void MainWindow::paintEvent(QPaintEvent *)
{
}

void MainWindow::closeEvent(QCloseEvent *)
{
    /*while(!m_dataMan.isFinished() && m_dataMan.isRunning())
	{
		m_dataMan.stop();

		//m_dataMan.msleep(5);
    }*/

    writeProperty();
}

void MainWindow::onTimerOut(){
    dialogWelcome->onTimerOut();
}

void MainWindow::readProperty()
{
	QString strFilePath;
	strFilePath += QApplication::applicationDirPath()+"/";
	strFilePath += QApplication::applicationName();
    strFilePath += ".xml";

	QFile file(strFilePath); 

	if(file.open(QFile::ReadOnly | QFile::Text))
	{
		QString errStr; 
		int errLine, errCol; 
		QDomDocument doc;
		if(doc.setContent(&file, false, &errStr, &errLine, &errCol)) 
		{
			QDomElement root = doc.documentElement(); 

			//dialogConnect.readProperty(&root);
			//dialogAdjust.readProperty(&root);
			//dialogView.readProperty(&root);

			file.close();
		}
	}
	else
	{
		//dialogConnect.setDefaultProperty();
	}
}

void MainWindow::writeProperty()
{
	QString strFilePath;
	strFilePath += QApplication::applicationDirPath()+"/";
	strFilePath += QApplication::applicationName();
	strFilePath += ".xml";

	QDomDocument doc;

	QDomElement root = doc.createElement("property");
	doc.appendChild(root);

	//dialogConnect.writeProperty(&doc,&root);
	//dialogAdjust.writeProperty(&doc,&root);
	//dialogView.readProperty(&root);

	QFile file( strFilePath );
	if(file.open(QFile::WriteOnly | QFile::Text|QFile::Truncate ))
	{
		QTextStream out(&file);

		out.setCodec("UTF-8");
		doc.save(out,4,QDomNode::EncodingFromTextStream);

		file.close();
	}
}

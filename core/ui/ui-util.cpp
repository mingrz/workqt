#include "ui-util.h"
#include <QLabel>
#include <QGroupBox>
#include <QFrame>
#include <QLineEdit>
#include <QSlider>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QTreeWidget>
#include <QRadioButton>
#include <QTextCodec>
#include <QFileDialog>
#ifdef _WIN32_
#include <QWebView>
#endif
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QHeaderView>

QRect CUIUtil::m_rectTablewidget;

void CUIUtil::reInitWidgetsLayout(QObjectList &objectList,float &nXScale,float &nYScale)
{
	int nSpace,nSpSize;
    //float fWidth,fHeight;
	QString strText,str;

	QRect rect;
	QObjectList nextObList;

	for(int i=0;i<objectList.length();i++)
	{	
		QObject* o = objectList.at(i);
		QString st = o->objectName();

		if ( o->inherits("QLabel") ){
			QLabel* b = qobject_cast<QLabel*>(o);
			nextObList = b->children();

			rect = b->geometry();
            //int nn=b->size().width();
            //int nb=nn*(1+nXScale);
			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);

			/*QObject* parent = b->parent();
			if( parent->inherits("QGroupBox") )
			{
				QGroupBox* gb = qobject_cast<QGroupBox*>(parent);

				if( gb->objectName() == "groupBoxBatteryStatus" || gb->objectName() == "groupBoxMemStatus" )
					b->move(b->geometry().x(),b->geometry().y()*(1+nYScale));
				else
					b->move(b->geometry().x()*(1+nXScale),b->geometry().y()*(1+nYScale));
			}*/
		}
		else if ( o->inherits("QLineEdit") ){
			QLineEdit* b = qobject_cast<QLineEdit*>(o);
			nextObList = b->children();

			rect = b->geometry();
			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);
		}
		else if ( o->inherits("QSlider") ){
			QSlider* b = qobject_cast<QSlider*>(o);
			nextObList = b->children();

			rect = b->geometry();
			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);
		}
		else if ( o->inherits("QTreeWidget") ){
			QTreeWidget* b = qobject_cast<QTreeWidget*>(o);
			nextObList = b->children();

			rect = b->geometry();
			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);
		}
		else if ( o->inherits("QRadioButton") ){
			QRadioButton* b = qobject_cast<QRadioButton*>(o);
			nextObList = b->children();

			rect = b->geometry();
			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);
		}
		else if ( o->inherits("QTextEdit") ){
			QTextEdit* b = qobject_cast<QTextEdit*>(o);
			nextObList = b->children();

			rect = b->geometry();
			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);
        }
#ifdef _WIN32_
		else if ( o->inherits("QWebView") ){
			QWebView* b = qobject_cast<QWebView*>(o);
			nextObList = b->children();

			rect = b->geometry();
			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);
		}
#endif
		else if (o->inherits("QGroupBox")) {
			QGroupBox* b = qobject_cast<QGroupBox*>(o);
			nextObList = b->children();

			//if( b->objectName() == "groupBoxMain" )
			//{
			//	rect = b->geometry();
			//}

			//fWidth=b->size().width()*(1+nXScale)+0.5;
			//nSpace=b->size().height()*(1+nYScale)+0.5;

			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);

			// label lineedit特殊处理
			if( b->objectName() == "groupBoxLifeRemain" || b->objectName() == "groupBoxMemUsed" )
			{
				initLabelandLineeditLayout(nextObList,nXScale,nYScale);
			}
			else if( nextObList.size() > 0 )
			{
				reInitWidgetsLayout(nextObList,nXScale,nYScale);
			}
		}
		else if (o->inherits("QPushButton")) {
			QPushButton* b = qobject_cast<QPushButton*>(o);
			nextObList = b->children();
			
			rect= b->geometry();

			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);
		}
		else if (o->inherits("QFrame")) {
			QFrame* b = qobject_cast<QFrame*>(o);
			nextObList = b->children();

            QRect rect;
            if( b->objectName() == "tableWidget"){
                if( m_rectTablewidget.width()>0 && m_rectTablewidget.height()>0  )
                    rect=m_rectTablewidget;
                else
                    rect=b->geometry();
            }
            else
                rect=b->geometry();

            b->resize(rect.width()*(1+nXScale)+0.5,rect.height()*(1+nYScale)+0.5);
            b->move(rect.x()*(1+nXScale)+0.5,rect.y()*(1+nYScale)+0.5);

			if( b->objectName() == "tableWidget"){
                m_rectTablewidget=b->geometry();
                reInitTableWidget((QTableWidget*)b);
			}
		}
		else if (o->inherits("QComboBox")) {
			QComboBox* b = qobject_cast<QComboBox*>(o);
			nextObList = b->children();

			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);
		}
		else if (o->inherits("QDateTimeEdit")) {
			QDateTimeEdit* b = qobject_cast<QDateTimeEdit*>(o);
			nextObList = b->children();

			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);
		}
		else if (o->inherits("QCheckBox")) {
			QCheckBox* b = qobject_cast<QCheckBox*>(o);
			nextObList = b->children();

			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);

			QObject* parent = b->parent();
			if( parent->inherits("QGroupBox") )
			{
				QGroupBox* gb = qobject_cast<QGroupBox*>(parent);

				// checkbox特殊处理
				if( gb->objectName() == "groupBoxUnload" || gb->objectName() == "groupBoxTemplate" )
				{
					str = "";
					strText=b->text().trimmed();
					rect = b->geometry();

					QFont font= b->font();
					nSpace=rect.width();

					QFontMetrics fm=b->fontMetrics();
					nSpace = fm.width(strText);
					nSpSize = fm.width(" ");

					nSpace = (rect.width()-nSpace)/(2*nSpSize);

					for ( int i=0; i<nSpace;i++ ){str+=" ";}

					str+=strText;

					for ( int i=0; i<nSpace;i++ ){str+=" ";}

					b->setText(str);
				}
			}
		}
		else{
			if( o->objectName() == "qt_scrollarea_viewport"){
				QWidget* b = qobject_cast<QWidget*>(o);
				rect = b->geometry();
				b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nYScale)+0.5);
				b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);

				nextObList = b->children();

				reInitWidgetsLayout(nextObList,nXScale,nYScale);
			}
		}
	}
}

void CUIUtil::initLabelandLineeditLayout(QObjectList &objectList,float &nXScale,float &nYScale)
{
	int nLabelSize=0,nX=0;
	int nNum=objectList.size();
	for ( int i=0; i<nNum;i++ )
	{
		QObject* o = objectList.at(i);
		if ( nLabelSize== 0 && o->inherits("QLabel") ){
			QLabel* b = qobject_cast<QLabel*>(o);

			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nXScale)+0.5);
			b->move(b->geometry().x()*(1+nXScale)+0.5,b->geometry().y()*(1+nYScale)+0.5);

			QFontMetrics fm=b->fontMetrics();
			nLabelSize = fm.width(b->text());

			nX=b->geometry().x()+nLabelSize + 2;

			i=-1;
		}

		if ( nLabelSize != 0 && o->inherits("QLineEdit") ){
			QLineEdit* b = qobject_cast<QLineEdit*>(o);

			b->resize(b->size().width()*(1+nXScale)+0.5,b->size().height()*(1+nXScale)+0.5);
			b->move(nX,b->geometry().y()*(1+nYScale)+0.5);
		}
	}
}

void CUIUtil::reInitTableWidget(QTableWidget* table)
{
    float nOff=0;
    int tableWidth=table->size().width();
    int tableHeight=table->size().height();

    QHeaderView *header=table->verticalHeader();
    if( header!=NULL /*&& header->isVisible()*/)
        nOff = header->size().width();

    int nColumnWidth,headerHegiht;
    int nColumnNum=table->columnCount();

     tableHeight-=nOff;
     headerHegiht=table->horizontalHeader()->size().height();
     tableHeight=tableHeight-(tableHeight-headerHegiht)%(headerHegiht);

    tableWidth-=nOff;
    QRect rectTable=table->geometry();

    if( tableWidth%nColumnNum>0 )
    {
        tableWidth-=tableWidth%nColumnNum;
    }

    rectTable.setWidth(tableWidth+2);
    rectTable.setHeight(tableHeight+2);
    table->setGeometry(rectTable);

    table->setRowCount((tableHeight-headerHegiht)/(headerHegiht));

    nColumnWidth=tableWidth/nColumnNum;

    for ( int i=0; i<table->columnCount();i++ )
        table->setColumnWidth( i,nColumnWidth);

    for ( int i=0; i<table->rowCount();i++ )
        table->setRowHeight(i,headerHegiht);
}

void CUIUtil::mkPath(QString &strText)
{
	QDir dir;
	dir.mkpath(strText);
}

QString CUIUtil::getPath(QString &strDefaultPath,QString &strFilter,QChar bFlag)
{
	QString fileName;
	QTextCodec *gbk = QTextCodec::codecForLocale();

	if( bFlag==0 )
	{
		fileName = QFileDialog::getExistingDirectory(NULL, gbk->toUnicode("Choose Directory"),strDefaultPath);

		if ( !fileName.isEmpty() ){
			fileName+="/";
		}
	}
	else if(bFlag==1)
	{
		fileName = QFileDialog::getOpenFileName(NULL, gbk->toUnicode("Choose FileName"),strDefaultPath,strFilter);
	}
	else if(bFlag==2)
	{
		fileName = QFileDialog::getSaveFileName(NULL, gbk->toUnicode("Choose FileName"),strDefaultPath,strFilter);
	}

	return fileName;
}

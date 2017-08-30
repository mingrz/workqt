#ifndef UI_UTIL_H
#define UI_UTIL_H

#include <QColor>
#include <QObjectList>
#include <QDomDocument>
#include <QDomElement>
#include <QTableWidget>

class CUIUtil
{
public:
	void static initLabelandLineeditLayout(QObjectList &objectList,float &nXScale,float &nYScale);
	void static reInitWidgetsLayout(QObjectList &objectList,float &nXScale,float &nYScale);

	void static reInitTableWidget(QTableWidget* tableWidget);

	void static mkPath(QString &strText);
	QString static getPath(QString &strDefaultPath,QString &strFilter,QChar bFlag=0);

private:
    static QRect m_rectTablewidget;
};
#endif // UI_UTIL_H

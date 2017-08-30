/********************************************************************************
** Form generated from reading UI file 'welcomedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEDIALOG_H
#define UI_WELCOMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_welcomedialog
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QGroupBox *groupBox;
    QComboBox *comboBoxStation;
    QLabel *label;
    QLabel *labelStation;

    void setupUi(QMainWindow *welcomedialog)
    {
        if (welcomedialog->objectName().isEmpty())
            welcomedialog->setObjectName(QStringLiteral("welcomedialog"));
        welcomedialog->resize(393, 480);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(welcomedialog->sizePolicy().hasHeightForWidth());
        welcomedialog->setSizePolicy(sizePolicy);
        welcomedialog->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(welcomedialog);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setMinimumSize(QSize(900, 460));
        centralwidget->setStyleSheet(QStringLiteral(""));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 390, 480));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(5, 0, 380, 90));
        comboBoxStation = new QComboBox(groupBox);
        comboBoxStation->setObjectName(QStringLiteral("comboBoxStation"));
        comboBoxStation->setGeometry(QRect(300, 50, 71, 30));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(-140, 120, 54, 12));
        labelStation = new QLabel(groupBox);
        labelStation->setObjectName(QStringLiteral("labelStation"));
        labelStation->setGeometry(QRect(10, 30, 271, 41));
        welcomedialog->setCentralWidget(centralwidget);

        retranslateUi(welcomedialog);

        QMetaObject::connectSlotsByName(welcomedialog);
    } // setupUi

    void retranslateUi(QMainWindow *welcomedialog)
    {
        welcomedialog->setWindowTitle(QApplication::translate("welcomedialog", "Nanosense", 0));
        groupBox->setTitle(QApplication::translate("welcomedialog", "\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        comboBoxStation->clear();
        comboBoxStation->insertItems(0, QStringList()
         << QApplication::translate("welcomedialog", "\344\270\234\351\230\263", 0)
         << QApplication::translate("welcomedialog", "\347\243\220\345\256\211", 0)
        );
        label->setText(QApplication::translate("welcomedialog", "TextLabel", 0));
        labelStation->setText(QApplication::translate("welcomedialog", "\347\253\231\347\202\271", 0));
    } // retranslateUi

};

namespace Ui {
    class welcomedialog: public Ui_welcomedialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEDIALOG_H

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //QObject::connect(w.dialogWelcome->pushButtonQuit,SIGNAL(clicked()),&a,SLOT(quit()));

    w.show();

    return a.exec();
}

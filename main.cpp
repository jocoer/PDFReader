#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType <QMap<int,QImage>>("QMap<int,QImage>");
    MainWindow w;
    w.resize(800,  800);
    w.show();
    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QTextCodec>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    /*a06345e013ce4fa7985b39a0c2fcdcd5*/
    w.show();

    return a.exec();
}

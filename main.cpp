#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>



#include "generichelper.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("offlineshop_de");
    a.installTranslator(&translator);

    genericHelper::log(genericHelper::getAppName() +" started.");











    MainWindow w;
    w.show();

    return a.exec();
}

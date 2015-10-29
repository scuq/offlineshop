#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>



#include "generichelper.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLocale::setDefault(QLocale::German);
    QTranslator translator;
    translator.load("offlineshop_de.qm");
    a.installTranslator(&translator);

    genericHelper::log(genericHelper::getAppName() +" started.");











    MainWindow w;
    w.show();

    return a.exec();
}

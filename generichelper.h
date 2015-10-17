#ifndef GENERICHELPER_H
#define GENERICHELPER_H

#define NOMINMAX

#include <QObject>
#include "QString"
#include <QFileInfo>
#include <QDateTime>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QDateTime>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QTextStream>
#include <QRegExp>
#include <QStringList>
#include <windows.h>
#include <QDebug>


class genericHelper : public QObject
{
    Q_OBJECT
public:
    static genericHelper &GetInstance(){
        static genericHelper instance;
        return instance;
    }



     static QString getAppDir();
     static QString getAppName();
     static QStringList getCurrencies();
     static bool setAppDir(QString appdir);
     static QStringList getRecentFiles();
     static bool setRecentFiles(QStringList recentfiles);
     static bool addRecentFiles(QString recentfile, int maxrecent);
     static void log(QString logstring);
     static int getProcessPollInterval();
     static bool setProcessPollInterval(int interval);
     static int getGuiPollInterval();
     static bool setGuiPollInterval(int interval);
     static bool isValidEmailAddress(QString address);

     static QString getLastErrorMsg();

     static QString stdWToQString(const std::wstring &str);





signals:

public slots:

};

#endif // GENERICHELPER_H

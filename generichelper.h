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
#include <QThread>

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
     static void saveGeometry(QString window, QVariant geo);
     static void saveWindowstate(QString window, QVariant state);
     static QVariant getGeometry(QString window);
     static QVariant getWindowstate(QString window);
     static QString getLang();
     static void setLang(QString lang);
     static bool setAppDir(QString appdir);
     static QStringList getRecentFiles();
     static bool setRecentFiles(QStringList recentfiles);
     static bool addRecentFiles(QString recentfile, int maxrecent);
     static void log(QString logstring);
     static QString getTimestamp();
     static QString getToday();
     static QString getTime();
     static QString getPrettyTimestamp();
     static int getProcessPollInterval();
     static bool setProcessPollInterval(int interval);
     static int getGuiPollInterval();
     static bool setGuiPollInterval(int interval);
     static bool isValidEmailAddress(QString address);
     static bool isValidPhoneNumber(QString phone);
     static QString unzipDocxWithAddon7Zip(QString docxfile);
     static QString zipTempDirToDocxWithAddon7Zip(QString tempdir);
     static void replaceVarInDocx(QString tempdir, QHash<QString,QString> replacmentVars);
     static QHash<QString,QString> getDocxReplacmentVariables();
     static void setDocxReplacmentVariables(QHash<QString,QString> replacmentVars);

     static QString getUpdateCheckUrl();

     static bool getCheckUpdate();
     static void setCheckUpdate(bool checkupdate);

     static QString getCompanyName();
     static void setCompanyName(QString companyname);

     static QString getReportTitle();
     static void setReportTitle(QString reporttitle);

     static QString getTemplateFile();
     static void setTemplateFile(QString templatefile);

     static QString getLastErrorMsg();

     static QString stdWToQString(const std::wstring &str);





signals:

public slots:

};

#endif // GENERICHELPER_H


#include "generichelper.h"

QString genericHelper::getAppName(){
    return SETTINGS_PRODUCT;
}

QStringList genericHelper::getCurrencies()
{
    QStringList currencies;

    currencies << "EUR";
    currencies << "USD";
    currencies << "GBP";
    currencies << "CHF";
    currencies << "JPY";
    currencies << "NZD";
    currencies << "AUD";
    currencies << "CNY";

    return currencies;

}

int genericHelper::getProcessPollInterval() {
    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());
    if (settings.childKeys().contains("processPollInterval"))
    {
        return settings.value("processPollInterval", "").toString().toInt();
    }
    return 10;
}

bool genericHelper::setProcessPollInterval(int interval) {

    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());
    settings.setValue("processPollInterval", interval);
    settings.sync();

    return true;
}

int genericHelper::getGuiPollInterval() {
    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());
    if (settings.childKeys().contains("guiPollInterval"))
    {
        return settings.value("guiPollInterval", "").toString().toInt();
    }
    return 10;
}

bool genericHelper::setGuiPollInterval(int interval) {

    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());
    settings.setValue("guiPollInterval", interval);
    settings.sync();

    return true;
}

bool genericHelper::isValidEmailAddress(QString address)
{
    QRegExp regexEmail("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$" );

    if( regexEmail.indexIn( address ) != -1 ) {
        return true;
    } else {
        return false;
    }
}

QString genericHelper::unzipDocxWithAddon7Zip(QString docxfile)
{
    QString addon7z = "";
    QStringList args;

    QString extractedDocxDir = "";

    addon7z = QCoreApplication::applicationFilePath().replace(genericHelper::getAppName()+".exe","") + QDir::separator() +
            "3rdparty-addons" + QDir::separator() +
            "7zip" + QDir::separator() + "7z.exe";


    QFile origDocxfile( docxfile );

    QFileInfo origDocxfileInfo(docxfile);

    QFile addon7zFile( addon7z );

    QDir tempExtractDir(QStandardPaths::standardLocations(QStandardPaths::TempLocation)[0] + QDir::separator() + origDocxfileInfo.baseName() + "_" + genericHelper::getTimestamp());

    extractedDocxDir = QDir::toNativeSeparators(tempExtractDir.path());

    if (tempExtractDir.exists()) {
         qDebug() << "removing dir "+tempExtractDir.path();
        tempExtractDir.removeRecursively();
        qDebug() << "creating dir "+tempExtractDir.path();
        tempExtractDir.mkpath(".");
    } else {
        qDebug() << "creating dir "+tempExtractDir.path();
        tempExtractDir.mkpath(".");
    }

    if( (addon7zFile.exists()) &&  origDocxfile.exists())
    {

        args << "x";
        args << QDir::toNativeSeparators(docxfile);
        args << "-tzip";
        args << "-yo" + extractedDocxDir;

        qDebug() << "7z found.";
        qDebug() << "docx template found.";

        QProcess *process = new QProcess(qApp);


        qDebug() << addon7z << args;
        process->start(addon7z, args);
        process->waitForFinished(20000);


    }

    return extractedDocxDir;
}

void genericHelper::replaceVarInDocx(QString tempdir,  QHash<QString,QString> replacmentVars)
{

    qDebug() << "replaceVarInDocx";
    qDebug() << replacmentVars;
    QFile origDocxfile( tempdir + QDir::separator() + "word" + QDir::separator() + "document.xml" );

    qDebug() << tempdir + QDir::separator() + "word" + QDir::separator() + "document.xml";

    QString orgContent="";

    if (origDocxfile.exists()) {

        if (origDocxfile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&origDocxfile);

            while(!in.atEnd()) {
                orgContent += in.readLine();
            }



              origDocxfile.close();
        }

        orgContent.replace("$TITLE$","New Title");

        QThread::sleep(2);

        if (origDocxfile.open(QIODevice::ReadWrite | QIODevice::Text))
        {

              QTextStream out(&origDocxfile);
              out << orgContent;
              origDocxfile.close();
        }


    }

}

QHash<QString, QString> genericHelper::getDocxReplacmentVariables()
{
      QHash<QString,QString> replacementvars;



      QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());

      QListIterator<QString> itrsettings (settings.childKeys());

      while (itrsettings.hasNext()) {

          QString current = itrsettings.next();

          if (current.contains("docx_rv_")) {
              current.replace("docx_rv_","");
              replacementvars[current]=settings.value(current).toString();
         }
      }



      return replacementvars;

}

void genericHelper::setDocxReplacmentVariables(QHash<QString, QString> replacmentVars)
{

    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());

    QListIterator<QString> itrvars (replacmentVars.keys());

    while (itrvars.hasNext()) {
        QString current = itrvars.next();

        settings.setValue("docx_rv_"+current, replacmentVars[current]);
    }



    settings.sync();



}

QString genericHelper::getCompanyName()
{
    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());

    QString _retstr = "";

    if (settings.value("companyname", "").toString().length() > 1) {
        _retstr = settings.value("companyname", "").toString();

    } else {
        _retstr = SETTINGS_COMPANY;
    }

    return _retstr;
}

void genericHelper::setCompanyName(QString companyname)
{
    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());
    settings.setValue("companyname", companyname);
    settings.sync();
}

QString genericHelper::getReportTitle()
{
    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());

    QString _retstr = "";

    if (settings.value("reporttitle", "").toString().length() > 1) {
        _retstr = settings.value("reporttitle", "").toString();

    } else {
        _retstr = "Example Title";
    }

    return _retstr;
}

void genericHelper::setReportTitle(QString reporttitle)
{
    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());
    settings.setValue("reporttitle", reporttitle);
    settings.sync();
}

QString genericHelper::getTemplateFile()
{
    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());

    QString _retstr = "";

    if (settings.value("templatefile", "").toString().length() > 1) {
        _retstr = settings.value("templatefile", "").toString();

    } else {
        _retstr = QCoreApplication::applicationFilePath().replace(genericHelper::getAppName()+".exe","") + QDir::separator() + "report_template.docx";
    }

    return _retstr;
}

void genericHelper::setTemplateFile(QString templatefile)
{
    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());
    settings.setValue("templatefile", templatefile);
    settings.sync();
}

QString genericHelper::getAppDir(){

    QString _appDir = QDir::homePath() + QDir::separator () + genericHelper::getAppName();

    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());

    if (settings.value("appDir", "").toString().length() > 1) {


        _appDir = settings.value("appDir", "").toString();

    } else {


        QSettings settings(SETTINGS_COMPANY,genericHelper::getAppName());
        settings.setValue("appDir", _appDir);
        settings.sync();
    }



    if (QDir(_appDir).exists() == true) {

    } else {

        QDir().mkdir(_appDir);

    }

    if (QDir(_appDir).exists() == true) {
       return _appDir;
    } else {

        return QDir::tempPath();
    }

}

bool genericHelper::setAppDir(QString appdir) {


    QSettings settings(SETTINGS_COMPANY,genericHelper::getAppName());
    settings.setValue("appDir", appdir);
    settings.sync();

    return true;
}

QStringList genericHelper::getRecentFiles()
{
    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());

    QStringList _recentfilelist;


    if (settings.value("recentfiles", "").toString().length() > 1) {
        if (settings.value("recentfiles", "").toString().count(",") <= 0) {
            _recentfilelist << settings.value("recentfiles", "").toString();
        } else {
          _recentfilelist = settings.value("recentfiles", "").toString().split(",");
        }

    }

    return _recentfilelist;
}

bool genericHelper::setRecentFiles(QStringList recentfiles)
{

    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());
    settings.setValue("recentfiles", recentfiles.join(","));
    settings.sync();
    return true;
}

bool genericHelper::addRecentFiles(QString recentfile, int maxrecent)
{
    QSettings settings(SETTINGS_COMPANY, genericHelper::getAppName());

    QStringList _recentfilelist;

    _recentfilelist = genericHelper::getRecentFiles();


    if (_recentfilelist.length() <= 0) {
        _recentfilelist.append(recentfile);
        setRecentFiles(_recentfilelist);
    }
    if (_recentfilelist.length() >= maxrecent) {
        _recentfilelist[0] = recentfile;
    } else {
       _recentfilelist.append(recentfile);
    }

    return setRecentFiles(_recentfilelist);


}

void genericHelper::log(QString logstring) {
    QFile file(genericHelper::getAppDir() + QDir::separator() + genericHelper::getAppName() + ".log");
    if (!file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text))
    return;

    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss") << ": " << logstring << "\n";
    out.flush();

    file.close();
}

QString genericHelper::getTimestamp()
{
    return QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
}

QString genericHelper::getPrettyTimestamp()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}


QString genericHelper::getLastErrorMsg() {
    LPWSTR bufPtr = NULL;
    DWORD err = GetLastError();
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                   FORMAT_MESSAGE_FROM_SYSTEM |
                   FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, err, 0, (LPWSTR)&bufPtr, 0, NULL);
    const QString result =
        (bufPtr) ? QString::fromUtf16((const ushort*)bufPtr).trimmed() :
                   QString("Unknown Error %1").arg(err);
    LocalFree(bufPtr);
    return result;
}

/*! Convert an std::wstring to a QString */
QString genericHelper::stdWToQString(const std::wstring &str)
{
#ifdef _MSC_VER
    return QString::fromUtf16((const ushort *)str.c_str());
#else
    return QString::fromStdWString(str);
#endif
}




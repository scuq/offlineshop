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




#ifndef OSDB_H
#define OSDB_H


#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QStringList>
#include "generichelper.h"
#include <QSqlRecord>
#include <QRegExp>
#include <QStringList>

class osDb : public QObject
{
    Q_OBJECT
public:
    explicit osDb(QObject *parent = 0);

    bool createAllTables();
    bool createEmptyShoppingCart(int customerid, QString customername, QString prettydate, QString date);
    QHash<QString,QString> getCartInfos(QString carttablename);
    bool updateCartName(QString carttablename, QString cartname);
    bool fillAllExampleData();
    bool fillPricelistExampleData();
    bool fillCustomerExampleData();
    bool addItemToCart(int productid, QString cartname);
    bool open(QString path);
    QStringList getTables(QRegExp rxFilter);

    bool close();
    bool testConn();
    bool isOpen();
    QString getLastError();



private:
    bool createTablePricelist();
    bool createTableCustomer();
    bool createTableCartlist();

    QSqlDatabase db;
    QString lastErrorMsg;




signals:

public slots:

};

#endif // OSDB_H




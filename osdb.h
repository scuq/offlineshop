#ifndef OSDB_H
#define OSDB_H


#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QStringList>
#include "generichelper.h"

class osDb : public QObject
{
    Q_OBJECT
public:
    explicit osDb(QObject *parent = 0);

    bool createAllTables();
    bool createEmptyShoppingCart(int customerid, QString date);
    bool fillAllExampleData();
    bool fillPricelistExampleData();
    bool fillCustomerExampleData();
    bool open(QString path);

    bool close();
    bool testConn();
    bool isOpen();
    QString getLastError();



private:
    bool createTablePricelist();
    bool createTableCustomer();

    QSqlDatabase db;
    QString lastErrorMsg;




signals:

public slots:

};

#endif // OSDB_H




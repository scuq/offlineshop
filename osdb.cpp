#include "osdb.h"

osDb::osDb(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE", genericHelper::getAppName());
    lastErrorMsg = "";
}

bool osDb::createAllTables()
{
    bool ret = false;

    ret = this->createTablePricelist();
    this->createTableCustomer();


    lastErrorMsg = db.lastError().text();

    return ret;
}

bool osDb::fillAllExampleData()
{
    if (this->fillCustomerExampleData() == false) {
        qDebug() << "fillCustomerExampleDataFailed";
    }
    if (this->fillPricelistExampleData() == false) {

        qDebug() << "fillPricelistExampleDataFailed";
    }

    return true;

}

bool osDb::fillPricelistExampleData()
{
    QString table = "pricelist";

    genericHelper::log("fill example data in table: "+table);



    bool ret = false;

    if ( QSqlDatabase::database(genericHelper::getAppName()).isOpen() )
    {
         QSqlQuery query(QSqlDatabase::database(genericHelper::getAppName()));



         ret = query.exec("SELECT COUNT(*) FROM "+table+" LIMIT 1;");

         query.next();

         if (query.value(0).toString().toInt() == 0) {



             query.prepare( "INSERT INTO "+table+" "
                            "('productid', 'article_name', 'price_unit', 'currency') "
                            "VALUES (?, ?, ?, ?) ");

             QVariantList productid;
             QVariantList article_name;
             QVariantList price_unit;
             QVariantList currency;


             productid << "00711150"
                      << "00711152"
                      << "00711057";


             article_name << "Roth Net Polypen-Fangnetz"
                      << "Blue Net Polypen-Fangnetz"
                      << "Yellow Roth Net Polypen-Fangnetz";

             price_unit << "3"
                            << "9"
                            << "78";


             currency << "EUR"
                      << "USD"
                      << "YEN";

             query.addBindValue(productid);
             query.addBindValue(article_name);
             query.addBindValue(price_unit);
             query.addBindValue(currency);

             qDebug() << query.result();

             if (!query.execBatch()) {
                 ret = false;
                 genericHelper::log("db error: "+query.lastError().text());
                 genericHelper::log("db query: "+query.executedQuery());

             } else {
                 ret = true;
             }

          }



    }

    return ret;
}

bool osDb::fillCustomerExampleData()
{



    QString table = "customer";

    genericHelper::log("checking table: "+table);



    bool ret = false;

    if ( QSqlDatabase::database(genericHelper::getAppName()).isOpen() )
    {
         QSqlQuery query(QSqlDatabase::database(genericHelper::getAppName()));



         ret = query.exec("SELECT COUNT(*) FROM "+table+" LIMIT 1;");

         query.next();

         if (query.value(0).toString().toInt() == 0) {



             genericHelper::log("create table "+table+" with default content");

             query.prepare( "INSERT INTO "+table+" "
                            "('customerid', 'customer_name', 'customer_phonenumber', 'customer_email','customer_address','customer_postalcode','customer_country','customer_info','customer_info2','customer_info3') "
                            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?) ");

             QVariantList customerid;
             QVariantList customer_name;
             QVariantList customer_phonenumber;
             QVariantList customer_email;
             QVariantList customer_address;
             QVariantList customer_postalcode;
             QVariantList customer_country;
             QVariantList customer_info;
             QVariantList customer_info2;
             QVariantList customer_info3;


             /**
         ret = query.exec("CREATE TABLE IF NOT EXISTS "+table+" "
                                 "(id INTEGER PRIMARY KEY, "
                            "customerid BIGINT UNIQUE, "
                            "customer_name VARCHAR, "
                            "customer_phonenumber BIGINT, "
                            "customer_email VARCHAR, "
                            "customer_address VARCHAR, "
                            "customer_postalcode INT, "
                            "customer_country VARCHAR(2), "
                            "customer_info VARCHAR, "
                            "customer_info2 VARCHAR, "
                            "customer_info3 VARCHAR "


                                 ")" );
               **/

             customerid << "001"
                      << "002"
                      << "231";


             customer_name << "Maier"
                      << "Müller"
                      << "Smith";

             customer_phonenumber << "0043123456789"
                      << "0043123451789"
                      << "001123456789";

             customer_email << "Maier@maier.at"
                      << "Müller@mueller.at"
                      << "Smith@smith.com";


             customer_address << "Baugrund 1"
                      << "Planstadt 231"
                      << "Village Road 92";

             customer_postalcode << "8371"
                      << "9021"
                      << "90210";

             customer_country << "AT"
                      << "AT"
                      << "US";

             customer_info << "guter kunde"
                      << "schlechter kunde"
                      << "nice customer";

             customer_info2 << "öffentlich"
                      << "private firma"
                      << "university";

             customer_info3 << "hr. x ist y"
                      << "hr y. ist x"
                      << "mr. o is m.";

             query.addBindValue(customerid);
             query.addBindValue(customer_name);
             query.addBindValue(customer_phonenumber);
             query.addBindValue(customer_email);
             query.addBindValue(customer_address);
             query.addBindValue(customer_postalcode);
             query.addBindValue(customer_country);
             query.addBindValue(customer_info);
             query.addBindValue(customer_info2);
             query.addBindValue(customer_info3);



             qDebug() << query.result();

             if (!query.execBatch()) {
                 ret = false;
                 genericHelper::log("db error: "+query.lastError().text());
                 genericHelper::log("db query: "+query.executedQuery());

             } else {
                 ret = true;
             }

          } else {
               qDebug() << "already data there.";
         }



    }

    return ret;
}



bool osDb::open(QString path)
{
    bool createNewDb = false;

    QFile Fout(path);

    if(!Fout.exists()) {
        createNewDb = true;
    }



    db.setDatabaseName(path);





    if (!db.open()) {

        lastErrorMsg = db.lastError().text();

        return false;
    }

    if (createNewDb == true) {
        this->createAllTables();
    }

    lastErrorMsg = db.lastError().text();

    return true; // Database sucessfully opened
}

bool osDb::close()
{
     if (db.open()) {
         //db.cloneDatabase("QSQLITE", genericHelper::getAppName());
         db.close();
     }

     lastErrorMsg = db.lastError().text();

     return true;
}



bool osDb::testConn()
{
    QSqlDatabase db = QSqlDatabase::database(genericHelper::getAppName());
    if (!db.open()) {

        return false;

    }
    return true;
}

bool osDb::isOpen()
{
    if (!db.open()) {

        return false;

    }
    return true;
}

QString osDb::getLastError()
{
    return this->lastErrorMsg;
}

bool osDb::createTablePricelist()
{

    QString table = "pricelist";

    genericHelper::log("checking table: "+table);



    bool ret = false;

    if ( QSqlDatabase::database(genericHelper::getAppName()).isOpen() )
    {
         QSqlQuery query(QSqlDatabase::database(genericHelper::getAppName()));

         ret = query.exec("CREATE TABLE IF NOT EXISTS "+table+" "
                                 "(id INTEGER PRIMARY KEY, "
                            "productid BIGINT UNIQUE, "
                            "article_name VARCHAR NOT NULL, "
                            "price_unit REAL, "
                            "price_package REAL, "
                             "currency VARCHAR(3), "
                            "packing_unit INT, "
                            "min_sell_units INT, "
                            "article_length REAL, "
                            "article_width REAL, "
                            "article_depth REAL, "
                            "article_height REAL, "
                            "article_weight REAL, "                            
                            "delivery_time INT "
                            "article_desc VARCHAR "

                                 ")" );


    }

    return ret;

}

bool osDb::createTableCustomer()
{

    QString table = "customer";

    genericHelper::log("checking table: "+table);



    bool ret = false;

    if ( QSqlDatabase::database(genericHelper::getAppName()).isOpen() )
    {
         QSqlQuery query(QSqlDatabase::database(genericHelper::getAppName()));

         ret = query.exec("CREATE TABLE IF NOT EXISTS "+table+" "
                                 "(id INTEGER PRIMARY KEY, "
                            "customerid BIGINT UNIQUE, "
                            "customer_name VARCHAR, "
                            "customer_phonenumber BIGINT, "
                            "customer_email VARCHAR, "
                            "customer_address VARCHAR, "
                            "customer_postalcode INT, "
                            "customer_country VARCHAR(2), "
                            "customer_info VARCHAR, "
                            "customer_info2 VARCHAR, "
                            "customer_info3 VARCHAR "


                                 ")" );



         ret = query.exec("SELECT COUNT(*) FROM "+table+" LIMIT 1;");

         query.next();

         if (query.value(0).toString().toInt() == 0) {

             genericHelper::log("create table "+table+" with default content");

             query.prepare( "INSERT INTO "+table+" "
                            "('productid', 'article_desc', 'currency', 'price_unit') "
                            "VALUES (?, ?, ?, ?) ");

             QVariantList customerid;
             QVariantList customer_name;
             QVariantList customer_phonenumber;
             QVariantList customer_email;
             QVariantList customer_address;
             QVariantList customer_postalcode;
             QVariantList customer_country;
             QVariantList customer_info;
             QVariantList customer_info2;
             QVariantList customer_info3;



             customerid << "001"
                      << "002"
                      << "231";


             customer_name << "Maier"
                      << "Müller"
                      << "Smith";

             customer_phonenumber << "0043123456789"
                      << "0043123451789"
                      << "001123456789";

             customer_email << "Maier@maier.at"
                      << "Müller@mueller.at"
                      << "Smith@smith.com";


             customer_address << "Baugrund 1"
                      << "Planstadt 231"
                      << "Village Road 92";

             customer_postalcode << "8371"
                      << "9021"
                      << "90210";

             customer_country << "AT"
                      << "AT"
                      << "US";

             customer_info << "guter kunde"
                      << "schlechter kunde"
                      << "nice customer";

             customer_info2 << "öffentlich"
                      << "private firma"
                      << "university";

             customer_info3 << "hr. x ist y"
                      << "hr y. ist x"
                      << "mr. o is m.";

             query.addBindValue(customerid);
             query.addBindValue(customer_name);
             query.addBindValue(customer_phonenumber);
             query.addBindValue(customer_email);
             query.addBindValue(customer_address);
             query.addBindValue(customer_postalcode);
             query.addBindValue(customer_country);
             query.addBindValue(customer_info);
             query.addBindValue(customer_info2);
             query.addBindValue(customer_info3);



             qDebug() << query.result();

             if (!query.execBatch()) {
                 ret = false;
                 genericHelper::log("db error: "+query.lastError().text());
                 genericHelper::log("db query: "+query.executedQuery());

             } else {
                 ret = true;
             }

          }



    }

    return ret;

}

bool osDb::createEmptyShoppingCart(int customerid, QString date)
{
    QString table = "cart_"+QString::number(customerid)+"_"+date;

    genericHelper::log("checking table: "+table);



    bool ret = false;

    if ( QSqlDatabase::database(genericHelper::getAppName()).isOpen() )
    {
         QSqlQuery query(QSqlDatabase::database(genericHelper::getAppName()));

         ret = query.exec("CREATE TABLE IF NOT EXISTS "+table+" "
                                 "(id INTEGER PRIMARY KEY, "
                            "productid BIGINT UNIQUE, "
                            "units INT, "
                            "packages INT, "
                            "customer_want_info BOOL, "
                            "customer_want_training BOOL, "
                            "customer_want_trial BOOL "
                                 ")" );







    }

    return ret;
}

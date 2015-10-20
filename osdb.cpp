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
    this->createTableCartlist();


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

bool osDb::addItemToCart(int productid, QString cartname)
{



    bool ret = false;

    if ( QSqlDatabase::database(genericHelper::getAppName()).isOpen() )
    {

         QSqlQuery query(QSqlDatabase::database(genericHelper::getAppName()));


         QString table_pricelist = "pricelist";
         QString table = cartname;

         query.prepare("SELECT COUNT(*) FROM "+table_pricelist+" WHERE productid="+QString::number(productid)+";");


         if (!query.exec()) {
             ret = false;
             genericHelper::log("db error: "+query.lastError().text());
             genericHelper::log("db query: "+query.executedQuery());

         } else {
             ret = true;
         }

        query.next();



         if (query.value(0).toString().toInt() > 0) {

             QVariantList productids;
             QVariantList article_name;
             QVariantList units;
             QVariantList packages;
             QVariantList price_unit;
             QVariantList price_package;
             QVariantList currency;
             QVariantList delivery_time;

             genericHelper::log("found "+query.value(0).toString()+" product matching productid: "+QString::number(productid));

             query.prepare("SELECT * FROM "+table_pricelist+" WHERE productid="+QString::number(productid)+" LIMIT 1 ;");

             if (!query.exec()) {
                 ret = false;
                 genericHelper::log("db error: "+query.lastError().text());
                 genericHelper::log("db query: "+query.executedQuery());

             } else {
                 ret = true;
             }

             query.next();

             QSqlRecord rec = query.record();



             for (int i=0; i<rec.count(); i++) {
               if (rec.fieldName(i) == "productid") {
                    productids << rec.value(i);
                    continue;
               }
               if (rec.fieldName(i) == "article_name") {
                    article_name << rec.value(i);
                    continue;
               }
               if (rec.fieldName(i) == "price_unit") {
                    price_unit << rec.value(i);
                    continue;
               }
               if (rec.fieldName(i) == "price_package") {
                    price_package << rec.value(i);
                    continue;
               }
               if (rec.fieldName(i) == "currency") {
                    currency << rec.value(i);
                    continue;
               }
               if (rec.fieldName(i) == "delivery_time") {
                    delivery_time << rec.value(i);
                    continue;
               }

             }

             units << 1;
             packages << 0;

             query.finish();
             query.clear();


             query.prepare( "INSERT INTO "+table+" "
                            "('productid', 'article_name', 'units', 'packages', 'price_unit', 'price_package', 'currency', 'delivery_time') "
                            "VALUES (?, ?, ?, ?, ?, ?, ?, ?) ");


             query.addBindValue(productids);
             query.addBindValue(article_name);
             query.addBindValue(units);
             query.addBindValue(packages);
             query.addBindValue(price_unit);
             query.addBindValue(price_package);
             query.addBindValue(currency);
             query.addBindValue(delivery_time);


             if (!query.execBatch()) {
                 ret = false;
                 genericHelper::log("db error: "+query.lastError().text());
                 genericHelper::log("db query: "+query.executedQuery());

             } else {
                 ret = true;
             }


         } else {
             genericHelper::log("no products matching productid: "+QString::number(productid)+" found");
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

QStringList osDb::getTables(QRegExp rxFilter)
{




    QStringList tables;
    QStringList tablesfiltered;

    if ( QSqlDatabase::database(genericHelper::getAppName()).isOpen() )
    {
        tables = QSqlDatabase::database(genericHelper::getAppName()).tables();
    }


    for( int i=0; i<tables.count(); ++i )
    {

        if(QString(tables.at(i)).contains(rxFilter) == true ) {

            tablesfiltered.append(tables.at(i));

        }
    }



    return tablesfiltered;
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

bool osDb::createTableCartlist()
{
    QString table = "cartlist";

    genericHelper::log("checking table: "+table);


    bool ret = false;

    if ( QSqlDatabase::database(genericHelper::getAppName()).isOpen() )
    {
         QSqlQuery query(QSqlDatabase::database(genericHelper::getAppName()));

         ret = query.exec("CREATE TABLE IF NOT EXISTS "+table+" "
                                 "(id INTEGER PRIMARY KEY, "
                            "cartname VARCHAR, "
                            "carttablename VARCHAR, "
                            "customer_name VARCHAR NOT NULL, "
                            "customerid BIGINT, "
                            "pretty_date VARCHAR, "
                            "date VARCHAR "
                                 ")" );



    }

    return ret;

}

bool osDb::createEmptyShoppingCart(int customerid, QString customername, QString prettydate, QString date)
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
                            "article_name VARCHAR NOT NULL, "
                            "units INT, "
                            "packages INT, "
                            "price_unit REAL, "
                            "price_package REAL, "
                            "currency VARCHAR(3), "
                            "delivery_time INT "
                            "customer_want_info BOOL, "
                            "customer_want_training BOOL, "
                            "customer_want_trial BOOL "
                                 ")" );


         if (ret == true) {

             query.prepare( "INSERT INTO cartlist "
                            "('cartname', 'carttablename', 'customer_name', 'customerid', 'pretty_date', 'date') "
                            "VALUES (?, ?, ?, ?, ?, ?);");

             QVariantList cartname;
             QVariantList carttablename;
             QVariantList customer_name;
             QVariantList customerids;
             QVariantList pretty_date;
             QVariantList dates;

             cartname << "";
             carttablename << "cart_"+QString::number(customerid)+"_"+date;
             customer_name << customername;
             customerids << customerid;
             pretty_date << prettydate;
             dates << date;

             query.addBindValue(cartname);
             query.addBindValue(carttablename);
             query.addBindValue(customer_name);
             query.addBindValue(customerids);
             query.addBindValue(pretty_date);
             query.addBindValue(dates);


             if (!query.execBatch()) {
                 ret = false;

                 genericHelper::log("db error: "+query.lastError().text());
                 genericHelper::log("db query: "+query.executedQuery());

                 genericHelper::log("db trying to drop table: "+table);
                 query.exec("DROP TABLE "+table+"");

             } else {

                 ret = true;

             }

         }



    }

    return ret;
}

QHash<QString,QString> osDb::getCartInfos(QString carttablename)
{
    bool ret = false;

    QHash<QString,QString> cartinfos;

    if ( QSqlDatabase::database(genericHelper::getAppName()).isOpen() )
    {
        QSqlQuery query(QSqlDatabase::database(genericHelper::getAppName()));

        query.prepare("SELECT * FROM cartlist WHERE carttablename=\'"+carttablename+"\' LIMIT 1 ;");

        if (!query.exec()) {
            ret = false;
            genericHelper::log("db error: "+query.lastError().text());
            genericHelper::log("db query: "+query.executedQuery());

        } else {
            ret = true;

            query.next();

            QSqlRecord rec = query.record();



            for (int i=0; i<rec.count(); i++) {
              if (rec.fieldName(i) == "cartname") {
                   cartinfos["cartname"] = rec.value(i).toString();
                   continue;
              }
              if (rec.fieldName(i) == "carttablename") {
                   cartinfos["carttablename"] = rec.value(i).toString();
                   continue;
              }
              if (rec.fieldName(i) == "customer_name") {
                   cartinfos["customer_name"] = rec.value(i).toString();
                   continue;
              }
              if (rec.fieldName(i) == "customerid") {
                   cartinfos["customerid"] = rec.value(i).toString();
                   continue;
              }
              if (rec.fieldName(i) == "pretty_date") {
                   cartinfos["pretty_date"] = rec.value(i).toString();
                   continue;
              }
              if (rec.fieldName(i) == "date") {
                   cartinfos["date"] = rec.value(i).toString();
                   continue;
              }

            }

        }

    }
    return cartinfos;
}

bool osDb::updateCartName(QString carttablename, QString cartname)
{
    bool ret = false;

    QHash<QString,QString> cartinfos;

    if ( QSqlDatabase::database(genericHelper::getAppName()).isOpen() )
    {
        QSqlQuery query(QSqlDatabase::database(genericHelper::getAppName()));

        query.prepare("UPDATE cartlist SET cartname=\'"+cartname+"\' WHERE carttablename =\'"+carttablename+"\';");

        if (!query.exec()) {
            ret = false;
            genericHelper::log("db error: "+query.lastError().text());
            genericHelper::log("db query: "+query.executedQuery());

        } else {
            ret = true;
        }
    }

    return ret;

}

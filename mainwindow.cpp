#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //tab_index_pricelist = 0;
    //tab_index_customer = 1;
    //tab_index_cart = 2;

    this->ui->tabWidget->tabBar()->tabButton(0,QTabBar::RightSide)->resize(0, 0);
    this->ui->tabWidget->tabBar()->tabButton(1,QTabBar::RightSide)->resize(0, 0);

    this->ui->tabCarts->setHidden(true);

    this->ui->tabWidget->removeTab(tab_index_cart);

    this->toggleInputEnabled(false);

    osDatabase = new osDb();


    maxRecentFiles = 4;

    defaultStatusTimeout = 5000;

    this->fillRecentFileHistory();

    modelPricelist = new QSqlRelationalTableModel(this,QSqlDatabase::database(genericHelper::getAppName()));

    proxymodelPricelist = new AdvQSortFilterProxyModel(this);

    imgDelegateProductImage = new MyImageDelegate();
    iDelegateProductId = new MyIntDelegate();
    iDelegateArticleLength = new MyIntDelegate();
    iDelegateArticleWidth = new MyIntDelegate();
    iDelegateArticleDepth = new MyIntDelegate();
    iDelegateArticleHeight = new MyIntDelegate();
    iDelegateArticleWeight = new MyIntDelegate();
    iDelegatePackingUnit = new MyIntDelegate();
    iDelegateMinSellUnits = new MyIntDelegate();
    fDelegatePriceUnit = new MyFloatDelegate();
    fDelegatePricePackage = new MyFloatDelegate();
    cbxMyCurrencyComboDelegate = new MyCurrencyComboDelegate();
    emlMyEmailDelegate = new MyEmailLineEditDelegate();


    proxymodelPricelist->setSourceModel(modelPricelist);

    modelCustomer = new QSqlRelationalTableModel(this,QSqlDatabase::database(genericHelper::getAppName()));

    modelCart = new QSqlRelationalTableModel(this,QSqlDatabase::database(genericHelper::getAppName()));

    proxymodelCustomer = new AdvQSortFilterProxyModel(this);

    proxymodelCustomer->setSourceModel(modelCustomer);

    iDelegateCustomerId = new MyIntDelegate();

    open_mailclient = new QAction(tr("Open in &Mail Client"), this);

    new_cart = new QAction(tr("New &Cart"), this);

    show_carts = new QAction(tr("&Show Carts"), this);

    add_to_cart = new QAction(tr("Add to &Cart"), this);

    show_image = new QAction(tr("Show &Image"), this);

    signalMapperEmailAddress = new QSignalMapper(this);

    QObject::connect(open_mailclient, SIGNAL(triggered()), signalMapperEmailAddress, SLOT(map()));

    QObject::connect(signalMapperEmailAddress, SIGNAL(mapped(QString)), this, SLOT(on_open_MailClient(QString)));




    signalMapperCart = new QSignalMapper(this);

    QObject::connect(new_cart, SIGNAL(triggered()), signalMapperCart, SLOT(map()));

    QObject::connect(signalMapperCart, SIGNAL(mapped(QString)), this, SLOT(on_open_Cart(QString)));

    signalMapperShowCart = new QSignalMapper(this);

    QObject::connect(show_carts, SIGNAL(triggered()), signalMapperShowCart, SLOT(map()));

    QObject::connect(signalMapperShowCart, SIGNAL(mapped(QString)), this, SLOT(on_show_Carts(QString)));


    signalMapperPricelist = new QSignalMapper(this);

    signalMapperShowImage = new QSignalMapper(this);

    QObject::connect(add_to_cart, SIGNAL(triggered()), signalMapperPricelist, SLOT(map()));

    QObject::connect(show_image, SIGNAL(triggered()), signalMapperShowImage, SLOT(map()));


    QObject::connect(signalMapperPricelist, SIGNAL(mapped(QString)), this, SLOT(on_add_Cart(QString)));

    QObject::connect(signalMapperShowImage, SIGNAL(mapped(QString)), this, SLOT(on_show_Image(QString)));


    emailAddressContextMenu = new QMenu("E-Mail", this);

    cartContextMenu = new QMenu("Cart", this);

    pricelistContextMenu = new QMenu("Pricelist", this);


    QObject::connect(this, SIGNAL(databaseLoaded()), this, SLOT(on_loaded_Database()));


    diaShowCarts = new DialogShowCarts(this);

    QObject::connect(diaShowCarts, SIGNAL(cartSelected(QString)), this, SLOT(on_reopen_Cart(QString)));

    diaOptions = new DialogOptions(this);

    diaImage = new DialogImage(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Database_triggered()
{

    if (osDatabase->isOpen()) {
        if (this->closeDatabase() == false) {
            return;
        }
    }


    QString fileName = QFileDialog::getSaveFileName(this, tr("New Database"),"",
                                                    tr("SQLite DB (*.db)"));
    if (!fileName.isEmpty()) {
        bool ret = osDatabase->open(fileName);
        if( ret == false) {
            QMessageBox::warning(this, genericHelper::getAppName(),
                                 tr("Database cannot be created: %1")
                                 .arg(fileName));
        } else {
            this->toggleInputEnabled(true);
            genericHelper::addRecentFiles(fileName,maxRecentFiles);
            ui->statusBar->showMessage(tr("Database created."), defaultStatusTimeout);

        }
    }

}

void MainWindow::on_actionOpen_Database_triggered()
{


    if (osDatabase->isOpen()) {
        if (this->closeDatabase() == false) {
            return;
        }
    }




    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Database"),"",
                                                      tr("SQLite DB (*.db)"));
      if (!fileName.isEmpty()) {

          bool ret = osDatabase->open(fileName);

          if( ret == false) {
              QMessageBox::warning(this, tr("Costs"),
                                   tr("Database cannot be opened: %1, Error %2")
                                   .arg(fileName).arg(osDatabase->getLastError()));
          } else {
              this->toggleInputEnabled(true);
              ui->statusBar->showMessage(tr("Database opened"), defaultStatusTimeout);
              emit databaseLoaded ( );
              genericHelper::addRecentFiles(fileName,maxRecentFiles);
          }
      }



}



void MainWindow::on_actionClose_Database_triggered()
{


    this->closeDatabase();
}

void MainWindow::toggleInputEnabled(bool toggle)
{
    QList<QWidget*> widgets = this->findChildren<QWidget*>();

    this->ui->actionClose_Database->setEnabled(toggle);
    this->ui->actionSave_Database->setEnabled(toggle);

    foreach (QWidget *widget, widgets)
    {

        if (
            (widget->objectName() != "mainToolBar") &&
            (widget->objectName() != "menuBar") &&
            (widget->objectName() != "menuFile")


            )
        {

        widget->setEnabled(toggle);
        }
     }



}

void MainWindow::fillRecentFileHistory()
{

     QListIterator<QString> recentFileItr (genericHelper::getRecentFiles());
     while (recentFileItr.hasNext()) {

         QString _currRecentFile = recentFileItr.next();



         QFileInfo _currRecentFileInfo(_currRecentFile);

         QAction *_recentFileAction = new QAction(this);
         _recentFileAction->setText(_currRecentFileInfo.filePath().left(10)+" ... "+_currRecentFileInfo.completeBaseName());


         QSignalMapper *signalMapper = new QSignalMapper(this);

         QObject::connect(_recentFileAction, SIGNAL(triggered()), signalMapper, SLOT(map()));
         signalMapper->setMapping(_recentFileAction, QString(_currRecentFile));
         QObject::connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(on_open_RecentFile(QString)));

         recentFileActions.append(_recentFileAction);
         ui->menuFile->insertAction(ui->actionQuit,_recentFileAction);


     }
}

void MainWindow::submit(QSqlRelationalTableModel *model)
{

    qDebug() << "submit";
    model->database().transaction();
     if (model->submitAll()) {
         model->database().commit();
     } else {
         model->database().rollback();
         QMessageBox::warning(this, tr("Costs"),
                              tr("The database reported an error: %1")
                              .arg(model->lastError().text()));
     }
     model->select();

     ui->statusBar->showMessage(tr("Database saved"), defaultStatusTimeout);
}

bool MainWindow::closeDatabase()
{
    if (osDatabase->isOpen()) {

        if (modelPricelist->isDirty() | modelCustomer->isDirty()) {
            qDebug() << "is dirty on close";
            QMessageBox::StandardButton ret;
            ret = QMessageBox::warning(this, genericHelper::getAppName(), tr("The database has been modified.\n Do you want to save your changes?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

            if (ret == QMessageBox::Save) {
                 this->submit(modelPricelist);
                 this->submit(modelCustomer);
            }
            if (ret == QMessageBox::Discard) {
                modelPricelist->revertAll();
                modelPricelist->select();
                modelCustomer->revertAll();
                modelCustomer->select();
            }
            if (ret == QMessageBox::Cancel) {
                return false;
            }

        }

        osDatabase->close();
        ui->statusBar->showMessage(tr("Database closed"), defaultStatusTimeout);
        this->toggleInputEnabled(false);

        return true;
    }
}


void MainWindow::on_actionQuit_triggered()
{
    if (osDatabase->isOpen()) {
        this->closeDatabase();
    }
    qApp->quit();
}

void MainWindow::on_open_RecentFile(QString fileName)
{

    if (osDatabase->isOpen()) {
        if (this->closeDatabase() == false) {
            return;
        }
    }


    bool ret = osDatabase->open(fileName);

    if( ret == false) {
        QMessageBox::warning(this, tr("Costs"),
                             tr("Database cannot be opened: %1, Error %2")
                             .arg(fileName).arg(osDatabase->getLastError()));
    } else {
        this->toggleInputEnabled(true);
        ui->statusBar->showMessage(tr("Database opened"), defaultStatusTimeout);
        emit databaseLoaded ( );

    }

}

void MainWindow::on_open_Cart(QString customerid)
{

    cart_widget = new CartWidget(this->ui->tabWidget);

    QObject::connect(cart_widget, SIGNAL(onCartNameChanged(QString)), this, SLOT(on_changed_CartName(QString)));

    if (this->ui->tabWidget->count() <= 2) {

        this->ui->tabWidget->addTab(cart_widget,tr("Cart"));



    }

    QString _timestmap = genericHelper::getPrettyTimestamp();
    QString _prettytimestmap = genericHelper::getPrettyTimestamp();

    cart_widget->setCustomerId(customerid);
    cart_widget->setCustomerName(this->proxymodelCustomer->getColData(1,customerid,2).toString());
    cart_widget->setDate(_timestmap);

    if (osDatabase->isOpen()) {

       if (osDatabase->createEmptyShoppingCart(customerid.toInt(), this->proxymodelCustomer->getColData(1,customerid,2).toString(), _prettytimestmap, _timestmap.replace(":","").replace(" ","").replace("-","")) == true ) {
        this->modelCart->setTable("cart_"+customerid+"_"+_timestmap);

        this->modelCart->setHeaderData(1, Qt::Horizontal, QObject::tr("Product Id"));
        this->modelCart->setHeaderData(2, Qt::Horizontal, QObject::tr("Article Name"));
        this->modelCart->setHeaderData(3, Qt::Horizontal, QObject::tr("Units"));
        this->modelCart->setHeaderData(4, Qt::Horizontal, QObject::tr("Packages"));
        this->modelCart->setHeaderData(5, Qt::Horizontal, QObject::tr("Price/Unit"));
        this->modelCart->setHeaderData(6, Qt::Horizontal, QObject::tr("Price/Package"));
        this->modelCart->setHeaderData(7, Qt::Horizontal, QObject::tr("Currency"));
        this->modelCart->setHeaderData(8, Qt::Horizontal, QObject::tr("Delivery Time"));
        this->modelCart->setHeaderData(9, Qt::Horizontal, QObject::tr("Training"));
        this->modelCart->setHeaderData(10, Qt::Horizontal, QObject::tr("Trial"));




        this->modelCart->select();
        this->cart_widget->setModel(modelCart);

       }
    }

    //this->modelCustomer->setTable("customer");
    //this->modelCustomer->select();

    this->ui->tabWidget->setCurrentIndex(tab_index_cart);

}

void MainWindow::on_reopen_Cart(QString cartname)
{
    cart_widget = new CartWidget(this->ui->tabWidget);

    QObject::connect(cart_widget, SIGNAL(onCartNameChanged(QString)), this, SLOT(on_changed_CartName(QString)));

    this->currentCartInfos = osDatabase->getCartInfos(cartname);

    if (this->ui->tabWidget->count() <= 2) {
        this->ui->tabWidget->addTab(cart_widget,tr("Cart"));
    }

   cart_widget->setCustomerId(this->currentCartInfos.value("customerid"));
   cart_widget->setCustomerName(this->currentCartInfos.value("customer_name"));
   cart_widget->setDate(this->currentCartInfos.value("pretty_date"));
   cart_widget->setCartName(this->currentCartInfos.value("cartname"));

    if (osDatabase->isOpen()) {

        this->modelCart->setTable(cartname);

        this->modelCart->setHeaderData(1, Qt::Horizontal, QObject::tr("Product Id"));
        this->modelCart->setHeaderData(2, Qt::Horizontal, QObject::tr("Article Name"));
        this->modelCart->setHeaderData(3, Qt::Horizontal, QObject::tr("Units"));
        this->modelCart->setHeaderData(4, Qt::Horizontal, QObject::tr("Packages"));
        this->modelCart->setHeaderData(5, Qt::Horizontal, QObject::tr("Price/Unit"));
        this->modelCart->setHeaderData(6, Qt::Horizontal, QObject::tr("Price/Package"));
        this->modelCart->setHeaderData(7, Qt::Horizontal, QObject::tr("Currency"));
        this->modelCart->setHeaderData(8, Qt::Horizontal, QObject::tr("Delivery Time"));
        this->modelCart->setHeaderData(9, Qt::Horizontal, QObject::tr("Training"));
        this->modelCart->setHeaderData(10, Qt::Horizontal, QObject::tr("Trial"));




        this->modelCart->select();
        this->cart_widget->setModel(modelCart);


    }



    this->ui->tabWidget->setCurrentIndex(tab_index_cart);
}

void MainWindow::on_changed_CartName(QString newcartname)
{
    qDebug() << "on_changed_CartName";
    //osDatabase->updateCartName(this->curr)
    osDatabase->updateCartName(this->currentCartInfos.value("carttablename"),newcartname);
}

void MainWindow::on_show_Carts(QString customerid)
{
    qDebug() << "on_show_Carts" << customerid;

    diaShowCarts->setCarts(osDatabase->getTables(QRegExp("^cart_"+customerid+"_")));

    //currentCartCustomerId = customerid;
    //currentCartCustomerName = this->proxymodelCustomer->getColData(1,customerid,2).toString();



    if (diaShowCarts->getDialogShown() == true)
    {
        diaShowCarts->close();

        diaShowCarts->show();

    } else {


        diaShowCarts->show();
        diaShowCarts->setDialogShown();
    }


}

void MainWindow::on_add_Cart(QString productid)
{
    qDebug() << "on_add_Cart " << this->modelCart->tableName();


    osDatabase->addItemToCart(productid.toInt(),this->modelCart->tableName());
    this->modelCart->select();

}

void MainWindow::on_show_Image(QString productid)
{
    qDebug() << "on_show_Image ";
    diaImage->setImage(QByteArray( this->modelCustomer->index( this->ui->tableViewPricelist->selectionModel()->currentIndex().row(), 1).data().toByteArray()));

    return;
    if (diaImage->getDialogShown() == true)
    {
        diaImage->close();

        diaImage->show();

    } else {


        diaImage->show();
        diaImage->setDialogShown();
    }
}





void MainWindow::on_loaded_Database()
{
    qDebug() << "on_loaded_Database";

    this->modelPricelist->setTable("pricelist");
    this->modelPricelist->select();


    this->modelPricelist->setHeaderData(1, Qt::Horizontal, QObject::tr("Image"));
    this->modelPricelist->setHeaderData(2, Qt::Horizontal, QObject::tr("Product Id"));
    this->modelPricelist->setHeaderData(3, Qt::Horizontal, QObject::tr("Article Name"));
    this->modelPricelist->setHeaderData(4, Qt::Horizontal, QObject::tr("Price/Unit"));
    this->modelPricelist->setHeaderData(5, Qt::Horizontal, QObject::tr("Price/Package"));
    this->modelPricelist->setHeaderData(6, Qt::Horizontal, QObject::tr("Currency"));
    this->modelPricelist->setHeaderData(7, Qt::Horizontal, QObject::tr("Packing Units"));
    this->modelPricelist->setHeaderData(8, Qt::Horizontal, QObject::tr("Min. Units to Sell"));
    this->modelPricelist->setHeaderData(9, Qt::Horizontal, QObject::tr("Length"));
    this->modelPricelist->setHeaderData(10, Qt::Horizontal, QObject::tr("Width"));
    this->modelPricelist->setHeaderData(11, Qt::Horizontal, QObject::tr("Depth"));
    this->modelPricelist->setHeaderData(12, Qt::Horizontal, QObject::tr("Height"));
    this->modelPricelist->setHeaderData(13, Qt::Horizontal, QObject::tr("Weight"));
    this->modelPricelist->setHeaderData(14, Qt::Horizontal, QObject::tr("Estimated delivery time"));
    this->modelPricelist->setHeaderData(15, Qt::Horizontal, QObject::tr("Article Description"));

    this->modelPricelist->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

    this->ui->tableViewPricelist->setModel(proxymodelPricelist);

    this->ui->tableViewPricelist->setItemDelegateForColumn(1,imgDelegateProductImage);
    this->ui->tableViewPricelist->setItemDelegateForColumn(2,iDelegateProductId);
    this->ui->tableViewPricelist->setItemDelegateForColumn(4,fDelegatePriceUnit);
    this->ui->tableViewPricelist->setItemDelegateForColumn(5,fDelegatePricePackage);
    this->ui->tableViewPricelist->setItemDelegateForColumn(6,cbxMyCurrencyComboDelegate);
    this->ui->tableViewPricelist->setItemDelegateForColumn(7,iDelegatePackingUnit);
    this->ui->tableViewPricelist->setItemDelegateForColumn(8,iDelegateMinSellUnits);
    this->ui->tableViewPricelist->setItemDelegateForColumn(9,iDelegateArticleLength);
    this->ui->tableViewPricelist->setItemDelegateForColumn(10,iDelegateArticleWidth);
    this->ui->tableViewPricelist->setItemDelegateForColumn(11,iDelegateArticleDepth);
    this->ui->tableViewPricelist->setItemDelegateForColumn(12,iDelegateArticleHeight);
    this->ui->tableViewPricelist->setItemDelegateForColumn(13,iDelegateArticleWeight);






    this->ui->tableViewPricelist->setColumnHidden(0,true);


    this->ui->tableViewPricelist->resizeColumnsToContents();
    this->ui->tableViewPricelist->resizeRowsToContents();


    this->modelCustomer->setTable("customer");
    this->modelCustomer->select();



    //


    this->modelCustomer->setHeaderData(1, Qt::Horizontal, QObject::tr("Customer Id"));
    this->modelCustomer->setHeaderData(2, Qt::Horizontal, QObject::tr("Customer Name"));
    this->modelCustomer->setHeaderData(3, Qt::Horizontal, QObject::tr("Phone"));
    this->modelCustomer->setHeaderData(4, Qt::Horizontal, QObject::tr("E-Mail"));
    this->modelCustomer->setHeaderData(5, Qt::Horizontal, QObject::tr("Address"));
    this->modelCustomer->setHeaderData(6, Qt::Horizontal, QObject::tr("ZIP-Code"));
    this->modelCustomer->setHeaderData(7, Qt::Horizontal, QObject::tr("Country"));
    this->modelCustomer->setHeaderData(8, Qt::Horizontal, QObject::tr("Info"));

    this->modelCustomer->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

    this->ui->tableViewCustomer->setModel(proxymodelCustomer);

    this->ui->tableViewCustomer->setItemDelegateForColumn(1,iDelegateCustomerId);
    this->ui->tableViewCustomer->setItemDelegateForColumn(4,emlMyEmailDelegate);


    this->ui->tableViewCustomer->setColumnHidden(0,true);
    this->ui->tableViewCustomer->setColumnHidden(9,true);
    this->ui->tableViewCustomer->setColumnHidden(10,true);


    this->ui->tableViewCustomer->resizeColumnsToContents();








}

void MainWindow::on_open_MailClient(QString mailaddress)
{
qDebug() << "on_open_MailClient";

    QDesktopServices::openUrl(QUrl("mailto:"+mailaddress));
}

void MainWindow::on_actionSave_Database_triggered()
{
    qDebug() << "on_actionSave_Database_triggered";
    if (modelPricelist->isDirty()) {

         this->submit(modelPricelist);
    }
}

void MainWindow::on_actionRevert_Changes_triggered()
{


    if (modelPricelist->isDirty()) {

         modelPricelist->revertAll();
         modelPricelist->select();
    }
    if (modelCustomer->isDirty()) {

         modelCustomer->revertAll();
         modelCustomer->select();
    }
}

void MainWindow::on_actionNew_Entry_Pricelist_triggered()
{



    switch( this->ui->tabWidget->currentIndex() )
    {
        case 0:
            modelPricelist->insertRecord(modelPricelist->rowCount(),modelPricelist->record());
            ui->tableViewPricelist->scrollToBottom();
            break ;
        case 1:
            modelCustomer->insertRecord(modelCustomer->rowCount(),modelCustomer->record());
            ui->tableViewCustomer->scrollToBottom();
            break ;
        case 2:
            QMessageBox::information(this, genericHelper::getAppName(), tr("Add new products by selecting them in the pricelist tab."));
            this->ui->tabWidget->setCurrentIndex(0);
            break ;
    }

}

void MainWindow::on_actionFill_with_Example_Data_triggered()
{
    osDatabase->fillAllExampleData();
    modelPricelist->select();
    modelCustomer->select();
}

void MainWindow::on_tableViewCustomer_clicked(const QModelIndex &index)
{

    QString cellvalue = index.model()->data(index,Qt::DisplayRole).toString();
    if (genericHelper::isValidEmailAddress(cellvalue) == true) {


        //QDesktopServices::openUrl(QUrl("mailto:"+cellvalue));
    }

}

void MainWindow::on_tableViewCustomer_customContextMenuRequested(const QPoint &pos)
{


    if (genericHelper::isValidEmailAddress(this->ui->tableViewCustomer->selectionModel()->selectedIndexes().at(0).data().toString()) == true) {
        emailAddressContextMenu->addAction(open_mailclient);

        signalMapperEmailAddress->setMapping(open_mailclient, QString(this->ui->tableViewCustomer->selectionModel()->selectedIndexes().at(0).data().toString()));

        emailAddressContextMenu->popup(this->ui->tableViewCustomer->viewport()->mapToGlobal(pos));

    } else {


        if (this->ui->tabWidget->count() == 2) {

        cartContextMenu->addAction(new_cart);

        signalMapperCart->setMapping(new_cart, QString( this->modelCustomer->index( this->ui->tableViewCustomer->selectionModel()->currentIndex().row(), 1).data(Qt::DisplayRole).toString()));

        cartContextMenu->popup(this->ui->tableViewCustomer->viewport()->mapToGlobal(pos));

        }

        cartContextMenu->addAction(show_carts);

        signalMapperShowCart->setMapping(show_carts, QString( this->modelCustomer->index( this->ui->tableViewCustomer->selectionModel()->currentIndex().row(), 1).data(Qt::DisplayRole).toString()));

        cartContextMenu->popup(this->ui->tableViewCustomer->viewport()->mapToGlobal(pos));

    }


}

void MainWindow::on_actionDelete_Entry_triggered()
{

}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{

    if (index == 2) {
        this->ui->tabWidget->removeTab(tab_index_cart);
    }
}

void MainWindow::on_tableViewPricelist_customContextMenuRequested(const QPoint &pos)
{
    if (this->ui->tabWidget->count() > 2) {

        pricelistContextMenu->addAction(add_to_cart);

        signalMapperPricelist->setMapping(add_to_cart, QString( this->modelPricelist->index( this->ui->tableViewPricelist->selectionModel()->currentIndex().row(), 1).data(Qt::DisplayRole).toString()));


    }


        pricelistContextMenu->addAction(show_image);
        signalMapperShowImage->setMapping(show_image, QString( this->modelPricelist->index( this->ui->tableViewPricelist->selectionModel()->currentIndex().row(), 1).data(Qt::DisplayRole).toString()));

    pricelistContextMenu->popup(this->ui->tableViewPricelist->viewport()->mapToGlobal(pos));

}

void MainWindow::on_actionExportODF_triggered()
{

    if (this->ui->tabWidget->currentIndex() == tab_index_cart) {

        QString _template;
        QString extractedDocxDir;
        QString newDocxFile;
        QHash<QString,QString> replacementvars;

        QFile file(genericHelper::getTemplateFile());
        if (file.exists()) {

            extractedDocxDir = genericHelper::unzipDocxWithAddon7Zip(genericHelper::getTemplateFile());


            replacementvars = genericHelper::getDocxReplacmentVariables();

            replacementvars["$DATE$"] = this->cart_widget->getDate();
            replacementvars["$CUSTOMER$"] = this->cart_widget->getCustomerName();
            replacementvars["$CUSTOMERID$"] = this->cart_widget->getCustomerId();
            replacementvars["$TITLE$"] = this->cart_widget->getCartName();

            int row = this->modelCart->rowCount();
            int col = this->modelCart->columnCount();

            QStringList products;

            for (int i = 0; i < row ; ++i) {

                products << this->modelCart->data(this->modelCart->index(i, 1), Qt::DisplayRole).toString()+" ("+this->modelCart->data(this->modelCart->index(i, 2), Qt::DisplayRole).toString()+")";

            }

            replacementvars["$PRODUCTS$"] = products.join("\n");

            genericHelper::replaceVarInDocx(extractedDocxDir,replacementvars);

            newDocxFile = genericHelper::zipTempDirToDocxWithAddon7Zip(extractedDocxDir);



        } else {
            QMessageBox::warning(this, genericHelper::getAppName(), tr("Report template file not found: %1").arg(genericHelper::getTemplateFile()));
        }

        bool ret = false;

        QString filters("Microsoft Word 2007/2010/2013 XML (*.docx)");
        QString defaultFilter("Microsoft Word 2007/2010/2013 XML (*.docx)");
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save report file"), QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0] + QDir::separator() + genericHelper::getTimestamp()+"_"+this->cart_widget->getCartName()+"_"+this->cart_widget->getCustomerName()+".docx", filters, &defaultFilter);

        if (!fileName.isEmpty()) {

              QFile::copy(QDir::toNativeSeparators(newDocxFile),QDir::toNativeSeparators(fileName));


        }


    } else {

        QMessageBox::warning(this, genericHelper::getAppName(), tr("Export not available for %1").arg(this->ui->tabWidget->tabText(this->ui->tabWidget->currentIndex())));

    }


}

void MainWindow::on_actionOptions_triggered()
{
    if (diaOptions->getDialogShown() == true)
    {
        diaOptions->close();

        diaOptions->show();

    } else {


        diaOptions->show();
        diaOptions->setDialogShown();
    }

}


void MainWindow::on_actionAdd_to_Cart_triggered()
{
    qDebug() << "on_add_Cart " << this->modelCart->tableName();

    QString  productid = QString( this->modelPricelist->index( this->ui->tableViewPricelist->selectionModel()->currentIndex().row(), 1).data(Qt::DisplayRole).toString());
    osDatabase->addItemToCart(productid.toInt(),this->modelCart->tableName());
    this->modelCart->select();
}

void MainWindow::on_actionRemove_From_Cart_triggered()
{

}

void MainWindow::on_actionShow_Carts_triggered()
{

    QString customerid = QString( this->modelCustomer->index( this->ui->tableViewCustomer->selectionModel()->currentIndex().row(), 1).data(Qt::DisplayRole).toString());
    diaShowCarts->setCarts(osDatabase->getTables(QRegExp("^cart_"+customerid+"_")));

    //currentCartCustomerId = customerid;
    //currentCartCustomerName = this->proxymodelCustomer->getColData(1,customerid,2).toString();



    if (diaShowCarts->getDialogShown() == true)
    {
        diaShowCarts->close();

        diaShowCarts->show();

    } else {


        diaShowCarts->show();
        diaShowCarts->setDialogShown();
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{


    if (index == tab_index_pricelist ) {

            this->ui->actionShow_Carts->setDisabled(true);
            this->ui->actionRemove_From_Cart->setDisabled(true);
            this->ui->actionNew_Entry_Pricelist->setDisabled(false);
            this->ui->actionDelete_Entry->setDisabled(false);
            this->ui->actionRevert_Changes->setDisabled(false);

            if (this->ui->tabWidget->count() > 2) {
                this->ui->actionAdd_to_Cart->setDisabled(false);
            } else {
                this->ui->actionAdd_to_Cart->setDisabled(true);
            }

            this->ui->actionExportODF->setDisabled(true);
            this->ui->actionNew_Cart->setDisabled(true);



            return;
    }

    if (index == tab_index_customer ) {

            this->ui->actionShow_Carts->setDisabled(false);
            this->ui->actionRemove_From_Cart->setDisabled(true);
            this->ui->actionAdd_to_Cart->setDisabled(true);
            this->ui->actionNew_Entry_Pricelist->setDisabled(false);
            this->ui->actionDelete_Entry->setDisabled(false);
            this->ui->actionRevert_Changes->setDisabled(false);
            this->ui->actionExportODF->setDisabled(true);
            this->ui->actionNew_Cart->setDisabled(false);

            return;
    }

    if (index == tab_index_cart ) {

            this->ui->actionShow_Carts->setDisabled(false);
            this->ui->actionRemove_From_Cart->setDisabled(false);
            this->ui->actionAdd_to_Cart->setDisabled(false);
            this->ui->actionNew_Entry_Pricelist->setDisabled(true);
            this->ui->actionDelete_Entry->setDisabled(true);
            this->ui->actionRevert_Changes->setDisabled(true);
            this->ui->actionExportODF->setDisabled(false);
            this->ui->actionNew_Cart->setDisabled(true);

            return;
    }

}

void MainWindow::on_actionNew_Cart_triggered()
{

    this->on_open_Cart(QString( this->modelCustomer->index( this->ui->tableViewCustomer->selectionModel()->currentIndex().row(), 1).data(Qt::DisplayRole).toString()));
}

void MainWindow::on_tableViewPricelist_doubleClicked(const QModelIndex &index)
{

}

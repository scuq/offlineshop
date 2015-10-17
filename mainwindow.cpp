#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->toggleInputEnabled(false);

    osDatabase = new osDb();

    maxRecentFiles = 4;

    defaultStatusTimeout = 5000;

    this->fillRecentFileHistory();

    modelPricelist = new QSqlRelationalTableModel(this,QSqlDatabase::database(genericHelper::getAppName()));

    proxymodelPricelist = new AdvQSortFilterProxyModel(this);

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



    proxymodelCustomer = new AdvQSortFilterProxyModel(this);

    proxymodelCustomer->setSourceModel(modelCustomer);

    iDelegateCustomerId = new MyIntDelegate();

    open_mailclient = new QAction(tr("Open in &Mail Client"), this);


    signalMapperEmailAddress = new QSignalMapper(this);

    QObject::connect(open_mailclient, SIGNAL(triggered()), signalMapperEmailAddress, SLOT(map()));



    QObject::connect(signalMapperEmailAddress, SIGNAL(mapped(QString)), this, SLOT(on_open_MailClient(QString)));

    //connect(open_mailclient, SIGNAL(triggered()), this, SLOT(on_open_MailClient()));

    /**

         QObject::connect(_recentFileAction, SIGNAL(triggered()), signalMapper, SLOT(map()));
         signalMapper->setMapping(_recentFileAction, QString(_currRecentFile));
         QObject::connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(on_open_RecentFile(QString)));
      **/

    emailAddressContextMenu = new QMenu("E-Mail", this);

    QObject::connect(this, SIGNAL(databaseLoaded()), this, SLOT(on_loaded_Database()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Database_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("New Database"),"",
                                                    tr("SQLite DB (*.db)"));
    if (!fileName.isEmpty()) {
        bool ret = osDatabase->open(fileName);
        if( ret == false) {
            QMessageBox::warning(this, tr("Costs"),
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
    if (osDatabase->isOpen()) {
        osDatabase->close();
        ui->statusBar->showMessage(tr("Database closed"), defaultStatusTimeout);
        this->toggleInputEnabled(false);
    }
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


void MainWindow::on_actionQuit_triggered()
{
    if (osDatabase->isOpen()) {
        osDatabase->close();
        this->toggleInputEnabled(false);
    }
    qApp->quit();
}

void MainWindow::on_open_RecentFile(QString fileName)
{

qDebug() << "on_open_RecentFile";
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

void MainWindow::on_loaded_Database()
{
    qDebug() << "on_loaded_Database";

    this->modelPricelist->setTable("pricelist");
    this->modelPricelist->select();


    this->modelPricelist->setHeaderData(1, Qt::Horizontal, QObject::tr("Product Id"));
    this->modelPricelist->setHeaderData(2, Qt::Horizontal, QObject::tr("Article Name"));
    this->modelPricelist->setHeaderData(3, Qt::Horizontal, QObject::tr("Price/Unit"));
    this->modelPricelist->setHeaderData(4, Qt::Horizontal, QObject::tr("Price/Package"));
    this->modelPricelist->setHeaderData(5, Qt::Horizontal, QObject::tr("Currency"));
    this->modelPricelist->setHeaderData(6, Qt::Horizontal, QObject::tr("Packing Units"));
    this->modelPricelist->setHeaderData(7, Qt::Horizontal, QObject::tr("Min. Units to Sell"));
    this->modelPricelist->setHeaderData(8, Qt::Horizontal, QObject::tr("Length"));
    this->modelPricelist->setHeaderData(9, Qt::Horizontal, QObject::tr("Width"));
    this->modelPricelist->setHeaderData(10, Qt::Horizontal, QObject::tr("Depth"));
    this->modelPricelist->setHeaderData(11, Qt::Horizontal, QObject::tr("Height"));
    this->modelPricelist->setHeaderData(12, Qt::Horizontal, QObject::tr("Weight"));
    this->modelPricelist->setHeaderData(12, Qt::Horizontal, QObject::tr("Estimated delivery time"));
    this->modelPricelist->setHeaderData(13, Qt::Horizontal, QObject::tr("Article Description"));

    this->modelPricelist->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

    this->ui->tableViewPricelist->setModel(proxymodelPricelist);

    this->ui->tableViewPricelist->setItemDelegateForColumn(1,iDelegateProductId);
    this->ui->tableViewPricelist->setItemDelegateForColumn(3,fDelegatePriceUnit);
    this->ui->tableViewPricelist->setItemDelegateForColumn(4,fDelegatePricePackage);
    this->ui->tableViewPricelist->setItemDelegateForColumn(5,cbxMyCurrencyComboDelegate);
    this->ui->tableViewPricelist->setItemDelegateForColumn(6,iDelegatePackingUnit);
    this->ui->tableViewPricelist->setItemDelegateForColumn(7,iDelegateMinSellUnits);
    this->ui->tableViewPricelist->setItemDelegateForColumn(8,iDelegateArticleLength);
    this->ui->tableViewPricelist->setItemDelegateForColumn(9,iDelegateArticleWidth);
    this->ui->tableViewPricelist->setItemDelegateForColumn(10,iDelegateArticleDepth);
    this->ui->tableViewPricelist->setItemDelegateForColumn(11,iDelegateArticleHeight);
    this->ui->tableViewPricelist->setItemDelegateForColumn(12,iDelegateArticleWeight);







    this->ui->tableViewPricelist->setColumnHidden(0,true);


    this->ui->tableViewPricelist->resizeColumnsToContents();


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

    if (this->ui->tabWidget->currentIndex() == 0) {
        modelPricelist->insertRecord(modelPricelist->rowCount(),modelPricelist->record());
        ui->tableViewPricelist->scrollToBottom();
    } else {
        modelCustomer->insertRecord(modelCustomer->rowCount(),modelCustomer->record());
        ui->tableViewCustomer->scrollToBottom();
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

    }


}

void MainWindow::on_actionDelete_Entry_triggered()
{
    if (this->ui->tabWidget->currentIndex() == 0) {
        modelPricelist->insertRecord(modelPricelist->rowCount(),modelPricelist->record());
        ui->tableViewPricelist->scrollToBottom();
    } else {
        modelCustomer->insertRecord(modelCustomer->rowCount(),modelCustomer->record());
        ui->tableViewCustomer->scrollToBottom();
        modelCustomer->deleteRowFromTable(modelCustomer->)
    }
}

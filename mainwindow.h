#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>
#include <QAction>
#include <QDebug>
#include <QFileInfo>
#include <QSignalMapper>
#include <QCloseEvent>
#include <QSqlRelationalTableModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDesktopServices>
#include "advqsortfilterproxymodel.h"
#include "advqsortfilterproxymodelcustomer.h"
#include <myintdelegate.h>
#include <myfloatdelegate.h>
#include <mycurrencycombodelegate.h>
#include <myemaillineeditdelegate.h>
#include <myphonelineeditdelegate.h>
#include <myimagedelegate.h>
#include <mynoeditdelegate.h>
#include "cartwidget.h"
#include "dialogshowcarts.h"
#include "dialogoptions.h"
#include "dialogshowproduct.h"
#include "dialogshowcustomer.h"
#include "QTranslator"
#include "osdb.h"
#include "updatecheck.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_Database_triggered();

    void on_actionOpen_Database_triggered();

    void on_actionClose_Database_triggered();

    void on_actionQuit_triggered();

    void on_open_RecentFile(QString fileName);

    void on_open_Cart(QString customerid);

    void on_reopen_Cart(QString cartname);

    void on_changed_CartName(QString newcartname);

    void on_show_Carts(QString customerid);

    void on_add_Cart(QString productid);

    void on_show_Product(QString productid);

    void on_show_Customer(QString customerid);

    void on_loaded_Database();

    void on_open_MailClient(QString mailaddress);

    void on_actionSave_Database_triggered();

    void on_actionRevert_Changes_triggered();

    void on_actionNew_Entry_Pricelist_triggered();

    void on_actionFill_with_Example_Data_triggered();

    void on_tableViewCustomer_clicked(const QModelIndex &index);

    void on_tableViewCustomer_customContextMenuRequested(const QPoint &pos);

    void on_actionDelete_Entry_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_tableViewPricelist_customContextMenuRequested(const QPoint &pos);

    void on_actionExportODF_triggered();

    void on_actionOptions_triggered();

    void on_lang_Changed(QString lang);

    void on_actionAdd_to_Cart_triggered();

    void on_actionRemove_From_Cart_triggered();

    void on_actionShow_Carts_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_actionNew_Cart_triggered();

    void on_tableViewPricelist_doubleClicked(const QModelIndex &index);

    void on_tableViewPricelist_clicked(const QModelIndex &index);



private:
    Ui::MainWindow *ui;
    osDb *osDatabase;
    int maxRecentFiles;
    int defaultStatusTimeout;
    QTranslator translator;
    QList<QAction*> recentFileActions;
    QSqlRelationalTableModel *modelPricelist;
    QSqlRelationalTableModel *modelCustomer;
    QSqlRelationalTableModel *modelCart;
    MyImageDelegate *imgDelegateProductImage;
    MyIntDelegate *iDelegateProductId;
    MyFloatDelegate *fDelegateArticleLength;
    MyFloatDelegate *fDelegateArticleDepth;
    MyFloatDelegate *fDelegateArticleWidth;
    MyFloatDelegate *fDelegateArticleHeight;
    MyFloatDelegate *fDelegateArticleWeight;
    MyFloatDelegate *fDelegateArticleDiameter;
    MyIntDelegate *iDelegatePackingUnit;
    MyIntDelegate *iDelegateMinSellUnits;
    MyFloatDelegate *fDelegatePriceUnit;
    MyFloatDelegate *fDelegatePricePackage;
    MyNoEditDelegate *noedDelegate;
    MyCurrencyComboDelegate *cbxMyCurrencyComboDelegate;
    MyEmailLineEditDelegate *emlMyEmailDelegate;
    MyPhoneLineEditDelegate *phoMyPhoneDelegate;
    const int tab_index_pricelist = 0;
    const int tab_index_customer = 1;
    const int tab_index_cart = 2;

    MyIntDelegate *iDelegateCustomerId;

    AdvQSortFilterProxyModel *proxymodelPricelist;
    AdvQSortFilterProxyModelCustomer *proxymodelCustomer;

    QAction *open_mailclient;
    QMenu *emailAddressContextMenu;
    QSignalMapper *signalMapperEmailAddress;

    QAction *new_cart;
    QAction *show_carts;
    QMenu *cartContextMenu;
    QSignalMapper *signalMapperCart;
    QSignalMapper *signalMapperShowCart;

    DialogShowCarts *diaShowCarts;
    DialogOptions *diaOptions;
    DialogShowproduct *diaShowproduct;
    DialogShowcustomer *diaShowcustomer;

    QAction *add_to_cart;
    QAction *show_product;
    QAction *show_customer;

    QMenu *pricelistContextMenu;
    QSignalMapper *signalMapperPricelist;
    QSignalMapper *signalMapperShowProduct;
    QSignalMapper *signalMapperShowCustomer;

    CartWidget *cart_widget;

    QHash<QString,QString> currentCartInfos;

    void toggleInputEnabled(bool toggle);
    void fillRecentFileHistory();
    void submit(QSqlRelationalTableModel *model);
    bool closeDatabase();

    void closeEvent(QCloseEvent *); // Overriding the window's close event

    updateCheck *uc;



signals:
    void databaseLoaded();
    void retranslateSubDialogs();
};

#endif // MAINWINDOW_H

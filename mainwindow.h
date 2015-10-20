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
#include <QSqlRelationalTableModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDesktopServices>
#include "advqsortfilterproxymodel.h"
#include <myintdelegate.h>
#include <myfloatdelegate.h>
#include <mycurrencycombodelegate.h>
#include <myemaillineeditdelegate.h>
#include "cartwidget.h"
#include "dialogshowcarts.h"
#include "dialogoptions.h"

#include "osdb.h"

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

private:
    Ui::MainWindow *ui;
    osDb *osDatabase;
    int maxRecentFiles;
    int defaultStatusTimeout;
    QList<QAction*> recentFileActions;
    QSqlRelationalTableModel *modelPricelist;
    QSqlRelationalTableModel *modelCustomer;
    QSqlRelationalTableModel *modelCart;
    MyIntDelegate *iDelegateProductId;
    MyIntDelegate *iDelegateArticleLength;
    MyIntDelegate *iDelegateArticleDepth;
    MyIntDelegate *iDelegateArticleWidth;
    MyIntDelegate *iDelegateArticleHeight;
    MyIntDelegate *iDelegateArticleWeight;
    MyIntDelegate *iDelegatePackingUnit;
    MyIntDelegate *iDelegateMinSellUnits;
    MyFloatDelegate *fDelegatePriceUnit;
    MyFloatDelegate *fDelegatePricePackage;
    MyCurrencyComboDelegate *cbxMyCurrencyComboDelegate;
    MyEmailLineEditDelegate *emlMyEmailDelegate;
    int tab_index_pricelist;
    int tab_index_customer;
    int tab_index_cart;

    MyIntDelegate *iDelegateCustomerId;

    AdvQSortFilterProxyModel *proxymodelPricelist;
    AdvQSortFilterProxyModel *proxymodelCustomer;

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

    QAction *add_to_cart;
    QMenu *pricelistContextMenu;
    QSignalMapper *signalMapperPricelist;

    CartWidget *cart_widget;

    QHash<QString,QString> currentCartInfos;

    void toggleInputEnabled(bool toggle);
    void fillRecentFileHistory();
    void submit(QSqlRelationalTableModel *model);
    bool closeDatabase();

signals:
    void databaseLoaded();
};

#endif // MAINWINDOW_H
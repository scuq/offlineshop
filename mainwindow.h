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
#include <QSqlRecord>
#include "advqsortfilterproxymodel.h"
#include <myintdelegate.h>
#include <myfloatdelegate.h>
#include <mycurrencycombodelegate.h>
#include <myemaillineeditdelegate.h>

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

    void on_loaded_Database();

    void on_open_MailClient(QString mailaddress);

    void on_actionSave_Database_triggered();

    void on_actionRevert_Changes_triggered();

    void on_actionNew_Entry_Pricelist_triggered();

    void on_actionFill_with_Example_Data_triggered();

    void on_tableViewCustomer_clicked(const QModelIndex &index);

    void on_tableViewCustomer_customContextMenuRequested(const QPoint &pos);

    void on_actionDelete_Entry_triggered();

private:
    Ui::MainWindow *ui;
    osDb *osDatabase;
    int maxRecentFiles;
    int defaultStatusTimeout;
    QList<QAction*> recentFileActions;
    QSqlRelationalTableModel *modelPricelist;
    QSqlRelationalTableModel *modelCustomer;
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

    MyIntDelegate *iDelegateCustomerId;

    AdvQSortFilterProxyModel *proxymodelPricelist;
    AdvQSortFilterProxyModel *proxymodelCustomer;

    QAction *open_mailclient;
    QMenu *emailAddressContextMenu;
    QSignalMapper *signalMapperEmailAddress;

    void toggleInputEnabled(bool toggle);
    void fillRecentFileHistory();
    void submit(QSqlRelationalTableModel *model);

signals:
    void databaseLoaded();
};

#endif // MAINWINDOW_H

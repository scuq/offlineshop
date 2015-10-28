#include "dialogshowcarts.h"
#include "ui_dialogshowcarts.h"

DialogShowCarts::DialogShowCarts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShowCarts)
{
    ui->setupUi(this);
    restoreGeometry(genericHelper::getGeometry("showcarts").toByteArray());
}

DialogShowCarts::~DialogShowCarts()
{
    delete ui;
}

void DialogShowCarts::setDialogShown()
{
    dialogShown = true;



}

bool DialogShowCarts::getDialogShown()
{

    return dialogShown;
}

void DialogShowCarts::clearCarts()
{
        this->ui->treeWidget->clear();
}

void DialogShowCarts::addCarts(QString cart, QHash<QString,QString> cartinfo)
{

    qDebug() << cartinfo;

    QTreeWidgetItem * topLevel = new QTreeWidgetItem();
    topLevel->setText(0, cart);
    topLevel->setText(1, cartinfo.value("pretty_date"));
    topLevel->setText(2, cartinfo.value("cartname"));
    topLevel->setText(3, cartinfo.value("customer_name"));

    this->ui->treeWidget->addTopLevelItem(topLevel);

    this->ui->treeWidget->hideColumn(0);
    this->ui->treeWidget->resizeColumnToContents(1);
    this->ui->treeWidget->resizeColumnToContents(2);
    this->ui->treeWidget->resizeColumnToContents(3);




}

void DialogShowCarts::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{

    genericHelper::saveGeometry("showcarts",saveGeometry());
    emit cartSelected (item->text());
    this->hide();

}

void DialogShowCarts::on_treeWidget_doubleClicked(const QModelIndex &index)
{

    genericHelper::saveGeometry("showcarts",saveGeometry());
    emit cartSelected (this->ui->treeWidget->topLevelItem(index.row())->data(0,Qt::DisplayRole).toString());
    this->hide();
}

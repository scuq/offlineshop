#include "dialogshowcarts.h"
#include "ui_dialogshowcarts.h"

DialogShowCarts::DialogShowCarts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShowCarts)
{
    ui->setupUi(this);
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

void DialogShowCarts::setCarts(QStringList carts)
{
    this->ui->listWidget->clear();
    this->ui->listWidget->addItems(carts);

}

void DialogShowCarts::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{

    emit cartSelected (item->text());
    this->hide();

}

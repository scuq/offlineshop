#include "cartwidget.h"
#include "ui_cartwidget.h"
#include "QDebug";

CartWidget::CartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CartWidget)
{
    ui->setupUi(this);
}

CartWidget::~CartWidget()
{
    delete ui;
}

void CartWidget::setCustomerId(QString customerid)
{
    this->ui->lineEditCartCustimerId->setText(customerid);
}

void CartWidget::setCustomerName(QString customername)
{
    this->ui->lineEditCartCustomer->setText(customername);
}

void CartWidget::setCartName(QString cartname)
{
    this->ui->lineEditCartName->setText(cartname);
}

void CartWidget::setDate(QString date)
{
    this->ui->lineEditCartDate->setText(date);
}

void CartWidget::setModel(QSqlRelationalTableModel *model)
{
    this->ui->tableViewCart->setModel(model);
    this->ui->tableViewCart->resizeColumnsToContents();
    this->ui->tableViewCart->setColumnHidden(0,true);
}

QString CartWidget::getCartName()
{
    return this->ui->lineEditCartName->text();

}

QString CartWidget::getCustomerName()
{
    return this->ui->lineEditCartCustomer->text();
}

QString CartWidget::getDate()
{
    return this->ui->lineEditCartDate->text();
}

QString CartWidget::getCustomerId()
{
    return this->ui->lineEditCartCustimerId->text();
}


void CartWidget::on_lineEditCartName_textEdited(const QString &arg1)
{

}

void CartWidget::on_lineEditCartName_returnPressed()
{


}

void CartWidget::on_lineEditCartName_editingFinished()
{
     emit onCartNameChanged(this->ui->lineEditCartName->text());
}

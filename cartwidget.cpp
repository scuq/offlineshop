#include "cartwidget.h"
#include "ui_cartwidget.h"

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

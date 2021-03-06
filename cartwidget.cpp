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

void CartWidget::resizeColumns()
{
    this->ui->tableViewCart->resizeColumnsToContents();
}

void CartWidget::resizeRows()
{
    this->ui->tableViewCart->resizeRowsToContents();
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

int CartWidget::getSelectedRow()
{
    return this->ui->tableViewCart->selectionModel()->currentIndex().row();
}

void CartWidget::removeRow(int row)
{
    this->ui->tableViewCart->model()->removeRow(row);

}


void CartWidget::on_lineEditCartName_textEdited(const QString &arg1)
{

}

void CartWidget::on_lineEditCartName_returnPressed()
{


}

void CartWidget::on_lineEditCartName_editingFinished()
{
    // emit onCartNameChanged(this->ui->lineEditCartName->text());
}

void CartWidget::on_lineEditCartName_textChanged(const QString &arg1)
{
    emit onCartNameChanged(this->ui->lineEditCartName->text());
}

#include "dialogshowcustomer.h"
#include "ui_dialogshowcustomer.h"

DialogShowcustomer::DialogShowcustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShowcustomer)
{
    ui->setupUi(this);
    restoreGeometry(genericHelper::getGeometry("showcustomer").toByteArray());
}



DialogShowcustomer::~DialogShowcustomer()
{
    delete ui;
}

void DialogShowcustomer::setDialogShown()
{
    dialogShown = true;


}

bool DialogShowcustomer::getDialogShown()
{

    return dialogShown;
}

void DialogShowcustomer::setCustomerId(QString customerid)
{
    this->ui->lineEditCustomerId->setText(customerid);
}

void DialogShowcustomer::setCustomerName(QString customername)
{
    this->ui->lineEditCustomerName->setText(customername);
}

void DialogShowcustomer::setPhone(QString phone)
{
    this->ui->lineEditPhone->setText(phone);
}

void DialogShowcustomer::setEmail(QString email)
{
    this->ui->lineEditEmail->setText(email);
}

void DialogShowcustomer::setAddress(QString address)
{
    this->ui->lineEditAddress->setText(address);
}

void DialogShowcustomer::setZipcode(QString zipcode)
{
    this->ui->lineEditZipcode->setText(zipcode);
}

void DialogShowcustomer::setCountry(QString country)
{
    this->ui->lineEditCountry->setText(country);
}

void DialogShowcustomer::setInfo(QString info)
{
    this->ui->plainTextEditInfo->clear();
    this->ui->plainTextEditInfo->appendHtml(info);
}

void DialogShowcustomer::on_pushButtonClose_clicked()
{
    genericHelper::saveGeometry("showcustomer",saveGeometry());
    this->hide();
}

#include "dialogshowproduct.h"
#include "ui_dialogshowproduct.h"
#include "QDebug"

DialogShowproduct::DialogShowproduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShowproduct)
{
    ui->setupUi(this);


}

DialogShowproduct::~DialogShowproduct()
{
    delete ui;
}

void DialogShowproduct::setDialogShown()
{
    dialogShown = true;


}

bool DialogShowproduct::getDialogShown()
{

    return dialogShown;
}

void DialogShowproduct::setImage(QPixmap image)
{

if (!image.isNull() ) {
    this->ui->labelImage->setHidden(false);
    this->ui->labelImage->setPixmap(image);
} else {
    this->ui->labelImage->setHidden(true);
}

}

void DialogShowproduct::setProductId(QString productid)
{
    this->ui->lineEditProductId->setText(productid);
}

void DialogShowproduct::setProductName(QString productname)
{
    this->ui->lineEditProductName->setText(productname);
}

void DialogShowproduct::on_pushButtonClose_clicked()
{

    this->hide();
}

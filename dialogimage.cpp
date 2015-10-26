#include "dialogimage.h"
#include "ui_dialogimage.h"
#include "QDebug"

DialogImage::DialogImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImage)
{
    ui->setupUi(this);
}

DialogImage::~DialogImage()
{
    delete ui;
}

void DialogImage::setDialogShown()
{
    dialogShown = true;


}

bool DialogImage::getDialogShown()
{

    return dialogShown;
}

void DialogImage::setImage(QByteArray image)
{


    QPixmap pixmap = QPixmap();
    pixmap.loadFromData(image);
    qDebug() << pixmap;

    QGraphicsPixmapItem item(pixmap);
    QGraphicsScene scene;
    this->ui->graphicsView->setScene(&scene);
    scene.addItem(&item);
    this->ui->graphicsView->show();
}

#ifndef DIALOGSHOWPRODUCT_H
#define DIALOGSHOWPRODUCT_H

#include <QDialog>
#include <QGraphicsPixmapItem>
#include <QtAlgorithms>
#include "generichelper.h"

namespace Ui {
class DialogShowproduct;
}

class DialogShowproduct : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShowproduct(QWidget *parent = 0);
    ~DialogShowproduct();
    void setDialogShown();
    bool getDialogShown();
    void setImage(QPixmap image);
    void setProductId(QString productid);
    void setProductName(QString productname);


private slots:
    void on_pushButtonClose_clicked();

private:
    Ui::DialogShowproduct *ui;
    bool dialogShown;

};

#endif // DIALOGSHOWPRODUCT_H

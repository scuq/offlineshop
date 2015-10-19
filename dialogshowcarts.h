#ifndef DIALOGSHOWCARTS_H
#define DIALOGSHOWCARTS_H

#include <QDialog>
#include <QDebug>
#include <QListWidgetItem>

namespace Ui {
class DialogShowCarts;
}

class DialogShowCarts : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShowCarts(QWidget *parent = 0);
    ~DialogShowCarts();
    void setDialogShown();
    bool getDialogShown();
    void setCarts(QStringList carts);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::DialogShowCarts *ui;
    bool dialogShown;

signals:

    void cartSelected(QString);
};

#endif // DIALOGSHOWCARTS_H

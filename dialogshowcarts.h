#ifndef DIALOGSHOWCARTS_H
#define DIALOGSHOWCARTS_H

#include <QDialog>
#include <QDebug>
#include <QListWidgetItem>
#include "generichelper.h"

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
    void clearCarts();
    void addCarts(QString cart, QHash<QString,QString> cartinfo);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_treeWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::DialogShowCarts *ui;
    bool dialogShown;

signals:

    void cartSelected(QString);
};

#endif // DIALOGSHOWCARTS_H

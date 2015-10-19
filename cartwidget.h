#ifndef CARTWIDGET_H
#define CARTWIDGET_H

#include <QWidget>
#include <qsqlrelationaltablemodel.h>

namespace Ui {
class CartWidget;
}

class CartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CartWidget(QWidget *parent = 0);
    ~CartWidget();
    void setCustomerId(QString customerid);
    void setCustomerName(QString customername);
    void setCartName(QString cartname);
    void setDate(QString date);
    void setModel(QSqlRelationalTableModel *model);

private:
    Ui::CartWidget *ui;

};

#endif // CARTWIDGET_H

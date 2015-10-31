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
    void resizeColumns();
    void resizeRows();
    QString getCartName();
    QString getCustomerName();
    QString getDate();
    QString getCustomerId();

private slots:
    void on_lineEditCartName_textEdited(const QString &arg1);

    void on_lineEditCartName_returnPressed();

    void on_lineEditCartName_editingFinished();

    void on_lineEditCartName_textChanged(const QString &arg1);

private:
    Ui::CartWidget *ui;

signals:
    void onCartNameChanged(QString);
};

#endif // CARTWIDGET_H


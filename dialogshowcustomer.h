#ifndef DIALOGSHOWCUSTOMER_H
#define DIALOGSHOWCUSTOMER_H

#include <QDialog>

namespace Ui {
class DialogShowcustomer;
}

class DialogShowcustomer : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShowcustomer(QWidget *parent = 0);
    ~DialogShowcustomer();
    void setDialogShown();
    bool getDialogShown();
    void setCustomerId(QString customerid);
    void setCustomerName(QString customername);
    void setPhone(QString phone);
    void setEmail(QString email);
    void setAddress(QString address);
    void setZipcode(QString zipcode);
    void setCountry(QString country);
    void setInfo(QString info);

private slots:
    void on_pushButtonClose_clicked();

private:
    Ui::DialogShowcustomer *ui;
    bool dialogShown;
};

#endif // DIALOGSHOWCUSTOMER_H

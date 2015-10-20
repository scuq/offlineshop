#ifndef DIALOGOPTIONS_H
#define DIALOGOPTIONS_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "generichelper.h"

namespace Ui {
class DialogOptions;
}

class DialogOptions : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOptions(QWidget *parent = 0);
    ~DialogOptions();
    void setDialogShown();
    bool getDialogShown();
    void refreshUiData();

private slots:
    void on_pushButtonTemplateFileSelect_clicked();

    void on_pushButtonOk_clicked();

private:
    Ui::DialogOptions *ui;
    bool dialogShown;
};

#endif // DIALOGOPTIONS_H

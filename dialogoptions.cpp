#include "dialogoptions.h"
#include "ui_dialogoptions.h"

DialogOptions::DialogOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOptions)
{
    ui->setupUi(this);
}


DialogOptions::~DialogOptions()
{
    delete ui;
}

void DialogOptions::setDialogShown()
{
    dialogShown = true;
    this->refreshUiData();

}

bool DialogOptions::getDialogShown()
{
    this->refreshUiData();
    return dialogShown;
}

void DialogOptions::refreshUiData()
{

}

void DialogOptions::on_pushButtonTemplateFileSelect_clicked()
{
    bool ret = false;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Word XML Template"),"",
                                                      tr("Microsoft Word 2007/2010/2013 XML (*.docx)"));
      if (!fileName.isEmpty()) {

          //bool ret = osDatabase->open(fileName);

          if( ret == false) {
              QMessageBox::warning(this, genericHelper::getAppName(), tr("File cannot be opened: %1, Error %2").arg("").arg(""));
          } else {


            //  emit databaseLoaded ( );
              //genericHelper::addRecentFiles(fileName,maxRecentFiles);
          }
      }

}

void DialogOptions::on_pushButtonOk_clicked()
{

}

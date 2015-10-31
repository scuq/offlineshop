#include "dialogoptions.h"
#include "ui_dialogoptions.h"

DialogOptions::DialogOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOptions)
{
    ui->setupUi(this);
    restoreGeometry(genericHelper::getGeometry("options").toByteArray());

    this->ui->comboBoxLanguage->setCurrentText(genericHelper::getLang());

}


DialogOptions::~DialogOptions()
{
    delete ui;
}

void DialogOptions::setDialogShown()
{
    dialogShown = true;


}

bool DialogOptions::getDialogShown()
{
    this->refreshUiData();
    return dialogShown;
}

void DialogOptions::refreshUiData()
{
    this->ui->tableWidgetReplacmentVars->clear();
    QHash<QString,QString> replacementvars;

    replacementvars = genericHelper::getDocxReplacmentVariables();



    QListIterator<QString> itrvars (replacementvars.keys());

    while (itrvars.hasNext()) {


        QString current = itrvars.next();

        int insertRow = this->ui->tableWidgetReplacmentVars->rowCount();

        this->ui->tableWidgetReplacmentVars->insertRow(insertRow);

        QTableWidgetItem* newItemR = new QTableWidgetItem(current);
        QTableWidgetItem* newItemW = new QTableWidgetItem(replacementvars[current]);

        newItemR->setText(current);

        newItemW->setText(replacementvars[current]);

        this->ui->tableWidgetReplacmentVars->setItem(insertRow,0, newItemR);
        this->ui->tableWidgetReplacmentVars->setItem(insertRow,1, newItemW);

    }

    this->ui->lineEditTemplateFile->setText(genericHelper::getTemplateFile());





}

void DialogOptions::on_retranslate()
{

}

void DialogOptions::on_pushButtonTemplateFileSelect_clicked()
{
    bool ret = false;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Word XML Template"),"",
                                                      tr("Microsoft Word 2007/2010/2013 XML (*.docx)"));
      if (fileName.isEmpty()) {

              QMessageBox::warning(this, genericHelper::getAppName(), tr("File cannot be opened: %1, Error %2").arg("").arg(""));

      } else {
          this->ui->lineEditTemplateFile->setText(fileName);
      }

}

void DialogOptions::on_pushButtonOk_clicked()
{


    QHash<QString,QString> replacementvars;

    for (int i=0; i<this->ui->tableWidgetReplacmentVars->rowCount(); ++i)
    {
        replacementvars[this->ui->tableWidgetReplacmentVars->item(i, 0)->text()]=this->ui->tableWidgetReplacmentVars->item(i, 1)->text();
    }

    genericHelper::setDocxReplacmentVariables(replacementvars);

    genericHelper::setTemplateFile(this->ui->lineEditTemplateFile->text());

    if (this->ui->comboBoxLanguage->currentText() != "<default>") {
        genericHelper::setLang(this->ui->comboBoxLanguage->currentText());
    }



    genericHelper::saveGeometry("options",saveGeometry());
    this->hide();



}

void DialogOptions::on_pushButtonAdd_clicked()
{
    this->ui->tableWidgetReplacmentVars->insertRow(this->ui->tableWidgetReplacmentVars->rowCount());
}

void DialogOptions::on_comboBoxLanguage_currentTextChanged(const QString &arg1)
{

    if (arg1 != "<default>") {
        emit langChanged(arg1);
    }
}

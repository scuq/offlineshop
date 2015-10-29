#include "mycurrencycombodelegate.h"

MyCurrencyComboDelegate::MyCurrencyComboDelegate()
{

}

QWidget *MyCurrencyComboDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);

    editor->addItems(genericHelper::getCurrencies());



    return editor;
}

void MyCurrencyComboDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index,Qt::EditRole).toString();
    QComboBox *cmbbox = static_cast<QComboBox*>(editor);
    cmbbox->setCurrentText(value);
}

void MyCurrencyComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cmbbox = static_cast<QComboBox*>(editor);

    QString value = cmbbox->currentText();
    model->setData(index,value,Qt::EditRole);
}

void MyCurrencyComboDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}


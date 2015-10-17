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

}

void MyCurrencyComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void MyCurrencyComboDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}


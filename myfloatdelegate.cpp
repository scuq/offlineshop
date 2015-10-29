#include "myfloatdelegate.h"

#include <QDebug>

MyFloatDelegate::MyFloatDelegate()
{

}



QWidget *MyFloatDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(9999999);
    editor->setDecimals(2);

    editor->setSingleStep(0.50);






    return editor;
}

void MyFloatDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index,Qt::EditRole).toDouble();
    QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(editor);
    spinbox->setValue(value);


}

void MyFloatDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(editor);


    double value = spinbox->value();

    model->setData(index,value,Qt::EditRole);

}

void MyFloatDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}


#include "myfloatdelegate.h"

#include <QDebug>

MyFloatDelegate::MyFloatDelegate()
{

}



QWidget *MyFloatDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setMinimum(0.00);
    editor->setDecimals(2);
    editor->setSingleStep(1.00);



    return editor;
}

void MyFloatDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index,Qt::EditRole).toFloat();
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


#include "mynoeditdelegate.h"

MyNoEditDelegate::MyNoEditDelegate()
{

}

QWidget *MyNoEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return 0;
}

void MyNoEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void MyNoEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void MyNoEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}


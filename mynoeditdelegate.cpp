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

void MyNoEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 myOption = option;

    myOption.text = index.data().toString();
    myOption.displayAlignment = Qt::AlignCenter;

    myOption.backgroundBrush = (QBrush(QColor(255, 255, 242, 200)));


   //background-color: rgb(255, 255, 242);



    QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
}


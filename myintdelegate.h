#ifndef MYINTDELEGATE_H
#define MYINTDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QSpinBox>
#include <QModelIndex>

class MyIntDelegate : public QItemDelegate
{
public:
    MyIntDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;


};

#endif // MYINTDELEGATE_H

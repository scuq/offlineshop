#ifndef MYFLOATDELEGATE_H
#define MYFLOATDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QDoubleSpinBox>
#include <QModelIndex>

class MyFloatDelegate : public QItemDelegate
{
public:
    MyFloatDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;


};

#endif // MYFLOATDELEGATE_H

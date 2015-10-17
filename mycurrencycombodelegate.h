#ifndef MYCURRENCYCOMBODELEGATE_H
#define MYCURRENCYCOMBODELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QComboBox>
#include <QModelIndex>
#include <generichelper.h>


class MyCurrencyComboDelegate : public QItemDelegate
{
public:
    MyCurrencyComboDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // MYCURRENCYCOMBODELEGATE_H

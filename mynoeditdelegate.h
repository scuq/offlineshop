#ifndef MYNOEDITDELEGATE_H
#define MYNOEDITDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QLabel>
#include <QLineEdit>
#include <QModelIndex>
#include <generichelper.h>
#include <QPainter>
#include <QStylePainter>
#include <QApplication>
#include <QStyle>
#include <QUrl>
#include <QRegExpValidator>
#include <QMenu>
#include <QAction>
#include <QFileDialog>

class MyNoEditDelegate : public QItemDelegate
{
public:
    MyNoEditDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // MYNOEDITDELEGATE_H

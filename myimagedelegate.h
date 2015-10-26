#ifndef MYIMAGEDELEGATE_H
#define MYIMAGEDELEGATE_H

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

class MyImageDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    MyImageDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // MYIMAGEDELEGATE_H

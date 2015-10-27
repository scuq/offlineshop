#ifndef MYPHONELINEEDITDELEGATE_H
#define MYPHONELINEEDITDELEGATE_H


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


class MyPhoneLineEditDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    MyPhoneLineEditDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private slots:
    void checkInput(QString text);

private:

};

#endif // MYPHONELINEEDITDELEGATE_H

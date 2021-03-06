#ifndef ADVQSORTFILTERPROXYMODEL_H
#define ADVQSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QModelIndex>
#include <QColor>
#include <QBrush>
#include <QDebug>

class AdvQSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:

   AdvQSortFilterProxyModel(QObject* parent);
   QVariant data ( const QModelIndex & index, int role ) const;
   QVariant getColData(int keycol, QVariant key, int updatecol);


protected:
    bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const;



private:


};

#endif // ADVQSORTFILTERPROXYMODEL_H

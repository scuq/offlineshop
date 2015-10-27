#ifndef ADVQSORTFILTERPROXYMODELCUSTOMER_H
#define ADVQSORTFILTERPROXYMODELCUSTOMER_H



#include <QSortFilterProxyModel>
#include <QModelIndex>
#include <QColor>
#include <QBrush>
#include <QDebug>

class AdvQSortFilterProxyModelCustomer : public QSortFilterProxyModel
{
    Q_OBJECT
public:

   AdvQSortFilterProxyModelCustomer(QObject* parent);
   QVariant data ( const QModelIndex & index, int role ) const;
   QVariant getColData(int keycol, QVariant key, int updatecol);


protected:
    bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const;



private:


};

#endif // ADVQSORTFILTERPROXYMODELCUSTOMER_H

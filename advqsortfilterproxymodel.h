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


protected:


private:


};

#endif // ADVQSORTFILTERPROXYMODEL_H

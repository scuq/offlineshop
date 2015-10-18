#include "advqsortfilterproxymodel.h"

AdvQSortFilterProxyModel::AdvQSortFilterProxyModel(QObject *parent)
{

}

QVariant AdvQSortFilterProxyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::BackgroundRole ) {

        QBrush demonicBackground(QColor(255, 60, 43));
        QBrush evilBackground(QColor(255,123,71));
        QBrush unkownBackground(QColor(102, 191, 255));
        QBrush goodBackground(QColor(110, 255, 96));


        if (index.column() == 1) {
            if (index.data().toString() == "online") {
                return QVariant(goodBackground);
            } else {
                if (index.data().toString() == "hosting") {
                    return QVariant(unkownBackground);
                }
            }
        }

    }






    if ( role == Qt::TextAlignmentRole )
    {
        if (index.column() == 1) {
            return Qt::AlignVCenter | Qt::AlignHCenter;


        }
    }

    return QSortFilterProxyModel::data( index, role );
}

QVariant AdvQSortFilterProxyModel::getColData(int keycol, QVariant key, int updatecol)
{

    QVariant data = "";

    for(int i = 0; i<this->sourceModel()->rowCount(); ++i)
    {
        QModelIndex key_index = this->sourceModel()->index(i,keycol);
        QModelIndex update_index = this->sourceModel()->index(i,updatecol);

        if ( this->sourceModel()->itemData(key_index)[0].toString() == key.toString() )  {

            data = this->sourceModel()->data(update_index,0);
        }
    }

    return data;


}

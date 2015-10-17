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

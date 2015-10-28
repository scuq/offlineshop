#include "myimagedelegate.h"

MyImageDelegate::MyImageDelegate()
{

}

QWidget *MyImageDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //QString fileName = QFileDialog::getOpenFileName(this, tr("Add receipt"),"",
      //                                                 tr("Image (*.jpg *.png *.bmp)"));
    QString filters("Image (*.jpg *.png)");

    QFileDialog *editor = new QFileDialog(parent);
    editor->setFileMode(QFileDialog::AnyFile);
    editor->setFilter(QDir::Files);
    editor->setNameFilter(filters);
    editor->setModal(true);

    return editor;

}

void MyImageDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //QVariant value = index.model()->data(index,Qt::EditRole);
    //qDebug() << value;

    //QFileDialog *filedia = static_cast<QFileDialog*>(editor);

    //model->setData(index,filedia->selectedFiles()[0]);


}

void MyImageDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QFileDialog *filedia = static_cast<QFileDialog*>(editor);

    if (filedia->selectedFiles().length() > 0)    {
    QFile file(filedia->selectedFiles()[0]);

    if (! file.open(QIODevice::ReadOnly)) return;

    QByteArray byteArray = file.readAll();


    model->setData(index,byteArray);
    }
}

void MyImageDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  editor->setGeometry(option.rect);
}


void MyImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
     QByteArray value = index.model()->data(index,Qt::DisplayRole).toByteArray();
     if (!value.isNull()) {
         QPixmap pixmap = QPixmap();
         pixmap.loadFromData(value);


         painter->save();

         painter->drawPixmap(option.rect.x(),option.rect.y(),option.rect.width(),option.rect.height(),  pixmap.scaled(60,60,Qt::KeepAspectRatio));

         painter->restore();
     }
}



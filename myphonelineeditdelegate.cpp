#include "myphonelineeditdelegate.h"

MyPhoneLineEditDelegate::MyPhoneLineEditDelegate()
{

}

QWidget *MyPhoneLineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);



    QRegExp regexPhone("^([0-9\(\)\/\+ \-]*)$" );


    QObject::connect(editor, SIGNAL(textChanged(QString)), this, SLOT(checkInput(QString)));
    QRegExpValidator *phoneval = new QRegExpValidator(regexPhone, parent);
    editor->setValidator(phoneval);


    return editor;
}

void MyPhoneLineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index,Qt::EditRole).toString();
    QLineEdit *lineedit = static_cast<QLineEdit*>(editor);
    lineedit->setText(value);
}

void MyPhoneLineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineedit = static_cast<QLineEdit*>(editor);

    QString value = lineedit->text();
    model->setData(index,value,Qt::EditRole);
}

void MyPhoneLineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void MyPhoneLineEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

     QString value = index.model()->data(index,Qt::DisplayRole).toString();

     painter->save();

     QLabel *ql = new QLabel();


    ql->setTextFormat(Qt::RichText);
    ql->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ql->setAlignment(Qt::AlignCenter);

    ql->setText( "<a href=\"callto:"+value+"\" target=\"_top\">"+value+"</a>"  );

    ql->render(painter, painter->deviceTransform().map(QPoint(option.rect.left()+5,option.rect.center().y()-10)));

    painter->restore();
}

void MyPhoneLineEditDelegate::checkInput(QString text)
{
    QLineEdit *lineedit = static_cast<QLineEdit*>(this->sender());

    QString color;

    color = "#f6989d";

   if (lineedit->hasAcceptableInput() == true) {
        color = "#c4df9b" ;

   }


    lineedit->setStyleSheet("QLineEdit { background-color: "+color+" }");
}




#include "myemaillineeditdelegate.h"

MyEmailLineEditDelegate::MyEmailLineEditDelegate()
{



}

QWidget *MyEmailLineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);


    QRegExp regexEmail("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$" );



    QObject::connect(editor, SIGNAL(textChanged(QString)), this, SLOT(checkInput(QString)));
    QRegExpValidator *emailval = new QRegExpValidator(regexEmail, parent);
    editor->setValidator(emailval);


    return editor;
}

void MyEmailLineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index,Qt::EditRole).toString();
    QLineEdit *lineedit = static_cast<QLineEdit*>(editor);
    lineedit->setText(value);
}

void MyEmailLineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineedit = static_cast<QLineEdit*>(editor);

    QString value = lineedit->text();
    model->setData(index,value,Qt::EditRole);
}

void MyEmailLineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void MyEmailLineEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

     QString value = index.model()->data(index,Qt::DisplayRole).toString();

     painter->save();

     QLabel *ql = new QLabel();


    ql->setTextFormat(Qt::RichText);
    ql->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ql->setAlignment(Qt::AlignCenter);

    ql->setText( "<a href=\"mailto:"+value+"\" target=\"_top\">"+value+"</a>"  );

    ql->render(painter, painter->deviceTransform().map(QPoint(option.rect.left()+5,option.rect.center().y()-10)));

    painter->restore();
}

void MyEmailLineEditDelegate::checkInput(QString text)
{
    QLineEdit *lineedit = static_cast<QLineEdit*>(this->sender());

    QString color;

    color = "#f6989d";

   if (lineedit->hasAcceptableInput() == true) {
        color = "#c4df9b" ;

   }


    lineedit->setStyleSheet("QLineEdit { background-color: "+color+" }");
}






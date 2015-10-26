#ifndef DIALOGIMAGE_H
#define DIALOGIMAGE_H

#include <QDialog>
#include <QGraphicsPixmapItem>

namespace Ui {
class DialogImage;
}

class DialogImage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogImage(QWidget *parent = 0);
    ~DialogImage();
    void setDialogShown();
    bool getDialogShown();
    void setImage(QByteArray image);

private:
    Ui::DialogImage *ui;
    bool dialogShown;
};

#endif // DIALOGIMAGE_H

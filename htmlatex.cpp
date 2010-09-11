#include "htmlatex.h"
#include "ui_htmlatex.h"

#include <QPainter>
#include <QRectF>

htmlatex::htmlatex(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::htmlatex)
{
    ui->setupUi(this);
};
htmlatex::~htmlatex()
{
    delete ui;
};
void htmlatex::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
};
void htmlatex::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    QRectF rect = QRectF(this->width() / 4, this->height() / 4, this->width() / 2, this->height() / 2);
    painter.drawRoundedRect(rect, qreal(2.5), qreal(2.5), Qt::RelativeSize);
    painter.setPen(Qt::red);
    painter.drawText(rect, "Like it says in a book:\nWe're blessed and cursed.", QTextOption(Qt::AlignCenter));
};

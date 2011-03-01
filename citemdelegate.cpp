#include "citemdelegate.h"

CItemDelegate::CItemDelegate(CModel* model, QObject* parent)
    : QItemDelegate(parent)
{
    this->model = model;
    this->colorFocusLine = QColor(0, 255, 255, 255);
    this->colorFocusBackground = QColor(180, 180, 180, 255);
    this->colorMarked = QColor(200, 0, 0, 255);
    this->color = QColor(0, 0, 0, 255);
    this->colorLayer0 = QColor(75,86, 32, 255);
    this->colorLayer1 = QColor(0, 0, 255, 255);
};
void CItemDelegate::setColorFocusLine(QColor color)
{
    this->colorFocusLine = color;
};
QColor CItemDelegate::getColorFocusLine() const
{
    return this->colorFocusLine;
};
void CItemDelegate::setColorFocusBackground(QColor color)
{
    this->colorFocusBackground = color;
};
QColor CItemDelegate::getColorFocusBackground() const
{
    return this->colorFocusBackground;
};
void CItemDelegate::setColorMarked(QColor color)
{
    this->colorMarked = color;
};
QColor CItemDelegate::getColorMarked() const
{
    return this->colorMarked;
};
void CItemDelegate::setColor(QColor color)
{
    this->color = color;
};
QColor CItemDelegate::getColor() const
{
    return this->color;
};
void CItemDelegate::setColorLayer0(QColor color)
{
    this->colorLayer0 = color;
};
QColor CItemDelegate::getColorLayer0() const
{
    return this->colorLayer0;
};
void CItemDelegate::setColorLayer1(QColor color)
{
    this->colorLayer1 = color;
};
QColor CItemDelegate::getColorLayer1() const
{
    return this->colorLayer1;
};
void CItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const
{
    painter->save();
    QStyleOptionViewItem opt = option;
    opt.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
    CNode* node = model->nodeFromIndex(index);
    QString text = node->name() + " (" + QString::number(node->layer()) + ")";
    painter->setPen(color);
    if (node->content() != "")
        text += ": " + node->content();
    // an item of the treeview is selected
    if (option.state & QStyle::State_Selected)
    {
        painter->save();
        painter->setBrush(colorFocusBackground);
        painter->fillRect(QRect(opt.rect.x(), opt.rect.y(), opt.rect.width() - 1, opt.rect.height() - 1), Qt::SolidPattern);
        painter->setPen(QPen(QBrush(colorFocusLine, Qt::SolidPattern), 1.0, Qt::DashLine, Qt::RoundCap, Qt::BevelJoin));
        painter->drawRect(QRect(opt.rect.x(), opt.rect.y(), opt.rect.width() - 1, opt.rect.height() - 1));
        painter->restore();
    }
    if ((node->layer() % 2) == 0)
        painter->setPen(colorLayer0);
    else if ((node->layer() % 2) == 1)
        painter->setPen(colorLayer1);
    // determine icon size
    //int size = opt.rect.height() - 2;
    //painter->drawText(QRect(opt.rect.x() + size + 4, opt.rect.y(), opt.rect.width(), opt.rect.height()), text, QTextOption(Qt::AlignLeft|Qt::AlignVCenter));
    painter->drawText(QRect(opt.rect.x(), opt.rect.y(), opt.rect.width(), opt.rect.height()), text, QTextOption(Qt::AlignLeft|Qt::AlignVCenter));
    painter->restore();
};

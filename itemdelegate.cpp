#include "itemdelegate.h"

ItemDelegate::ItemDelegate(Model* model, QObject* parent)
    : QItemDelegate(parent)
{
    this->model = model;
    this->colorFocusLine = QColor(220, 220, 220, 255);
    this->colorFocusBackground = QColor(240, 240, 240, 255);
    this->colorMarked = QColor(200, 0, 0, 255);
    this->color = QColor(0, 0, 0, 255);
    this->colorLayer0 = QColor(30,86, 45, 255);
    this->colorLayer1 = QColor(0, 0, 255, 255);
};
void ItemDelegate::setColorFocusLine(QColor color)
{
    this->colorFocusLine = color;
};
QColor ItemDelegate::getColorFocusLine() const
{
    return this->colorFocusLine;
};
void ItemDelegate::setColorFocusBackground(QColor color)
{
    this->colorFocusBackground = color;
};
QColor ItemDelegate::getColorFocusBackground() const
{
    return this->colorFocusBackground;
};
void ItemDelegate::setColorMarked(QColor color)
{
    this->colorMarked = color;
};
QColor ItemDelegate::getColorMarked() const
{
    return this->colorMarked;
};
void ItemDelegate::setColor(QColor color)
{
    this->color = color;
};
QColor ItemDelegate::getColor() const
{
    return this->color;
};
void ItemDelegate::setColorLayer0(QColor color)
{
    this->colorLayer0 = color;
};
QColor ItemDelegate::getColorLayer0() const
{
    return this->colorLayer0;
};
void ItemDelegate::setColorLayer1(QColor color)
{
    this->colorLayer1 = color;
};
QColor ItemDelegate::getColorLayer1() const
{
    return this->colorLayer1;
};
void ItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const
{
    // stores the current state of the painter
    painter->save();
    QStyleOptionViewItem opt = option;
    opt.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
    Node* node = model->nodeFromIndex(index);
    QString text = node->getName() + " (" + QString::number(node->getLayer()) + ")";
    painter->setPen(color);
    if (node->getContent() != "")
        text += ": " + node->getContent();
    // an item of the treeview is selected
    if (option.state & QStyle::State_Selected)
    {
        // stores the current state of the painter
        painter->save();
        painter->setBrush(colorFocusBackground);
        painter->fillRect(QRect(opt.rect.x(), opt.rect.y(), opt.rect.width() - 1, opt.rect.height() - 1), Qt::SolidPattern);
        painter->setPen(QPen(QBrush(colorFocusLine, Qt::SolidPattern), 1.0, Qt::DashLine, Qt::RoundCap, Qt::BevelJoin));
        painter->drawRect(QRect(opt.rect.x(), opt.rect.y(), opt.rect.width() - 1, opt.rect.height() - 1));
        // restores the stored state of the painter
        painter->restore();
    }
    if ((node->getLayer() % 2) == 0)
        painter->setPen(colorLayer0);
    else if ((node->getLayer() % 2) == 1)
        painter->setPen(colorLayer1);
    painter->drawText(QRect(opt.rect.x(), opt.rect.y(), opt.rect.width(), opt.rect.height()), text, QTextOption(Qt::AlignLeft|Qt::AlignVCenter));
    // restores the initially stored state of the painter
    painter->restore();
};

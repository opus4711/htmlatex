#ifndef CITEMDELEGATE_H
#define CITEMDELEGATE_H

#include "cmodel.h"
#include <QItemDelegate>
#include <QPainter>
#include <QPixmap>
#include <QBrush>

class CItemDelegate : public QItemDelegate
{
    Q_OBJECT
private:
    CModel* model;
    QColor colorFocusLine;
    QColor colorFocusBackground;
    QColor colorMarked;
    QColor color;
    QColor colorLayer0;
    QColor colorLayer1;
public:
    void setColorFocusLine(QColor color);
    QColor getColorFocusLine() const;
    void setColorFocusBackground(QColor color);
    QColor getColorFocusBackground() const;
    void setColorMarked(QColor color);
    QColor getColorMarked() const;
    void setColor(QColor color);
    QColor getColor() const;
    void setColorLayer0(QColor color);
    QColor getColorLayer0() const;
    void setColorLayer1(QColor color);
    QColor getColorLayer1() const;
    void paint(QPainter* painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    // Constructor
    CItemDelegate(CModel* model = 0, QObject* parent = 0);
};

#endif // CITEMDELEGATE_H

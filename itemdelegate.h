#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include "model.h"
#include <QItemDelegate>
#include <QPainter>
#include <QPixmap>
#include <QBrush>

/** This class is derived from the QItemDelegate class. In this application its
    purpose is to control how the mainWindow's treeView displays data. The paint()
    method influences the drawing of the underlying widget directly. For further
    information look up QItemDelegate and QTreeView in the Qt documentation.
    @author Bjoern
  */
class ItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    /** This is the only constructor.
        @param <model> is the data structure which serves the treeView of the
        mainWindow as data source. Because this class controls the way how data is
        actually drawn on the widget it needs access to the tree structure as well.
        @param <parent> may be specified to take advantage of Qt's destructor
        chaining mechanism which prevents memory leaks effectivly.
        @author Bjoern
      */
    ItemDelegate(Model* model = 0, QObject* parent = 0);
private:
    /** The model is the data source of the mainWindow's treeView. The Model class
        is derived from the abstract class QAbstractItemModel and provides the
        functionality that a QTreeView object demands in order to display data.
        @author Bjoern
      */
    Model* model;
    /** This is the outline color of the selected node.
        @author Bjoern
      */
    QColor colorFocusLine;
    /** This is the background color of the selected node.
        @author Bjoern
      */
    QColor colorFocusBackground;
    /** This is the color of a marked node.
        @author Bjoern
      */
    QColor colorMarked;
    /** This is the text color.
        @author Bjoern
      */
    QColor color;
    /** This is the text color of nodes whose _layer number is even.
        @author Bjoern
      */
    QColor colorLayer0;
    /** This is the text color of nodes whose _layer number is uneven.
        @author Bjoern
      */
    QColor colorLayer1;
public:
    /** This method sets the outline color of the selected node.
        @author Bjoern
      */
    void setColorFocusLine(QColor color);
    /** This method returns the outline color of the selected node.
        @author Bjoern
      */
    QColor getColorFocusLine() const;
    /** This method sets the background color of the selected node.
        @author Bjoern
      */
    void setColorFocusBackground(QColor color);
    /** This method returns the background color of the selected node.
        @author Bjoern
      */
    QColor getColorFocusBackground() const;
    /** This method sets the color of a marked node.
        @author Bjoern
      */
    void setColorMarked(QColor color);
    /** This method returns the color of a marked node.
        @author Bjoern
      */
    QColor getColorMarked() const;
    /** This method sets the text color.
        @author Bjoern
      */
    void setColor(QColor color);
    /** This method returns the text color.
        @author Bjoern
      */
    QColor getColor() const;
    /** This method sets the text color of nodes whose _layer number is even.
        @author Bjoern
      */
    void setColorLayer0(QColor color);
    /** This method returns the text color of nodes whose _layer number is even.
        @author Bjoern
      */
    QColor getColorLayer0() const;
    /** This method sets the text color of nodes whose _layer number is uneven.
        @author Bjoern
      */
    void setColorLayer1(QColor color);
    /** This method returns the text color of nodes whose _layer number is uneven.
        @author Bjoern
      */
    QColor getColorLayer1() const;
    /** This method draws the data on the underlying mainWindow's treeView.
        @param <painter> is a pointer which allows drawing on the mainWindow's
        treeView.
        @param <option> holds various kinds of information such as the coordinates
        and size of the rectangle on which the node data is supposed to be drawn.
        It also provides information whether or not the currently drawn node is
        selected. Notice that this method is called for each node of the
        mainWindow's treeView every time the treeView is repainted what can be
        caused be various events such as resizing the widget.
        @param <index> is the index of the currently drawn node. Using the
        underlying model data structure the node can be identified and accessed
        by means of the given index.
        @author Bjoern
      */
    void paint(QPainter* painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
};

#endif // ITEMDELEGATE_H

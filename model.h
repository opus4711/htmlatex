#ifndef MODEL_H
#define MODEL_H

#include "node.h"
#include <QAbstractItemModel>

/** This class is derived from the QAbstractItemModel. It serves the mainWindow's
    treeVoew as data source.
    @author Bjoern
  */
class Model : public QAbstractItemModel
{
public:
    /** This is the only constructor.
        @author Bjoern
      */
    Model(QObject* parent = 0);
    /** This is the only destructor. It deletes the application's internal tree
        structure by deleting the _root node which starts a destructor chain.
        @author Bjoern
      */
    ~Model();
private:
    /** This is the root node of the application's internal tree structure.
        @author Bjoern
      */
    Node* _root;
public:
    /** When a node of the mainWindow's treeView is selected the treeView's method
        "currentIndex()" returns a QModelIndex object. The nodeFromIndex() method
        of this class returns the Node object of the application's internal tree
        structure which corresponds to that given QModelIndex.
        @author Bjoern
      */
    Node* nodeFromIndex(const QModelIndex &index) const;
    /** This method sets the root node of the application's internal tree
        structure.
        @param <node> is a Node object.
        @author Bjoern
      */
    void setRootNode(Node* node);
    /** This method returns the root node of the application's internal tree
        structure.
        @author Bjoern
      */
    Node* root() const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /** This method is called by the mainWindow when a node is removed from the
        treeView. The treeView repaints the visible items.
        @author Bjoern
      */
    void refresh();
};

#endif // MODEL_H

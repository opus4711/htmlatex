#ifndef MODEL_H
#define MODEL_H

#include "node.h"
#include <QAbstractItemModel>

class Model : public QAbstractItemModel
{
private:
    Node* _root;
public:
    Node* nodeFromIndex(const QModelIndex &index) const;
    void setRootNode(Node* node);
    Node* root() const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void refresh();
    /** Constructor */
    Model(QObject* parent = 0);
    ~Model();
};

#endif // MODEL_H

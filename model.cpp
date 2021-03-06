#include "model.h"

Model::Model(QObject* parent) : QAbstractItemModel(parent), _root(0)
{
};
Model::~Model()
{
    delete _root;
};
void Model::setRootNode(Node* node)
{
    if (_root != 0)
        delete _root;
    _root = node;
    // reset() notifies the treeView to refetch data for visible items
    reset();
};
QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
    if (!_root
        || (row < 0)
        || (column < 0))
        return QModelIndex();
    Node* parentNode = nodeFromIndex(parent);
    Node* childNode = parentNode->childAt(row);
    if (!childNode)
        return QModelIndex();
    return createIndex(row, column, childNode);
};
Node* Model::nodeFromIndex(const QModelIndex &index) const
{
    // cast the index's void* to a Node*
    if (index.isValid())
        return static_cast<Node*>(index.internalPointer());
    // In a model the root node is represented by an invalid index.
    return _root;
};
int Model::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;
    Node *parentNode = nodeFromIndex(parent);
    if (!parentNode)
        return 0;
    return parentNode->getCount();
};
int Model::columnCount(const QModelIndex &parent) const
{
    // just one column meets our needs
    return 1;
};
QModelIndex Model::parent(const QModelIndex &child) const
{
    Node* node = nodeFromIndex(child);
    if (!node)
        return QModelIndex();
    Node* parentNode = node->getParent();
    if (!parentNode)
        return QModelIndex();
    Node* grandparentNode = parentNode->getParent();
    if (!grandparentNode)
        return QModelIndex();
    int row = grandparentNode->indexOf(parentNode);
    return createIndex(row, 0, parentNode);
};
QVariant Model::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    Node* node = nodeFromIndex(index);
    if (!node)
        return QVariant();
    return node->getName() + ": " + node->getContent();
};
QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
};
Node* Model::root() const
{
    return this->_root;
};
void Model::refresh()
{
    reset();
};

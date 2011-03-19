#include "cmodel.h"

CModel::CModel(QObject* parent) : QAbstractItemModel(parent), _root(0)
{
};
CModel::~CModel()
{
    delete _root;
};
void CModel::setRootNode(CNode* node)
{
    delete _root;
    _root = node;
    // reset() notifies the views to refetch data for visible items
    reset();
};
QModelIndex CModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!_root
        || (row < 0)
        || (column < 0))
        return QModelIndex();
    CNode* parentNode = nodeFromIndex(parent);
    CNode* childNode = parentNode->childAt(row);
    if (!childNode)
        return QModelIndex();
    return createIndex(row, column, childNode);
};
CNode* CModel::nodeFromIndex(const QModelIndex &index) const
{
    // cast the index's void* to a CNode*
    if (index.isValid())
        return static_cast<CNode*>(index.internalPointer());
    // In a model the root node is represented by an invalid index.
    return _root;
};
int CModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;
    CNode *parentNode = nodeFromIndex(parent);
    if (!parentNode)
        return 0;
    return parentNode->getCount();
};
int CModel::columnCount(const QModelIndex &parent) const
{
    // just one column meets our needs
    return 1;
};
QModelIndex CModel::parent(const QModelIndex &child) const
{
    CNode* node = nodeFromIndex(child);
    if (!node)
        return QModelIndex();
    CNode* parentNode = node->getParent();
    if (!parentNode)
        return QModelIndex();
    CNode* grandparentNode = parentNode->getParent();
    if (!grandparentNode)
        return QModelIndex();
    int row = grandparentNode->indexOf(parentNode);
    return createIndex(row, 0, parentNode);
};
QVariant CModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    CNode* node = nodeFromIndex(index);
    if (!node)
        return QVariant();
    return node->getName() + ": " + node->getContent();
};
QVariant CModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
};
CNode* CModel::root() const
{
    return this->_root;
};
void CModel::refresh()
{
    reset();
};

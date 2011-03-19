#ifndef CCUSTOMMODEL_H
#define CCUSTOMMODEL_H

#include "cnode.h"
#include <QAbstractItemModel>

class CModel : public QAbstractItemModel
{
private:
    CNode* _root;
public:
    CNode* nodeFromIndex(const QModelIndex &index) const;
    void setRootNode(CNode* node);
    CNode* root() const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void refresh();
    // Constructor / Destructor
    CModel(QObject* parent = 0);
    ~CModel();
};

#endif // CCUSTOMMODEL_H

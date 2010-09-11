#include "cnode.h"

CNode::CNode(CNode* parent) : _parent(parent)
{
    instCount++;
    this->_id = instCount;
};
CNode::~CNode()
{
    qDeleteAll(children);
};
int CNode::instCount = 0;
QString CNode::name() const
{
    return this->_name;
};
QString CNode::reference() const
{
    return this->_reference;
};
QString CNode::fontData() const
{
    return this->_fontData;
};
CNode* CNode::childAt(int index) const
{
    return children.value(index);
};
int CNode::count() const
{
    return children.count();
};
void CNode::setParent(CNode* parent)
{
    this->_parent = parent;
};
int CNode::indexOf(CNode* node) const
{
    return children.indexOf(node);
};
void CNode::addChildren(QList<CNode*> nodes)
{
    for (int i = 0; i < nodes.count(); i++)
    {
        if (!containsChild(nodes.at(i)))
        {
            nodes.at(i)->setParent(this);
            children.append(nodes.at(i));
        }
    }
};
void CNode::addChild(CNode* node)
{
    if (!containsChild(node))
    {
        node->setParent(this);
        children.append(node);
    }
};
bool CNode::containsChild(CNode* node) const
{
    bool result = false;
    for (int i = 0; i < count(); i++)
    {
        if (children.at(i)->_id == node->_id)
        {
            result = true;
            break;
        }
    }
    return result;
};
void CNode::removeChild(CNode* node)
{
    if (children.removeOne(node))
        delete node;
};

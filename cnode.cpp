#include "cnode.h"

CNode::CNode(const CNode& node)
{
    _instCount++;
    this->_id = _instCount;
    this->_name = node.getName();
    this->_content = node.getContent();
    this->_layer = node.getLayer();
    this->_parent = node.getParent();
    this->_treeLevel = node.getTreeLevel();
    // add child nodes
    for (int i = 0; i < node.getCount(); i++)
        this->addChild(new CNode(*node.childAt(i)));
    // add attributes
    QList<QString> keys = node.getAttributes().keys();
    for (int i = 0; i < keys.count(); i++)
        this->addAttribute(keys.at(i), node.getAttributes()[keys.at(i)]);
};
CNode::CNode(CNode* parent, QString name, qint64 layer) : _layer(layer),
    _name(name), _content(""), _parent(parent), _cursor(0)
{
    if (_parent == 0)
        _treeNodeCount = 0;
    else
        _treeNodeCount++;
    _instCount++;
    if (layer > _treeLevel)
        _treeLevel = layer;
    this->_id = _instCount;
    this->_children = QList<CNode*>();
    this->_attributes = QMap<QString, QString>();
};
CNode::~CNode()
{
    qDeleteAll(_children);
};
qint64 CNode::_instCount = 0;
qint64 CNode::_treeLevel = 0;
qint64 CNode::_treeNodeCount;
qint64 CNode::getTreeLevel() const
{
    return this->_treeLevel;
};
qint64 CNode::getTreeNodeCount() const
{
    return this->_treeNodeCount;
};
qint64 CNode::getID() const
{
    return this->_id;
};
qint64 CNode::getLayer() const
{
    return this->_layer;
};
QString CNode::getName() const
{
    return this->_name;
};
void CNode::setName(QString name)
{
    this->_name = name;
};
QString CNode::getContent() const
{
    return this->_content;
};
void CNode::setContent(QString content)
{
    this->_content = content;
};
CNode* CNode::getParent() const
{
    if (_parent != 0)
        return this->_parent;
    return 0;
};
void CNode::setParent(CNode* parent)
{
    this->_parent = parent;
};
int CNode::getCount() const
{
    return _children.count();
};
bool CNode::containsChild(CNode* node) const
{
    bool result = false;
    for (int i = 0; i < _children.count(); i++)
    {
        if (_children.at(i)->_id == node->_id)
        {
            result = true;
            break;
        }
    }
    return result;
};
CNode* CNode::childAt(int index) const
{
    return _children.value(index);
};
CNode* CNode::nextChild()
{
    if (_cursor < _children.count())
    {
        _cursor++;
        return _children.at(_cursor - 1);
    }
    return 0;
};
CNode* CNode::firstChild()
{
    _cursor = 0;
    if (_children.count() > 0)
        return _children.at(_cursor);
    return 0;
};
CNode* CNode::lastChild()
{
    if (_children.count() > 0)
    {
        _cursor = _children.count() - 1;
        return _children.at(_cursor);
    }
    return 0;
};
void CNode::addChildren(QList<CNode*> nodes)
{
    for (int i = 0; i < nodes.count(); i++)
    {
        if (!containsChild(nodes.at(i)))
        {
            nodes.at(i)->setParent(this);
            _children.append(nodes.at(i));
        }
    }
};
void CNode::addChild(CNode* node)
{
    if (node != 0)
    {
        if (!containsChild(node))
        {
            node->setParent(this);
            _children.append(node);
        }
    }
};
void CNode::removeChild(CNode* node)
{
    if (_children.removeOne(node))
    {
        _cursor = -1;
        delete node;
    }
};
int CNode::indexOf(CNode* node) const
{
    return _children.indexOf(node);
};
QMap<QString, QString> CNode::getAttributes() const
{
    return this->_attributes;
};
void CNode::addAttribute(QString key, QString value)
{
    this->_attributes[key] = value;
};

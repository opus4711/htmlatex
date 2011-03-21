#include "node.h"

Node::Node(const Node& node)
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
        this->addChild(new Node(*node.childAt(i)));
    // add attributes
    QList<QString> keys = node.getAttributes().keys();
    for (int i = 0; i < keys.count(); i++)
        this->addAttribute(keys.at(i), node.getAttributes()[keys.at(i)]);
};
Node::Node(Node* parent, QString name, qint64 layer) : _layer(layer),
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
    this->_children = QList<Node*>();
    this->_attributes = QMap<QString, QString>();
};
Node::~Node()
{
    qDeleteAll(_children);
};
qint64 Node::_instCount = 0;
qint64 Node::_treeLevel = 0;
qint64 Node::_treeNodeCount;
qint64 Node::getTreeLevel() const
{
    return this->_treeLevel;
};
qint64 Node::getTreeNodeCount() const
{
    return this->_treeNodeCount;
};
qint64 Node::getID() const
{
    return this->_id;
};
qint64 Node::getLayer() const
{
    return this->_layer;
};
QString Node::getName() const
{
    return this->_name;
};
void Node::setName(QString name)
{
    this->_name = name;
};
QString Node::getContent() const
{
    return this->_content;
};
void Node::setContent(QString content)
{
    this->_content = content;
};
Node* Node::getParent() const
{
    if (_parent != 0)
        return this->_parent;
    return 0;
};
void Node::setParent(Node* parent)
{
    this->_parent = parent;
};
int Node::getCount() const
{
    return _children.count();
};
bool Node::containsChild(Node* node) const
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
Node* Node::childAt(int index) const
{
    return _children.value(index);
};
Node* Node::nextChild()
{
    if (_cursor < _children.count())
    {
        _cursor++;
        return _children.at(_cursor - 1);
    }
    return 0;
};
Node* Node::firstChild()
{
    _cursor = 0;
    if (_children.count() > 0)
        return _children.at(_cursor);
    return 0;
};
Node* Node::lastChild()
{
    if (_children.count() > 0)
    {
        _cursor = _children.count() - 1;
        return _children.at(_cursor);
    }
    return 0;
};
void Node::addChildren(QList<Node*> nodes)
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
void Node::addChild(Node* node)
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
void Node::removeChild(Node* node)
{
    if (_children.removeOne(node))
    {
        _cursor = -1;
        delete node;
    }
};
int Node::indexOf(Node* node) const
{
    return _children.indexOf(node);
};
QMap<QString, QString> Node::getAttributes() const
{
    return this->_attributes;
};
void Node::addAttribute(QString key, QString value)
{
    this->_attributes[key] = value;
};

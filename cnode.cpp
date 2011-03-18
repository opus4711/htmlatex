#include "cnode.h"

/** Copy constructor
  */
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
/**
 * Constructs a new object.
 * @param parent Initialiazes the object with the given CNode-object as its parent.
 * @author Bjoern Kaiser
 */
CNode::CNode(CNode* parent, QString name, qint64 layer) : _parent(parent),
    _layer(layer), _name(name), _content(""), _cursor(0)
{
    _instCount++;
    if (layer > _treeLevel)
        _treeLevel = layer;
    this->_id = _instCount;
    this->_children = QList<CNode*>();
    this->_attributes = QMap<QString, QString>();
};
/**
 * This destructor deletes all child nodes by means of Qt's generic algorithms.
 * @author Bjoern Kaiser
 */
CNode::~CNode()
{
    qDeleteAll(_children);
};
/**
 * This class instance counter is used to assign unique ID-numbers to each class instance.
 * @author Bjoern Kaiser
 */
qint64 CNode::_instCount = 0;
qint64 CNode::_treeLevel = 0;
/**
  Returns the greatest distance of a node to the root node.
  */
qint64 CNode::getTreeLevel() const
{
    return this->_treeLevel;
};
/**
 * Returns the node's unique ID.
 * @author Bjoern Kaiser
 */
qint64 CNode::getID() const
{
    return this->_id;
};
/**
  * Returns the layer number of the node. The layer number is the distance to the
  * root node of the tree.
  * @author Bjoern Kaiser
  */
qint64 CNode::getLayer() const
{
    return this->_layer;
};
/**
 * Returns the node's name.
 * @author Bjoern Kaiser
 */
QString CNode::getName() const
{
    return this->_name;
};
/**
 * Returns the node's text content.
 * @author Bjoern Kaiser
 */
QString CNode::getContent() const
{
    return this->_content;
};
/**
 * Returns node's attributes (such as size, width, align etc.).
 * @author Bjoern Kaiser
 */
QMap<QString, QString> CNode::getAttributes() const
{
    return this->_attributes;
};
/**
 * Sets the node's name.
 * @author Bjoern Kaiser
 */
void CNode::setName(QString name)
{
    this->_name = name;
};
/**
 * Sets the node's content.
 * @author Bjoern Kaiser
 */
void CNode::setContent(QString content)
{
    this->_content = content;
};
/**
 * Adds an attribute by means of a key-value-pair.
 * @author Bjoern Kaiser
 */
void CNode::addAttribute(QString key, QString value)
{
    this->_attributes[key] = value;
};
/**
 * Returns pointer to the child node with the specified index.
 * @author Bjoern Kaiser
 */
CNode* CNode::childAt(int index) const
{
    return _children.value(index);
};
/**
 * Returns the number of direct child nodes.
 * @author Bjoern Kaiser
 */
int CNode::getCount() const
{
    return _children.count();
};
/**
 * Sets the parent node.
 * @author Bjoern Kaiser
 */
void CNode::setParent(CNode* parent)
{
    this->_parent = parent;
};
/**
 * Returns the parent node.
 * @author Bjoern Kaiser
 */
CNode* CNode::getParent() const
{
    if (_parent != 0)
        return this->_parent;
    return 0;
};
/**
 * Returns the index of the specified child node.
 * @author Bjoern Kaiser
 */
int CNode::indexOf(CNode* node) const
{
    return _children.indexOf(node);
};
/**
 * Adds the given node collection to the node's child collection.
 * @param nodes is a collection of nodes.
 * @author Bjoern Kaiser
 */
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
/**
 * Adds the given node to the node's child collection.
 * @author Bjoern Kaiser
 */
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
/**
 * Checks if the node's child collection contains the specified node.
 * @author Bjoern Kaiser
 */
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
/**
 * Removes the given node from the node's child collection.
 * @author Bjoern Kaiser
 */
void CNode::removeChild(CNode* node)
{
    if (_children.removeOne(node))
    {
        _cursor = -1;
        delete node;
    }
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

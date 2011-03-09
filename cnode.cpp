#include "cnode.h"

/**
 * Constructs a new object.
 * @param parent Initialiazes the object with the given CNode-object as its parent.
 * @author Bjoern Kaiser
 */
CNode::CNode(CNode* parent, QString name, qint64 layer) : _parent(parent),
    _layer(layer), _name(name), _content(""), _cursor(0)
{
    instCount++;
    if (layer > _treeLevel)
        _treeLevel = layer;
    this->_id = instCount;
    this->children = QList<CNode*>();
    this->_attributes = QMap<QString, QString>();
};
/**
 * This destructor deletes all child nodes by means of Qt's generic algorithms.
 * @author Bjoern Kaiser
 */
CNode::~CNode()
{
    qDeleteAll(children);
};
/**
 * This class instance counter is used to assign unique ID-numbers to each class instance.
 * @author Bjoern Kaiser
 */
qint64 CNode::instCount = 0;
qint64 CNode::_treeLevel = 0;
/**
  Returns the greatest distance of a node to the root node.
  */
qint64 CNode::treeLevel() const
{
    return this->_treeLevel;
};
/**
 * Returns the node's unique ID.
 * @author Bjoern Kaiser
 */
qint64 CNode::ID() const
{
    return this->_id;
};
/**
  * Returns the layer number of the node. The layer number is the distance to the
  * root node of the tree.
  * @author Bjoern Kaiser
  */
qint64 CNode::layer() const
{
    return this->_layer;
};
/**
 * Returns the node's name.
 * @author Bjoern Kaiser
 */
QString CNode::name() const
{
    return this->_name;
};
/**
 * Returns the node's text content.
 * @author Bjoern Kaiser
 */
QString CNode::content() const
{
    return this->_content;
};
/**
 * Returns node's attributes (such as size, width, align etc.).
 * @author Bjoern Kaiser
 */
QMap<QString, QString> CNode::attributes() const
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
    return children.value(index);
};
/**
 * Returns the number of direct child nodes.
 * @author Bjoern Kaiser
 */
int CNode::count() const
{
    return children.count();
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
CNode* CNode::parent()
{
    return this->_parent;
};
/**
 * Returns the index of the specified child node.
 * @author Bjoern Kaiser
 */
int CNode::indexOf(CNode* node) const
{
    return children.indexOf(node);
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
            children.append(nodes.at(i));
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
            children.append(node);
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
/**
 * Removes the given node from the node's child collection.
 * @author Bjoern Kaiser
 */
void CNode::removeChild(CNode* node)
{
    if (children.removeOne(node))
        delete node;
};
CNode* CNode::nextChild()
{
    _cursor++;
    if (_cursor < children.count())
        return children.at(_cursor);
    return 0;
};
CNode* CNode::firstChild()
{
    _cursor = 0;
    return children.at(_cursor);
};
CNode* CNode::lastChild()
{
    _cursor = children.count() - 1;
    return children.at(_cursor);
};

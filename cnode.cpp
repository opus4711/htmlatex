#include "cnode.h"

/**
 * Constructs a new object.
 * @param parent Initialiazes the object with the given CNode-object as its parent.
 * @author Björn Kaiser
 */
CNode::CNode(CNode* parent, QString name) : _parent(parent), _name(name), _content("")
{
    instCount++;
    this->_id = instCount;
    this->children = QList<CNode*>();
    this->_attributes = QMap<QString, QString>();
};
/**
 * This destructor deletes all child nodes by means of Qt's generic algorithms.
 * @author Björn Kaiser
 */
CNode::~CNode()
{
    qDeleteAll(children);
};
/**
 * This class instance counter is used to assign unique ID-numbers to each class instance.
 * @author Björn Kaiser
 */
qint64 CNode::instCount = 0;
/**
 * Returns the node's name.
 * @author Björn Kaiser
 */
QString CNode::name() const
{
    return this->_name;
};
/**
 * Returns the node's content.
 * @author Björn Kaiser
 */
QString CNode::content() const
{
    return this->_content;
};
/**
 * Returns node's attributes (such as size, width, align etc.).
 * @author Björn Kaiser
 */
QMap<QString, QString> CNode::attributes() const
{
    return this->_attributes;
};
/**
 * Sets the node's name.
 * @author Björn Kaiser
 */
void CNode::setName(QString name)
{
    this->_name = name;
};
/**
 * Sets the node's content.
 * @author Björn Kaiser
 */
void CNode::setContent(QString content)
{
    this->_content = content;
};
/**
 * Adds an attribute by means of a key-value-pair.
 * @author Björn Kaiser
 */
void CNode::addAttribute(QString key, QString value)
{
    this->_attributes[key] = value;
};
/**
 * Returns pointer to the child node with the specified index.
 * @author Björn Kaiser
 */
CNode* CNode::childAt(int index) const
{
    return children.value(index);
};
/**
 * Returns the number of direct child nodes.
 * @author Björn Kaiser
 */
int CNode::count() const
{
    return children.count();
};
/**
 * Sets the parent node.
 * @author Björn Kaiser
 */
void CNode::setParent(CNode* parent)
{
    this->_parent = parent;
};
/**
 * Returns the parent node.
 * @author Björn Kaiser
 */
CNode* CNode::parent()
{
    return this->_parent;
};
/**
 * Returns the index of the specified child node.
 * @author Björn Kaiser
 */
int CNode::indexOf(CNode* node) const
{
    return children.indexOf(node);
};
/**
 * Adds the given node collection to the node's child collection.
 * @param nodes is a collection of nodes.
 * @author Björn Kaiser
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
 * @author Björn Kaiser
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
 * @author Björn Kaiser
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
 * @author Björn Kaiser
 */
void CNode::removeChild(CNode* node)
{
    if (children.removeOne(node))
        delete node;
};

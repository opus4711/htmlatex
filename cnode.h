#ifndef CNODE_H
#define CNODE_H

#include <QString>
#include <QList>
#include <QMap>

/** The CNode class provides rudimental functionality to build tree structures and
  access its nodes. Each node is aware of its parent and children which can be
  accessed by methods such as getParent() or childAt(int index). Additionally
  each node holds an array of attributes.
  */
class CNode
{
private:
    // The _instCount class member counts the created instances of the CNode class.
    static qint64 _instCount;
    // The _treeLevel attribute holds the greatest distance of a leaf to the root
    // of the whole tree.
    static qint64 _treeLevel;
    // This pointer points to the parent node. In case of the root node it points to null.
    CNode* _parent;
    // This is generic array of pointers pointing to the child nodes.
    QList<CNode*> _children;
    // The _id is a unique number which allows identification of the node.
    qint64 _id;
    // The _layer numbers allows to determine to which layer / generation a node
    // belongs. The root node has the _layer number 0, its children 1 and its
    // grand children 2 and so on.
    qint64 _layer;
    // This is the name of the node.
    QString _name;
    // This is the content of the node.
    QString _content;
    // This is a key-value-structure which provides access to the value of type
    // QString via keys of the type QString.
    QMap<QString, QString> _attributes;
    // The _cursor indicates the current index position within the array of child
    // nodes (_children). The _cursor moves when the methods firstChild(),
    // nextChild() and lastChild() are called.
    int _cursor;
public:
    // This method returns a pointer pointing to the parent node object.
    CNode* getParent() const;
    // This method sets the pointer pointing to the parent node object.
    void setParent(CNode* parent);
    // This method returns the number of child nodes.
    int getCount() const;
    // This method returns true, if the array of child nodes (_children) contains
    // the specified pointer to a CNode object.
    bool containsChild(CNode* node) const;
    // This method returns a pointer to the child node specified by its array index.
    CNode* childAt(int index) const;
    // This method returns a pointer to the next child node by moving the _cursor
    // one step forward (increment of 1). If the node has less than two children
    // null is returned.
    CNode* nextChild();
    // This method returns a pointer to the first child node. If the node has no
    // children null is returned.
    CNode* firstChild();
    // This method returns a pointer to the last child node. If the node has no
    // children null is returned.
    CNode* lastChild();
    // This method appends a generic array of pointers pointing to CNode objects
    // to the array of child nodes (_children).
    void addChildren(QList<CNode*> nodes);
    // This method appends a pointer pointing to a CNode object to the array of
    // child nodes (_children).
    void addChild(CNode* node);
    // This method removes the specified pointer pointing to a CNode object from
    // the array of child nodes (_chidren).
    void removeChild(CNode* node);
    // This method returns the array index of the specified pointer pointing to a
    // CNode object. If it isn't contained in the array of child dnodes -1 is
    // returned.
    int indexOf(CNode* node) const;
    // This method returns the ID of the node.
    qint64 getID() const;
    // This method returns the _layer number of the node.
    qint64 getLayer() const;
    // This method returns the _treeLevel number (class member).
    qint64 getTreeLevel() const;
    // This method returns the name of the node.
    QString getName() const;
    // This method returns the content of the node.
    QString getContent() const;
    // This method returns the attributes of the node.
    QMap<QString, QString> getAttributes() const;
    // This method sets the name of the node.
    void setName(QString name);
    // This method sets the content of the node.
    void setContent(QString content);
    // This method adds an attribute by means of a key-value-pair.
    void addAttribute(QString key, QString value);
    // This is the copy-construcotr of the class.
    CNode(const CNode& node);
    // This constructor creates an instance initiallzing its _parent, _name and
    // and _layer number.
    CNode(CNode* parent, QString name, qint64 layer);
    // This destructor ensures that all child nodes are deleted as well.
    ~CNode();
};

#endif // CNODE_H

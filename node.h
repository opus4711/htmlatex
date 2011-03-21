#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QList>
#include <QMap>

/** The Node class provides rudimental functionality to build tree structures and
    access its nodes. Each node is aware of its parent and children which can be
    accessed by methods such as getParent() or childAt(int index). Additionally
    each node holds an array of attributes.
  */
class Node
{
private:
    /** The _instCount class member counts the created instances of the Node class.
        @author Bjoern
      */
    static qint64 _instCount;
    /** The _treeLevel attribute holds the greatest distance of a leaf to the root
        of the whole tree.
        @author Bjoern
      */
    static qint64 _treeLevel;
    /** The _treeNodeCount attribute holds the number of nodes of the whole tree.
        @author Bjoern
      */
    static qint64 _treeNodeCount;
    /** The _id is a unique number which allows identification of the node.
        @author Bjoern
      */
    qint64 _id;
    /** The _layer numbers allows to determine to which layer / generation a node
        belongs. The root node has the _layer number 0, its children 1 and its
        grand children 2 and so on.
        @author Bjoern
      */
    qint64 _layer;
    /** This is the name of the node.
        @author Bjoern
      */
    QString _name;
    /** This is the content of the node.
        @author Bjoern
      */
    QString _content;
    /** This pointer points to the parent node. In case of the root node it points to null.
        @author Bjoern
      */
    Node* _parent;
    /** This is generic array of pointers pointing to the child nodes.
        @author Bjoern
      */
    QList<Node*> _children;
    /** This is a key-value-structure which provides access to the value of type
        QString via keys of the type QString.
        @author Bjoern
      */
    QMap<QString, QString> _attributes;
    /** The _cursor indicates the current index position within the array of child
        nodes (_children). The _cursor moves when the methods firstChild(),
        nextChild() and lastChild() are called.
        @author Bjoern
      */
    int _cursor;
public:
    /** This is the copy-construcotr of the class.
        @author Bjoern
      */
    Node(const Node& node);
    /** This constructor creates an instance initiallzing its _parent, _name and
        and _layer number.
        @author Bjoern
      */
    Node(Node* parent, QString name, qint64 layer);
    /** This destructor ensures that all child nodes are deleted as well.
        @author Bjoern
      */
    ~Node();
    /** This method returns the _treeLevel number (class member).
        @author Bjoern
      */
    qint64 getTreeLevel() const;
    /** This method returns the number of nodes of the whole tree (class member).
        @author Bjoern
      */
    qint64 getTreeNodeCount() const;
    /** This method returns the ID of the node.
        @author Bjoern
      */
    qint64 getID() const;
    /** This method returns the _layer number of the node.
        @author Bjoern
      */
    qint64 getLayer() const;
    /** This method returns the name of the node.
        @author Bjoern
      */
    QString getName() const;
    /** This method sets the name of the node.
        @author Bjoern
      */
    void setName(QString name);
    /** This method returns the content of the node.
        @author Bjoern
      */
    QString getContent() const;
    /** This method sets the content of the node.
        @author Bjoern
      */
    void setContent(QString content);
    /** This method returns a pointer pointing to the parent node object.
        @author Bjoern
      */
    Node* getParent() const;
    /** This method sets the pointer pointing to the parent node object.
        @author Bjoern
      */
    void setParent(Node* parent);
    /** This method returns the number of child nodes.
        @author Bjoern
      */
    int getCount() const;
    /** This method returns true, if the array of child nodes (_children) contains
        the specified pointer to a Node object.
        @author Bjoern
      */
    bool containsChild(Node* node) const;
    /** This method returns a pointer to the child node specified by its array index.
        @author Bjoern
      */
    Node* childAt(int index) const;
    /** This method returns a pointer to the next child node by moving the _cursor
        one step forward (increment of 1). If the node has less than two children
        null is returned.
        @author Bjoern
      */
    Node* nextChild();
    /** This method returns a pointer to the first child node. If the node has no
        children null is returned.
        @author Bjoern
      */
    Node* firstChild();
    /** This method returns a pointer to the last child node. If the node has no
        children null is returned.
        @author Bjoern
      */
    Node* lastChild();
    /** This method appends a generic array of pointers pointing to Node objects
        to the array of child nodes (_children).
        @author Bjoern
      */
    void addChildren(QList<Node*> nodes);
    /** This method appends a pointer pointing to a Node object to the array of
        child nodes (_children).
        @author Bjoern
      */
    void addChild(Node* node);
    /** This method removes the specified pointer pointing to a Node object from
        the array of child nodes (_chidren).
        @author Bjoern
      */
    void removeChild(Node* node);
    /** This method returns the array index of the specified pointer pointing to a
        Node object. If it isn't contained in the array of child dnodes -1 is
        returned.
        @author Bjoern
      */
    int indexOf(Node* node) const;
    /** This method returns the attributes of the node.
        @author Bjoern
      */
    QMap<QString, QString> getAttributes() const;
    /** This method adds an attribute by means of a key-value-pair.
        @author Bjoern
      */
    void addAttribute(QString key, QString value);
};

#endif // Node_H

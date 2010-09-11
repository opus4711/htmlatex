#ifndef CNODE_H
#define CNODE_H

#include <QString>
#include <QList>

class CNode
{
private:
    static int instCount;
    CNode* _parent;
    QList<CNode*> children;
    int _id;
    QString _name;
    QString _reference;
    QString _fontData;
public:
    // methods handling node operations
    CNode* parent();
    void setParent(CNode* parent);
    int count() const;
    bool containsChild(CNode* node) const;
    CNode* childAt(int index) const;
    void addChildren(QList<CNode*> nodes);
    void addChild(CNode* node);
    void removeChild(CNode* node);
    int indexOf(CNode* node) const;
    // methods returning attributes' values
    QString name() const;
    QString reference() const;
    QString fontData() const;
    // constructor and destructor
    CNode(CNode* parent);
    ~CNode();
};

#endif // CNODE_H

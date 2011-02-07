#ifndef CNODE_H
#define CNODE_H

#include <QString>
#include <QList>
#include <QMap>

class CNode
{
private:
    static qint64 instCount;
    CNode* _parent;
    QList<CNode*> children;
    qint64 _id;
    QString _name;
    QMap<QString, QString> _data;
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
    QMap<QString, QString> data() const;
    // methods setting attributes' values
    void setName(QString name);
    void addAttribute(QString key, QString value);
    // constructor and destructor
    CNode(CNode* parent, QString name);
    ~CNode();
};

#endif // CNODE_H

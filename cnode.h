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
    QString _content;
    QMap<QString, QString> _attributes;
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
    qint64 ID() const;
    QString name() const;
    QString content() const;
    QMap<QString, QString> attributes() const;
    // methods setting attributes' values
    void setName(QString name);
    void setContent(QString content);
    void addAttribute(QString key, QString value);
    // constructor and destructor
    CNode(CNode* parent, QString name);
    ~CNode();
};

#endif // CNODE_H

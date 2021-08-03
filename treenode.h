#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>
#include <QVariant>

class TreeNode : public QObject
{
    Q_OBJECT
public:
    TreeNode(const QString& name, const QVariant& value);

    const QString& name() const
    { return m_name; }

    const QVariant& value() const
    { return m_value; }

    void setValue(const QVariant& value)
    { m_value = value; }

    TreeNode* right() const
    { return m_right; }

    TreeNode* left() const
    { return m_left; }

    void addLeft(TreeNode* node)
    { m_left = node; }

    void addRight(TreeNode* node)
    { m_right = node; }



private:

    QString m_name;
    QVariant m_value;

    TreeNode* m_left;
    TreeNode* m_right;


};

#endif // TREENODE_H

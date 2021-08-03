#ifndef TREE_H
#define TREE_H

class QString;
class QVariant;

class TreeNode;

class Tree
{
public:
    Tree();

    TreeNode* head() const
    { return m_head; }

private:

    TreeNode* m_head;
};

#endif // TREE_H

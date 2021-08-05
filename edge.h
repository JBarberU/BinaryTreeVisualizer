#ifndef EDGE_H
#define EDGE_H

class INode;

class Edge
{
public:
    Edge(INode* parent, INode* child)
        : m_parent(parent)
        , m_child(child)
    {}

    INode* parent() const
    { return m_parent; }

    INode* child() const
    { return m_child; }

private:
    INode* m_parent;
    INode* m_child;
};

#endif // EDGE_H

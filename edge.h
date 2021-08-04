#ifndef EDGE_H
#define EDGE_H

class INode;

class Edge
{
public:
    Edge(INode* left, INode* right)
        : m_left(left)
        , m_right(right)
    {}

    INode* left() const
    { return m_left; }

    INode* right() const
    { return m_right; }

private:
    INode* m_left;
    INode* m_right;
};

#endif // EDGE_H

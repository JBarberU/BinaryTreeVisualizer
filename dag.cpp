#include "dag.h"
#include "node.h"
#include "edge.h"

Dag::Dag()
{

}

Dag::~Dag()
{
    for (INode* n : m_nodes)
    {
        delete n;
    }
    for (Edge* e : m_edges)
    {
        delete e;
    }

}

void Dag::connect(INode *left, INode *right)
{
    m_edges.push_back(new Edge(left, right));
}

std::vector<INode*> Dag::getConnected(INode* node) const
{
    std::vector<INode*> ret;
    for (const Edge* e : m_edges)
    {
        if (e->left() == node)
        {
            ret.push_back(e->right());
        }
        else if (e->right() == node)
        {
            ret.push_back(e->left());
        }
    }
    return ret;
}


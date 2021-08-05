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

void Dag::connect(INode *parent, INode *child)
{
    m_edges.push_back(new Edge(parent, child));
}

std::vector<INode*> Dag::getChildren(INode *node) const
{
    std::vector<INode*> ret;
    for (const Edge* e : m_edges)
    {
        if (e->parent() == node)
            ret.push_back(e->child());
    }
    return ret;
}


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

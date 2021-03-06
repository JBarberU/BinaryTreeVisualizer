// The MIT License (MIT)
//
// Copyright (c) John Barbero Unenge
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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


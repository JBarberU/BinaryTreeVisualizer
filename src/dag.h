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

#ifndef DAG_H
#define DAG_H

#include <QObject>
#include <QString>


template <typename T>
class Node;
class INode;

class Edge;

class Dag : public QObject
{
    Q_OBJECT
public:
    Dag();

    template<typename T>
    Node<T>* createNode(const QString& name, const T& value)
    {
        Node<T>* n = new Node<T>(name, value);
        m_nodes.push_back(n);
        return n;
    }

    void connect(INode* parent, INode* child);
    std::vector<INode*> getChildren(INode* node) const;

    ~Dag();

signals:

private:
    std::vector<INode*> m_nodes;
    std::vector<Edge*> m_edges;
};

#endif // DAG_H

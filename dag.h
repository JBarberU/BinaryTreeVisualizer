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
    Node<T>* createNode(const QString& name)
    {
        m_nodes.push_back(new Node<T>(name));
    }

    void connect(INode* left, INode* right);

    ~Dag();

signals:

private:
    std::vector<INode*> m_nodes;
    std::vector<Edge*> m_edges;
};

#endif // DAG_H

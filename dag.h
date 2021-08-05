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
//    std::vector<INode*> getConnected(INode* node) const;
    std::vector<INode*> getChildren(INode* node) const;

    ~Dag();

signals:

private:
    std::vector<INode*> m_nodes;
    std::vector<Edge*> m_edges;
};

#endif // DAG_H

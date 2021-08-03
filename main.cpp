#include "mainwindow.h"

#include <QApplication>

class INode;

template <typename T>
class Node;

class INode
{
public:

    INode()
        : m_left(nullptr)
        , m_right(nullptr)
    {}

    virtual ~INode()
    {
        if (m_left)
        {
            delete m_left;
            m_left = nullptr;
        }

        if (m_right)
        {
            delete m_right;
            m_right = nullptr;
        }
    }

    virtual void print() const
    {
        if (m_left)
            m_left->print();
        if (m_right)
            m_right->print();
    }

    INode* left()
    { return m_left; }

    INode* right()
    { return m_right; }

private:
    INode* m_left;
    INode* m_right;
};

template <typename T>
class Node : public INode
{
public:
    Node(const QString& name, const T& value)
        : m_name(name)
        , m_value(value)
    {}

    void print() const override
    {
        qDebug() << m_name << ": " << m_value;
        INode::print();
    }

private:
    QString m_name;
    T m_value;
};

class StringNode : public Node<QString>
{};

class FloatNode : public Node<float>
{};

class Tree
{
public:

    template <typename NodeT>
    Tree(NodeT* head)
        : m_head(head)
    {}

    ~Tree()
    {
        delete m_head;
    }

    void print()
    {
        m_head->print();
    }

private:

    INode* m_head;

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Tree t(new Node<QString>("HeadNode", "Hehe"));
    t.print();

    return a.exec();
}

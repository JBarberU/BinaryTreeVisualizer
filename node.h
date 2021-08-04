#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QVariant>

template <typename T>
class Node;

class INode
{
public:

    INode(const QString& name)
        : m_name(name)
    {}

    virtual ~INode()
    {}

    const QString& name() const
    { return m_name; }

    template <typename T>
    Node<T>* asType()
    {
        return dynamic_cast<Node<T>*>(this);
    }

private:

    QString m_name;

};

template <typename T>
class Node : public INode
{
public:

    template <typename T2>
    Node(const QString& name, const T2& value)
        : INode(name)
        , m_value(value)
    {}

    template <typename T2>
    Node<T> asType();

    const T& value() const
    { return m_value; }

    void setValue(const T& value)
    {
        m_value = value;
    }

private:
    T m_value;
};



#endif // NODE_H

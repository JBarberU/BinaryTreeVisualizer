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

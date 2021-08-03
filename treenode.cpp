#include "treenode.h"
#include <QMetaType>

TreeNode::TreeNode(const QString& name, const QVariant& value)
    : m_name(name)
    , m_value(value)
    , m_left(nullptr)
    , m_right(nullptr)
{
}



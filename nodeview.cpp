#include "nodeview.h"
#include "ui_nodeview.h"
#include "node.h"
#include <numeric>
#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QLineEdit>
#include <QSlider>

namespace
{
const QColor accent(16, 97, 110);
const QColor lightGray1(0xb0, 0xb0, 0xb0);
const QColor lightGray2(0x70, 0x70, 0x70);
}

NodeView::NodeView(INode* node, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NodeView)
    , m_node(node)
{

    ui->setupUi(this);

    Node<QString>* strNode = m_node->asType<QString>();

    if (strNode)
    {
        QLineEdit* le = new QLineEdit(strNode->value());
        ui->w_valueEdit->layout()->addWidget(le);

        {
            auto p = le->palette();
            p.setColor(QPalette::ColorRole::Text, Qt::white);
            p.setColor(QPalette::ColorRole::Base, lightGray2);
            p.setColor(QPalette::ColorRole::Highlight, accent);
            le->setPalette(p);
        }
        {
            auto font = le->font();
            font.setPointSize(14);
            le->setFont(font);
        }

        QObject::connect(le, &QLineEdit::textChanged, [strNode](const QString& str)
        {
            strNode->setValue(str);
        });
    }
    else
    {
        Node<float>* floatNode = m_node->asType<float>();
        if (floatNode)
        {
            QSlider* slider = new QSlider(Qt::Orientation::Horizontal);
            slider->setStyleSheet("QSlider::horizontal { height: 20px; } QSlider::groove:horizontal { height: 4px; border: 1px solid; margin: 0; } QSlider::add-page:horizontal {	background: #666666; height: 2px; } QSlider::sub-page:horizontal { background: #666666; } QSlider::handle:horizontal { background: #265b91; border-radius: 9px; margin: -7px 0; width: 18px; height: 18px; }");

            ui->w_valueEdit->layout()->addWidget(slider);
            slider->setValue(floatNode->value());
            connect(slider, &QSlider::valueChanged, [floatNode](int value)
            {
                floatNode->setValue(static_cast<float>(value));
            });
        }
        else
        {
            Q_ASSERT(false); // Unhandled node type
        }
    }
}

NodeView::~NodeView()
{
    delete ui;
}

void NodeView::paintEvent(QPaintEvent *event)
{

    QColor bg(59, 59, 59);

    QPainter painter(this);
    painter.setBrush(accent);
    painter.setPen(accent);
    auto w = width() * .05f;
    painter.drawRect(0, 0, w, height());

    painter.setBrush(bg);
    painter.setPen(bg);
    painter.drawRect(w, 0, width()-w, height());
//    style()
}

void NodeView::on_btn_left_clicked()
{
    // add child left
//    m_treeNode->addLeft(new TreeNode("NewNode", 13.37));
}

void NodeView::on_btn_right_clicked()
{
    // add child right
//    m_treeNode->addRight(new TreeNode("New right", "Hellol"));
}

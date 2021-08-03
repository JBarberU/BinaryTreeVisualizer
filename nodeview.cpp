#include "nodeview.h"
#include "ui_nodeview.h"
#include "treenode.h"
#include <numeric>
#include <QPaintEvent>
#include <QPainter>
#include <QColor>

namespace
{
const QColor accent(16, 97, 110);
}

NodeView::NodeView(TreeNode* treeNode, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NodeView)
    , m_treeNode(treeNode)
{

    ui->setupUi(this);

    {
        auto p = palette();
    //    p.setColor(QPalette::ColorGroup::Normal, QPalette::ColorRole::Window, QColor(16, 97, 110));
        p.setColor(QPalette::ColorGroup::Normal, QPalette::ColorRole::Window, QColor(59, 59, 59));
        setPalette(p);
    }
    {
        auto p = ui->le_value->palette();
        p.setColor(QPalette::ColorRole::Text, Qt::white);
        p.setColor(QPalette::ColorRole::Base, QColor(0x70, 0x70, 0x70));
        p.setColor(QPalette::ColorRole::Highlight, accent);
        ui->le_value->setPalette(p);
    }



    if (m_treeNode->value().canConvert<QString>())
    {
        ui->sl_value->setHidden(true);

        ui->le_value->setHidden(false);
        ui->le_value->setText(m_treeNode->value().toString());
        QObject::connect(ui->le_value, &QLineEdit::textChanged, [&](const QString& str)
        {
            this->m_treeNode->setValue(str);
        });
    }
    else if (m_treeNode->value().canConvert<float>())
    {
        ui->le_value->setHidden(true);

        ui->sl_value->setHidden(false);
        using flt_lim = std::numeric_limits<float>;
        ui->sl_value->setMinimum(flt_lim::min());
        ui->sl_value->setMaximum(flt_lim::max());
        ui->sl_value->setValue(treeNode->value().toFloat());
        connect(ui->sl_value, &QSlider::valueChanged, [&](int value)
        {
            treeNode->setValue(static_cast<float>(value));
        });

    }
    else
    {
        Q_ASSERT(false);
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
    m_treeNode->addLeft(new TreeNode("NewNode", 13.37));
}

void NodeView::on_btn_right_clicked()
{
    // add child right
    m_treeNode->addRight(new TreeNode("New right", "Hellol"));
}

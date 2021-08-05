#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nodeview.h"
#include "node.h"
#include "dag.h"
#include <map>
#include <QLabel>
#include <QPaintEngine>

namespace
{
constexpr int PADDING_Y = 50;
constexpr int PADDING_X = 30;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_dag = new Dag;
//    m_tree->add("Testing Node", "This is a node");

    m_head = m_dag->createNode<float>("Head node", 13.37);
    INode* node1l = m_dag->createNode<QString>("Left child", "Hello this is node");
    INode* node1r = m_dag->createNode<float>("Right child", 42);
    m_dag->connect(m_head, node1r);
    m_dag->connect(m_head, node1l);


    INode* node1ll = m_dag->createNode<QString>("ll child", "other");
    INode* node1lr = m_dag->createNode<float>("lr child", 78);
    m_dag->connect(node1l, node1lr);
    m_dag->connect(node1l, node1ll);

    INode* node1rl = m_dag->createNode<QString>("rl child", "other");
    INode* node1rr = m_dag->createNode<float>("rr child", 78);
    m_dag->connect(node1r, node1rr);
    m_dag->connect(node1r, node1rl);

    updateDagView();
//    INode* tn = new Node<QString>("Testing Node", "Some Text");
}

int getDepth(Dag* dag, INode* node)
{
    int d = 0;
    for (INode* n : dag->getChildren(node))
    {
        d = std::max(d, getDepth(dag, n));
    }
    return 1 + d;
}

void recursePlaceNodeViews(QWidget* w, INode* node, const QRect& placement, Dag* dag, std::map<INode*, NodeView*>& nodeViews, int distanceFromBottom)
{
    NodeView* nv = new NodeView(node, w);
    nodeViews[node] = nv;
    nv->move(placement.x(), placement.y());

    int modX = PADDING_X + ((distanceFromBottom-1) * placement.width() / 2);
    for (INode* n : dag->getChildren(node))
    {
        QRect r = placement;
        QPoint p(r.x() + modX, r.y() + placement.size().height() + PADDING_Y);
        r.moveTo(p);

        modX = -modX;
        recursePlaceNodeViews(w, n, r, dag, nodeViews, distanceFromBottom-1);
    }
}

void MainWindow::updateDagView()
{
    // 1. calculate total width
    // 2. place head in center at top
    // 3. check connections
    // 4. add left edge for left child
    // 5. add right edge for right child
    // 6. add left child
    // 7. add right child
    // 8. move to left child
    // 9. ...
    // 10. move to right child
    // 11. ...


    std::map<INode*, NodeView*> nvs;

    recursePlaceNodeViews(ui->sc_dagWidget, m_head, QRect(0, 0, NodeView::WIDTH, NodeView::HEIGHT), m_dag, nvs, getDepth(m_dag, m_head));

    int maxX = 0;
    int maxY = 0;
    int minX = 0;
    for (const auto& nvPair : nvs)
    {
        maxX = std::max(maxX, nvPair.second->pos().x());
        maxY = std::max(maxY, nvPair.second->pos().y());
        minX = std::min(minX, nvPair.second->pos().x());
    }

    // Shift all NodeViews into view
    for (const auto& nvPair : nvs)
    {
        auto* nodeView = nvPair.second;
        nodeView->move(PADDING_X + nodeView->pos().x() - minX, PADDING_Y + nodeView->pos().y());
    }

    // Resize widget in ScrollView
    ui->sc_dagWidget->setMinimumSize(2 * PADDING_X + maxX - minX + NodeView::WIDTH, 2 * PADDING_Y + maxY + NodeView::HEIGHT);
}
MainWindow::~MainWindow()
{
    delete ui;
    delete m_dag;
}


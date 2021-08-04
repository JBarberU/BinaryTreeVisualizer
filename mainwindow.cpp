#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nodeview.h"
#include "node.h"
#include "dag.h"
#include <map>

namespace
{
constexpr int PADDING = 30;
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
    m_dag->connect(m_head, node1l);
    m_dag->connect(m_head, node1r);


    INode* node1ll = m_dag->createNode<QString>("Left child", "other");
    INode* node1lr = m_dag->createNode<float>("Right child", 78);
    m_dag->connect(node1l, node1ll);
    m_dag->connect(node1l, node1lr);

    updateDagView();
//    INode* tn = new Node<QString>("Testing Node", "Some Text");
}

void recursePlaceNodeViews(QWidget* w, INode* node, const QRect& placement, Dag* dag, std::map<INode*, NodeView*>& nodeViews)
{
    NodeView* nv = new NodeView(node, w);
    nodeViews[node] = nv;
    nv->move(placement.x(), placement.y());

    int modX = 4 * placement.size().width() / 6;
    for (INode* n : dag->getConnected(node))
    {
        if (nodeViews.find(n) != nodeViews.end())
            continue;

        QRect r = placement;
        r.moveTo(r.x() + modX, r.y() + placement.size().height() + PADDING);
        modX = -modX;

        //QPoint thisPos(placement.x() + modX, placement.y() + placement.size().height() + PADDING);
        recursePlaceNodeViews(w, n, r, dag, nodeViews);
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

    recursePlaceNodeViews(ui->sc_dagWidget, m_head, QRect(0, 0, NodeView::WIDTH, NodeView::HEIGHT), m_dag, nvs);
//    NodeView* nv = new NodeView(m_head, ui->sc_dagWidget);
//    nvs.push_back(nv);

//    nv->move(-nv->size().width() / 2, 0);
//    int y = nv->size().height() + PADDING;
//    int xMod = 4 * nv->size().width() / 6;

//    int parentX = nv->pos().x();
//    int maxX = 0;
//    for (INode* n : m_dag->getConnected(m_head))
//    {
//        NodeView* nv2 = new NodeView(n, ui->sc_dagWidget);
//        nvs.push_back(nv2);
//        int currentX = parentX + xMod;
//        maxX = std::max(currentX, maxX);
//        nv2->move(currentX, y);
//        xMod = -xMod;
//    }

    int maxX = 0;
    int maxY = 0;
    for (const auto& nvPair : nvs)
    {
        maxX = std::max(maxX, nvPair.second->pos().x());
        maxY = std::max(maxY, nvPair.second->pos().y());
    }

    // Shift all views into view
    for (const auto& nvPair : nvs)
    {
        auto* nodeView = nvPair.second;
        nodeView->move(PADDING + nodeView->size().width() + nodeView->pos().x() + maxX, PADDING + nodeView->pos().y());
    }

    // Resize widget in ScrollView
    ui->sc_dagWidget->setMinimumSize(2* (maxX + NodeView::WIDTH + PADDING), 2 * PADDING + maxY + NodeView::HEIGHT);
}
MainWindow::~MainWindow()
{
    delete ui;
    delete m_dag;
}


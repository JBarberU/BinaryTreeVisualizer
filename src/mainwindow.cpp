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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nodeview.h"
#include "node.h"
#include "dag.h"
#include <map>
#include <QLabel>
#include <QPaintEngine>
#include "dagdrawer.h"

namespace
{
constexpr int PADDING_Y = 50;
constexpr int PADDING_X = 30;
}

void generateTestData(Dag* dag, INode*& head)
{
    head = dag->createNode<float>("Head node", 13.37);
    INode* nodel = dag->createNode<QString>("Left child", "Hello this is node");
    INode* noder = dag->createNode<float>("Right child", 42);
    dag->connect(head, noder);
    dag->connect(head, nodel);


    INode* nodell = dag->createNode<QString>("ll child", "Some text");
    INode* nodelr = dag->createNode<float>("lr child", 12);
    dag->connect(nodel, nodelr);
    dag->connect(nodel, nodell);

    INode* nodelrl = dag->createNode<float>("lr child", 55);
    dag->connect(nodelr, nodelrl);

    INode* noderl = dag->createNode<QString>("rl child", "Hello");
    INode* noderr = dag->createNode<float>("rr child", 2);
    dag->connect(noder, noderr);
    dag->connect(noder, noderl);

    INode* noderrl = dag->createNode<QString>("rrl child", "A really long text label");
    INode* nodellr = dag->createNode<float>("llr child", 97);
    dag->connect(noderr, noderrl);
    dag->connect(nodell, nodellr);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_dag(new Dag)
{
    ui->setupUi(this);

    generateTestData(m_dag, m_head);
    updateDagView();
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

void recursePlaceNodeViews(DagDrawer* w, INode* node, const QRect& placement, Dag* dag, std::map<INode*, NodeView*>& nodeViews, int distanceFromBottom)
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
        w->addEdge(QLineF(placement.x() + .5f * placement.width(), placement.y() + placement.height(), p.x() + .5f * placement.width(), p.y()));

        modX = -modX;
        recursePlaceNodeViews(w, n, r, dag, nodeViews, distanceFromBottom-1);
    }
}

void MainWindow::updateDagView()
{
    ui->sc_dagWidget->clearEdges();
    std::map<INode*, NodeView*> nodeViews;

    recursePlaceNodeViews(ui->sc_dagWidget, m_head, QRect(0, 0, NodeView::WIDTH, NodeView::HEIGHT), m_dag, nodeViews, getDepth(m_dag, m_head));

    int maxX = 0;
    int maxY = 0;
    int minX = 0;
    for (const auto& nvPair : nodeViews)
    {
        maxX = std::max(maxX, nvPair.second->pos().x());
        maxY = std::max(maxY, nvPair.second->pos().y());
        minX = std::min(minX, nvPair.second->pos().x());
    }

    // Shift all NodeViews into view
    int transformX = PADDING_X - minX;
    int transformY = PADDING_Y;
    for (const auto& nvPair : nodeViews)
    {
        auto* nodeView = nvPair.second;
        nodeView->move(transformX + nodeView->pos().x(), transformY + nodeView->pos().y());
    }
    ui->sc_dagWidget->transformLines(transformX, transformY);
    // Resize widget in ScrollView
    ui->sc_dagWidget->setMinimumSize(2 * PADDING_X + maxX - minX + NodeView::WIDTH, 2 * PADDING_Y + maxY + NodeView::HEIGHT);
}
MainWindow::~MainWindow()
{
    delete ui;
    delete m_dag;
}


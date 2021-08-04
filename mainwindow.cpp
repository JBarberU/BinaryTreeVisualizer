#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nodeview.h"
#include "node.h"
#include "dag.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_dag = new Dag;
//    m_tree->add("Testing Node", "This is a node");
    INode* tn = new Node<float>("Testing Node", 13.37);
//    INode* tn = new Node<QString>("Testing Node", "Some Text");
    NodeView* nv = new NodeView(tn, this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_dag;
}


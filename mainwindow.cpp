#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nodeview.h"
#include "treenode.h"
#include "tree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_tree = new Tree;
//    m_tree->add("Testing Node", "This is a node");
    TreeNode* tn = new TreeNode("Testing Node", 13.37);
    NodeView* nv = new NodeView(tn, this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_tree;
}


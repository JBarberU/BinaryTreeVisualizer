#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QWidget>

namespace Ui {
class NodeView;
}

class TreeNode;

class NodeView : public QWidget
{
    Q_OBJECT

public:
    explicit NodeView(TreeNode* tn, QWidget *parent = nullptr);
    ~NodeView();

    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_btn_left_clicked();

    void on_btn_right_clicked();

private:
    Ui::NodeView *ui;
    TreeNode* m_treeNode;
};

#endif // NODEVIEW_H

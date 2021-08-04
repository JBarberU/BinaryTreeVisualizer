#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QWidget>

namespace Ui {
class NodeView;
}

class INode;

class NodeView : public QWidget
{
    Q_OBJECT

public:
    explicit NodeView(INode* node, QWidget *parent = nullptr);
    ~NodeView();

    void paintEvent(QPaintEvent *event) override;

    static constexpr int WIDTH = 200;
    static constexpr int HEIGHT = 150;

private slots:
    void on_btn_left_clicked();

    void on_btn_right_clicked();

private:
    Ui::NodeView *ui;
    INode* m_node;
};

#endif // NODEVIEW_H

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

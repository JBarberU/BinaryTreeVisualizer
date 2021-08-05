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

#include "dagdrawer.h"
#include <QPainter>
#include <QColor>

void DagDrawer::addEdge(QLineF &&line)
{
    m_lines.emplace_back(std::move(line));
}

void DagDrawer::transformLines(int x, int y)
{
    for (auto& l : m_lines)
    {
        l.setP1(QPointF(l.p1().x() + x, l.p1().y() + y));
        l.setP2(QPointF(l.p2().x() + x, l.p2().y() + y));
    }
}

void DagDrawer::clearEdges()
{
    m_lines.clear();
}

void DagDrawer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(0xb9, 0x6d, 0x14), 5));
    painter.drawLines(m_lines);

    QWidget::paintEvent(event);
}

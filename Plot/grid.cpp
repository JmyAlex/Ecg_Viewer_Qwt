#include "grid.h"
#include <QPen>
#include <QPainter>
#include <QPalette>

Grid::Grid()
{
}

void Grid::draw(QPainter *p, const QwtScaleMap &xMap, const QwtScaleMap &yMap, const QRectF &rect) const
{
    p->save();

    QPalette palette;
    QPen quiteDark = palette.dark().color().light();
    for (int i = 0; i < rect.width(); i += 4)
    {
        p->setPen(quiteDark);
        p->drawLine(i, rect.top(), i, rect.bottom());
        p->drawLine(rect.left(), i, rect.right(), i);
    }
    //QPen quiteDark = palette().dark().color().light();
    for (int i = 0; i < rect.width(); i += 20)
    {
        p->setPen(Qt::lightGray);
        p->drawLine(i, rect.top(), i, rect.bottom());
        p->drawLine(rect.left(), i, rect.right(), i);
    }
    //QPen quiteDark = palette().dark().color().light();
    for (int i = 0; i < rect.width(); i += 40)
    {
        p->setPen(Qt::darkGray);
        p->drawLine(i, rect.top(), i, rect.bottom());
        p->drawLine(rect.left(), i, rect.right(), i);
    }

    p->restore();
}

#ifndef GRID_H
#define GRID_H

#include <qwt_plot_grid.h>

class Grid : public QwtPlotGrid
{
public:
    Grid();

    virtual void draw(QPainter *p, const QwtScaleMap &xMap, const QwtScaleMap &yMap, const QRectF &rect) const;
};

#endif // GRID_H

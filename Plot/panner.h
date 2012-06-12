#ifndef PANNER_H
#define PANNER_H

#include <qwt_plot_panner.h>

class Panner : public QwtPlotPanner
{
public:
    Panner(QwtPlotCanvas *canvas);
};

#endif // PANNER_H

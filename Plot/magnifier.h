#ifndef MAGNIFIER_H
#define MAGNIFIER_H

#include <qwt_plot_magnifier.h>

class Magnifier : public QwtPlotMagnifier
{
public:
    Magnifier(QwtPlotCanvas *canvas);
};

#endif // MAGNIFIER_H

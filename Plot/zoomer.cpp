#include "zoomer.h"

Zoomer::Zoomer(int xAxis, int yAxis, QwtPlotCanvas *canvas) : QwtPlotZoomer( xAxis, yAxis, canvas )
{
    setTrackerMode( QwtPicker::AlwaysOff );
    setRubberBand( QwtPicker::NoRubberBand );
    setMousePattern(QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier);
    setMousePattern(QwtEventPattern::MouseSelect3, Qt::RightButton);
}

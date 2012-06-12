#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>

class QwtPlotCurve;
class Zoomer;
class Magnifier;
class Panner;
class Grid;

class Plot : public QwtPlot
{
    Q_OBJECT

public:
    Plot(QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    Zoomer *zommer() const;
    Panner *panner() const;

    bool ReadFile(const QString &file_name);

    bool hasActiveTool();

signals:
    void modifiedPlot();

public slots:
    void zoomed (const QRectF &rect);
    void zoom(bool on);
    bool zoomIn();
    void zoomOut();
    void disableTools();
    bool panEnabled();

private:
    void rescale();

    //Plot data
    QwtPlotCurve *_curve;
    Zoomer *_zoomer[2];
    Magnifier *_magnifier;
    Panner *_panner;
    Grid *_grid;

    //Signal data
};

#endif // PLOT_H

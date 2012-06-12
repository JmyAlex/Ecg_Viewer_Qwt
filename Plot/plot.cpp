#include "plot.h"
#include "Plot/zoomer.h"
#include "Plot/magnifier.h"
#include "Plot/panner.h"
#include "Plot/grid.h"

#include "Signal/signaldata.h"
#include "Signal/curvedata.h"

#include <qwt_plot_curve.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_layout.h>

#include <QFile>
#include <QMessageBox>

#include <algorithm>

Plot::Plot(QWidget *parent) : QwtPlot(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setAutoReplot(false);

    // Curves
    _curve = new QwtPlotCurve("Ecg Signal");
    _curve->setPaintAttribute(QwtPlotCurve::ClipPolygons);

    QPen curve_pen;
    curve_pen.setColor(Qt::black);
    curve_pen.setWidth(2);

    _curve->setPen(curve_pen);
    _curve->setData(new CurveData());
    _curve->attach( this );

    // Zoomer
    // LeftButton for the zooming
    // RightButton: zoom out by 1
    // Ctrl+RighButton: zoom out to full size
//    _zoomer = new Zoomer(canvas());
//    _zoomer->setEnabled(false);
//    _zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
//        Qt::RightButton, Qt::ControlModifier);
//    _zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
//        Qt::RightButton);
    _zoomer[0] = new Zoomer(QwtPlot::xBottom, QwtPlot::yLeft, canvas());
    _zoomer[0]->setRubberBand(QwtPicker::RectRubberBand);
    _zoomer[0]->setTrackerMode(QwtPicker::ActiveOnly);
    _zoomer[1] = new Zoomer(QwtPlot::xTop, QwtPlot::yRight, canvas());
    zoom(false);

    // Magnidfier
    // zoom in/out with the wheel
    _magnifier = new Magnifier(canvas());

    // Panner
    // panning with the left mouse button
    _panner = new Panner(canvas());
    //_panner->setMouseButton( Qt::MidButton );
    _panner->setEnabled(false);

    // Grid
    _grid = new Grid();
    _grid->attach(this);

    // Axis
    //enableAxis(QwtPlot::xBottom, false);
    //enableAxis(QwtPlot::yLeft, false);

    // canvas
    canvas()->setFocusPolicy(Qt::StrongFocus);
    canvas()->setFocusIndicator(QwtPlotCanvas::ItemFocusIndicator);
    canvas()->setFocus();
    canvas()->setFrameShadow(QwtPlot::Plain);
    canvas()->setCursor(Qt::ArrowCursor);
    canvas()->setLineWidth(0);
    canvas()->setFrameStyle(QFrame::Box | QFrame::Plain);
    //canvas()->setBorderRadius(15);

    QColor background = QColor(Qt::white);
    background.setAlpha(255);

    QPalette palette;
    palette.setColor(QPalette::Window, background);
    setPalette(palette);

    //QPalette canvasPalette( Qt::white );
    //canvasPalette.setColor( QPalette::Foreground, QColor( 133, 190, 232 ) );
    //canvas()->setPalette( canvasPalette );

    // Plot
    setAutoFillBackground(true);
    //setPalette(QPalette(QColor(165, 193, 228)));

    setCanvasBackground (background);
    setFocusPolicy(Qt::StrongFocus);
    setFocusProxy(canvas());
    setFrameShape(QFrame::Box);
    setLineWidth(0);
    setMouseTracking(true);

    plotLayout()->setCanvasMargin(0);
    plotLayout()->setAlignCanvasToScales(true);
    for (int axis = 0; axis < QwtPlot::axisCnt; axis++)
        enableAxis(axis, false);

    connect(_zoomer[0], SIGNAL(zoomed(QRectF)), this, SLOT(zoomed(QRectF)));

}

QSize Plot::minimumSizeHint() const
{
    return QSize(300, 200);
}

QSize Plot::sizeHint() const
{
    return QSize(750, 400);
}

void Plot::zoomed(const QRectF &rect)
{
    emit modifiedPlot();
}

void Plot::zoom(bool on)
{
    _zoomer[0]->setEnabled(on);
    _zoomer[1]->setEnabled(on);

    if (on)
        //canvas()->setCursor(Qt::CrossCursor);
        canvas()->setCursor(QCursor(QPixmap(":/images/lens.png"), -1, -1));
    else
        canvas()->setCursor(Qt::ArrowCursor);
}

bool Plot::zoomIn()
{
    return (_zoomer[0]->isEnabled() || _zoomer[1]->isEnabled());
}

void Plot::zoomOut()
{
    _zoomer[0]->zoom(-1);
    _zoomer[1]->zoom(-1);
}

void Plot::disableTools()
{
    if (zoomIn())
        zoom(false);
}

bool Plot::panEnabled()
{
    return _panner->isEnabled();
}

Zoomer* Plot::zommer() const
{
    return _zoomer[0];
}

Panner* Plot::panner() const
{
    return _panner;
}

bool Plot::ReadFile(const QString &file_name)
{
    QFile InFile(file_name);                   //Добавить проверку расширения
    if (!InFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Plotter"), tr("Cannot read file "));
        qDebug() << "Cannot open file for reading: " << qPrintable(InFile.errorString());
        return false;
    }
    int size = InFile.size() / sizeof(double);
    double temp;
    QVector<double> data;
    for (int i = 0; i < size; i++)
    {
        InFile.read(reinterpret_cast<char*>(&temp), sizeof(double));  //Добавить проверку 1 елемента
        data.push_back(temp);
    }
    InFile.close();

    CurveData *curve_data = (CurveData *)_curve->data();
    curve_data->values()->set_samples(data);

    rescale();
    replot();

    return true;
}

bool Plot::hasActiveTool()
{
    if (zoomIn() || _panner)
        return true;

    return false;
}

void Plot::rescale()
{
    CurveData *curve_data = (CurveData *)_curve->data();
    int size = curve_data->size();
    QVector<double> data = curve_data->values()->samples();

    QVector<double>::iterator min_result = std::min_element(data.begin(), data.end());
    int minPos = std::distance(data.begin(), min_result);
    int minY = data[minPos];
    QVector<double>::iterator max_result = std::max_element(data.begin(), data.end());
    int maxPos = std::distance(data.begin(), max_result);
    int maxY = data[maxPos];

    setAxisScale(QwtPlot::xBottom, 0.0, size/4, 10);
    setAxisScale(QwtPlot::yLeft, minY-200, maxY+200, 10);
    _zoomer[0]->setZoomBase();
}

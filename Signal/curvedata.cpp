#include "curvedata.h"
#include "Signal/signaldata.h"

CurveData::CurveData()
{
    _signal_data = new SignalData;
}

SignalData* CurveData::values() const
{
    return _signal_data;
}

const double* CurveData::x() const
{
    QVector<double> x;
    for (int i = 0; i < _signal_data->size(); i++)
        x.append(i);
    return x.data();
}

const double* CurveData::y() const
{
    return _signal_data->samples().data();
}

QPointF CurveData::sample(size_t i) const
{
    return _signal_data->value(i);
}

size_t CurveData::size() const
{
    return _signal_data->size();
}

QRectF CurveData::boundingRect() const
{
    return _signal_data->bounding_rect();
}

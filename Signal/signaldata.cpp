#include "signaldata.h"

#include <algorithm>
#include <QDebug>

SignalData::SignalData() : _sample_rate(1000), _bounding_rect(1.0, 1.0, -2.0, -2.0)
{
    _samples.reserve(1000);
}

SignalData::SignalData(const SignalData &other)
{
    _samples = other.samples();
    _sample_rate = other.sample_rate();
    AdjustBoundingRect();
}

SignalData::SignalData(const QVector<double> &samples)
{
    _samples = samples;
    AdjustBoundingRect();
}

void SignalData::set_samples(const QVector<double> &samples)
{
    _samples = samples;
    AdjustBoundingRect();
}

const QVector<double> SignalData::samples() const
{
    return _samples;
}

void SignalData::set_sample_rate(const unsigned short sample_rate)
{
    if (_sample_rate == sample_rate)
        return;

    _sample_rate = sample_rate;
}

unsigned short SignalData::sample_rate() const
{
    return _sample_rate;
}

int SignalData::size() const
{
    return _samples.size();
}

QRectF SignalData::bounding_rect() const
{
    return _bounding_rect;
}

QPointF SignalData::value(int index) const

{
    if (index > _samples.size())
        qDebug() << "Error: index is out of bounds";
    const double x = index;
    const double y = _samples[index];
    return QPointF(x, y);
}

void SignalData::AdjustBoundingRect()
{
    QVector<double> data = _samples;
    QVector<double>::iterator max_result = std::max_element(data.begin(), data.end());
    int maxPos = std::distance(data.begin(), max_result);

    const double x = _samples.size();
    const double y = _samples[maxPos];

    _bounding_rect.setRect(0.0, 0.0, x, y);
}

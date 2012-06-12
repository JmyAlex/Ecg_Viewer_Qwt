#ifndef CURVEDATA_H
#define CURVEDATA_H

#include <qwt_series_data.h>

class SignalData;

class CurveData : public QwtSeriesData<QPointF>
{
public:
    CurveData();

    SignalData *values() const;

    const double *x() const;
    const double *y() const;

    virtual QPointF sample( size_t i ) const;
    virtual size_t size() const;

    virtual QRectF boundingRect() const;

private:
    SignalData *_signal_data;

};

#endif // CURVEDATA_H

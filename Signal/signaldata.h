#ifndef SIGNALDATA_H
#define SIGNALDATA_H

#include <QVector>
#include <QRect>

class SignalData
{
public:
    SignalData();
    SignalData(const SignalData &other);
    SignalData(const QVector<double> &samples);

    void set_samples(const QVector<double> &samples);
    const QVector<double> samples() const;

    void set_sample_rate(const unsigned short sample_rate);
    unsigned short sample_rate() const;

    int size() const;
    QRectF bounding_rect() const;
    QPointF value(int index) const;

private:
    void AdjustBoundingRect();

    unsigned short _sample_rate;
    QVector<double> _samples;

    // Сделать ?
    // QVector<double> _x;  const double* x() const { return _x.data() }
    // QVector<double> _y;  const double* x() const { return _y.data() }

    QRectF _bounding_rect;
};

#endif // SIGNALDATA_H

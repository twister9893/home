#ifndef TSIPRIMITIVE_H
#define TSIPRIMITIVE_H

#include <QVector>
#include <QPointF>
#include <QColor>

class TsiPrimitive {
public:
    TsiPrimitive() {}

    void setPoints(QVector<QPointF> points) {m_points = points;}
    void setColor(QColor color) {m_color = color;}
    void setWidth(uint width) {m_width = width;}

    QColor getColor() {return m_color;}
    uint getWidth() {return m_width;}
    QVector<QPointF> & getPoints() {return m_points;}

private:
    QVector<QPointF> m_points;
    QColor m_color;
    uint m_width;
};

#endif // TSIPRIMITIVE_H

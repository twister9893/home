#ifndef POINT_H
#define POINT_H

#include "primitive.h"

class Point : public Primitive
{
public:
    Point(qint64 id, const QPointF &point=QPointF())
        : Primitive(id),
          _point(point) {}
    Point(qint64 id, qint64 anchor, const QPointF &point=QPointF())
        : Primitive(id,anchor),
          _point(point) {}

    void setPos(const QPointF &pos) {_point=pos;}

    QPointF pos() const {return _point;}
    QRectF bounding() const {return QRectF(_point, QSizeF(pen().widthF(), pen().widthF()));}
    PrimitiveType primitiveType() {return Primitive::Point;}

private:
    QPointF _point;
};

#endif // POINT_H

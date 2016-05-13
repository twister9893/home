#ifndef POINT_H
#define POINT_H

#include "primitive.h"

class Point : public Primitive
{
public:
    Point(qint64 id, const QPointF &point=QPointF())
        : Primitive(id),
          point(point) {}
    Point(qint64 id, qint64 anchor, const QPointF &point=QPointF())
        : Primitive(id,anchor),
          point(point) {}

    void setPos(const QPointF &pos) {this->point=point;}

    QPointF pos() const {return this->point;}
    QRectF bounding() const {return QRectF();}
    PrimitiveType primitiveType() {return Point;}

private:
    QPointF point;
};

#endif // POINT_H

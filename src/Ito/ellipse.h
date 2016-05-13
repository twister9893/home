#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "primitive.h"

class Ellipse : public Primitive
{
public:
    Ellipse(qint64 id, const QPointF &center=QPointF(), const QRectF &rectangle=QRectF())
        : Primitive(id),
          center(center),
          rectangle(rectangle) {}
    Ellipse(qint64 id, qint64 anchor, const QPointF &center=QPointF(), const QRectF &rectangle=QRectF())
        : Primitive(id,anchor),
          center(center),
          rectangle(rectangle) {}

    virtual void setPos(const QPointF &pos) {this->center=pos;}
    void setRectangle(const QRectF &rectangle) {this->rectangle=rectangle;}

    virtual QPointF pos() const {return this->center;}
    QRectF rectangle() const {return this->rectangle;}
    virtual QRectF bounding() const {
        QRectF bounding(this->rectangle);
        bounding.moveCenter(this->center);
        return bounding;
    }
    virtual PrimitiveType primitiveType() {return Ellipse;}

private:
    QPointF center;
    QRectF rectangle;
};

#endif // ELLIPSE_H

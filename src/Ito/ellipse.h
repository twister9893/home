#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "primitive.h"

class Ellipse : public Primitive
{
public:
    Ellipse(qint64 id, const QPointF &center=QPointF(), const QRectF &rectangle=QRectF())
        : Primitive(id),
          _center(center),
          _rectangle(rectangle) {}
    Ellipse(qint64 id, qint64 anchor, const QPointF &center=QPointF(), const QRectF &rectangle=QRectF())
        : Primitive(id,anchor),
          _center(center),
          _rectangle(rectangle) {}

    virtual void setPos(const QPointF &pos) {this->_center=pos;}
    void setRectangle(const QRectF &rectangle) {this->_rectangle=rectangle;}

    virtual QPointF pos() const {return this->_center;}
    QRectF rectangle() const {return this->_rectangle;}
    virtual QRectF bounding() const {
        QRectF bounding(this->_rectangle);
        bounding.moveCenter(this->_center);
        return bounding;
    }
    virtual PrimitiveType primitiveType() const {return Primitive::Ellipse;}

private:
    QPointF _center;
    QRectF _rectangle;
};

#endif // ELLIPSE_H

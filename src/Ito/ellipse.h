#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "primitive.h"

class Ellipse : public Primitive
{
public:
    Ellipse(qint64 id, const QRectF &rectangle=QRectF())
        : Primitive(id),
          _rectangle(rectangle) {}
    Ellipse(qint64 id, qint64 anchor, const QRectF &rectangle=QRectF())
        : Primitive(id,anchor),
          _rectangle(rectangle) {}

    virtual void setPos(const QPointF &pos) {_rectangle.moveTo(pos);}
    void setRectangle(const QRectF &rectangle) {_rectangle=rectangle;}

    virtual QPointF pos() const {return _rectangle.center();}
    QRectF rectangle() const {return _rectangle;}
    virtual QRectF bounding() const {return _rectangle;}
    virtual PrimitiveType primitiveType() const {return Primitive::Ellipse;}

private:
    QRectF _rectangle;
};

#endif // ELLIPSE_H

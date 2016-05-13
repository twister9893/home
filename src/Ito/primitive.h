#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QPen>
#include <QBrush>
#include "object.h"

class Primitive : public Object
{
public:
    enum PrimitiveType {
        Point=0,
        Line,
        Rect,
        Polyline,
        Polygon,
        Ellipse,
        Arc,
        Sector
    };

    Primitive(qint64 id)
        : Object(id),
          _rotation(0.0),
          _scalable(true) {}
    Primitive(qint64 id, qint64 anchor)
        : Object(id,anchor),
          _rotation(0.0),
          _scalable(true) {}

    virtual ~Primitive() {}

    void setPen(const QPen & pen) {this->_pen=pen;}
    void setBrush(const QBrush & brush) {this->_brush=brush;}
    void setRotation(qreal angle) {this->_rotation=angle;}
    void setScalable(bool scalable) {this->_scalable=scalable;}

    QPen pen() const {return this->_pen;}
    QBrush brush() const {return this->_brush;}
    qreal rotation() const {return this->_rotation;}
    bool isScalable() const {return this->_scalable;}
    ObjectType objectType() const {return Object::Primitive;}

    virtual PrimitiveType primitiveType() const=0;

private:
    QPen _pen;
    QBrush _brush;
    qreal _rotation;
    bool _scalable;
};

#endif // PRIMITIVE_H

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
          rotation(0.0),
          scalable(true) {}
    Primitive(qint64 id, qint64 anchor)
        : Object(id,anchor),
          rotation(0.0),
          scalable(true) {}

    virtual ~Primitive();

    void setPen(const QPen & pen) {this->pen=pen;}
    void setBrush(const QBrush & pen) {this->brush=brush;}
    void setRotation(qreal angle) {this->rotation=angle;}
    void setScalable(bool scalable) {this->scalable=scalable;}

    QPen pen() const {return this->pen;}
    QBrush brush() const {return this->brush;}
    qreal rotation() const {return this->rotation;}
    bool isScalable() const {return this->scalable;}
    ObjectType objectType() const {return Primitive;}

    virtual PrimitiveType primitiveType() const=0;

private:
    QPen pen;
    QBrush brush;
    qreal rotation;
    bool scalable;
};

#endif // PRIMITIVE_H

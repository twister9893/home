#ifndef TARGET_H
#define TARGET_H

#include "object.h"

class Target : public Object
{
public:
    enum TargetIff {
        Iff_Friend=0,
        Iff_Foe,
        Iff_Unidentified
    };

    enum TargetType {
        Type_Ship=0,
        Type_Submarine,
        Type_Aircraft,
        Type_Unidentified
    };

    Target(qint64 id, TargetIff iff = Iff_Unidentified, TargetType type = Type_Unidentified)
        : Object(id),
          _iff(iff),
          _type(type),
          _altitude(0.0),
          _course(0.0),
          _speed(0.0) {}
    Target(qint64 id, qint64 anchor, TargetIff iff = Iff_Unidentified, TargetType type = Type_Unidentified)
        : Object(id,anchor),
          _iff(iff),
          _type(type),
          _altitude(0.0),
          _course(0.0),
          _speed(0.0) {}

    virtual ~Target() {}

    void setIff(TargetIff iff) {_iff = iff;}
    void setType(TargetType type) {_type = type;}
    void setPos(const QPointF &pos) {_pos = pos;}
    void setAltitude(qreal altitude) {_altitude = altitude;}
    void setCourse(qreal course) {_course = course;}
    void setSpeed(qreal speed) {_speed = speed;}

    TargetIff iff() const {return _iff;}
    TargetType type() const {return _type;}
    QPointF pos() const {return _pos;}
    qreal altitude() const {return _altitude;}
    qreal course() const {return _course;}
    qreal speed() const {return _speed;}

    QRectF bounding() const {return QRectF();}
    ObjectType objectType() const {return Object::Target;}

private:
    TargetIff _iff;
    TargetType _type;
    //_subtype
    QPointF _pos;
    qreal _altitude;
    qreal _course;
    qreal _speed;
};

#endif // TARGET_H

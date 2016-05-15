#ifndef OBJECT_H
#define OBJECT_H

#include <QRectF>

class Object
{
public:
    enum ObjectType {
        Target=0,
        Primitive
    };

    Object(qint64 id)
        : _id(id),
          _anchor(-1),
          _visible(true) {}

    Object(qint64 id, qint64 anchor)
        : _id(id),
          _anchor(anchor),
          _visible(true) {}

    virtual ~Object() {}

//    void setId(qint64 id) {this->id=id;}
    void setAnchor(qint64 id) {this->_anchor=id;}
    void setVisible(bool visible) {this->_visible=visible;}
    virtual void setPos(const QPointF &pos)=0;

    qint64 id() const {return _id;}
    qint64 anchor() const {return _anchor;}
    bool hasAnchor() const {return _anchor >= 0;}
    bool isVisible() const {return _visible;}
    virtual QPointF pos() const=0;
    virtual ObjectType objectType() const=0;
    virtual QRectF bounding() const=0;

private:
    qint64 _id;
    qint64 _anchor;
    bool _visible;
};

#endif // OBJECT_H

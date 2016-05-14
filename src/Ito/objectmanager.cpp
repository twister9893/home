#include "objectmanager.h"

bool ObjectManager::addObject(Object *object)
{
    if(_objects.find(object->id()) == _objects.end()) {
        _objects.insert(object->id(), object);
        return true;
    } else {
        return false;
    }
}

bool ObjectManager::removeObject(qint64 id)
{
    if(_objects.find(id) != _objects.end()) {
        _objects.remove(id);
        return true;
    } else {
        return false;
    }
}

Object* ObjectManager::object(qint64 id, bool *ok) const
{
    if(ok) {
        *ok = _objects.find(id) != _objects.end();
    }
    return _objects.value(id, NULL);
}

void ObjectManager::draw(QPainter *painter)
{
    for(QMap< qint64,Object* >::iterator i = _objects.begin(); i != _objects.end(); ++i) {
        if(!(*i)->isVisible())
            continue;

        switch((*i)->objectType()) {
            case Object::Primitive:
                drawPrimitive(painter, static_cast<Primitive*>(*i));
                break;
            default:
                break;
        }
    }
}

void ObjectManager::drawPrimitive(QPainter *painter, Primitive *primitive)
{
    //TODO ANCHORS


    if(!painter || !primitive)
        return;

    painter->save();
    painter->setPen(primitive->pen());
    painter->setBrush(primitive->brush());

//    painter->translate((qreal)(painter->device()->width()) / 2, (qreal)(painter->device()->height()) / 2);
    qreal s = (qreal)( qMin(painter->device()->width(), painter->device()->height())) / _coreState.scale;
    if(primitive->isScalable()) {
        painter->scale(s,s);
        painter->translate(_coreState.offset);
    } else {
        painter->translate(_coreState.offset * s);
    }

    switch(primitive->primitiveType()) {
        case Primitive::Point: {
            painter->drawPoint(primitive->pos());
            break;
        }
        case Primitive::Ellipse: {
            painter->drawEllipse(primitive->bounding());
            break;
        }
        default:
            break;
    }
    painter->restore();
}

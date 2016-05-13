#include "objectmanager.h"

ObjectManager::ObjectManager()
{

}

bool ObjectManager::addObject(Object *object)
{
    if(this->objects.find(object->id()) == this->objects.end()) {
        this->objects.insert(object->id(), object);
        return true;
    } else {
        return false;
    }
}

bool ObjectManager::removeObject(qint64 id)
{
    if(this->objects.find(id) != this->objects.end()) {
        this->objects.remove(id);
        return true;
    } else {
        return false;
    }
}

Object* ObjectManager::object(qint64 id, bool *ok) const
{
    if(ok) {
        *ok = this->objects.find(id) != this->objects.end();
    }
    return this->objects.value(id, NULL);
}

void ObjectManager::draw(QPainter *painter)
{
    for(QMap< qint64,Object* >::iterator i = this->objects.begin(); i != this->objects.end(); ++i) {
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
    if(!painter || !primitive)
        return;

    painter->save();
    painter->setPen(primitive->pen());
    painter->setBrush(primitive->brush());
    if(primitive->isScalable()) {
        qreal sx = (qreal)(painter->device()->width()) / coreState.scale;
        qreal sy = (qreal)(painter->device()->height()) / coreState.scale;;
        painter->scale(sx,sy);
    }
    painter->translate(coreState.offset);

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


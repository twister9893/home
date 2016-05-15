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

Object* ObjectManager::object(qint64 id) const
{
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
            case Object::Target:
                drawTarget(painter, static_cast<Target*>(*i));
            default:
                break;
        }
    }
}

void ObjectManager::getFullOffset(Object *anchor, qreal *dx, qreal *dy, QPaintDevice *device)
{
    if(!dx || !dy || !anchor)
        return;
    if(anchor->objectType() != Object::Primitive) {
        *dx += anchor->pos().x();
        *dy += anchor->pos().y();
    } else {
        Primitive *primitive = static_cast<Primitive*>(anchor);
        if(primitive->isScalable()) {
            *dx += anchor->pos().x();
            *dy += anchor->pos().y();
        } else {
            qreal s = (qreal)( _coreState.scale / qMin(device->width(), device->height()) );
            *dx += anchor->pos().x() * s;
            *dy += anchor->pos().y() * s;
        }
    }

    if(anchor->hasAnchor()) {
        getFullOffset(_objects[anchor->anchor()], dx, dy, device);
    }
    return;
}

void ObjectManager::drawTarget(QPainter *painter, Target *target)
{
    if(!painter || !target)
        return;

    painter->save();

    QPen pen;
    pen.setWidthF(2.0);
    switch(target->iff()) {
        case Target::Iff_Friend:
            pen.setColor(QColor(220,0,0));
            break;
        case Target::Iff_Foe:
            pen.setColor(QColor(0,0,220));
            break;
        case Target::Iff_Unidentified:
            pen.setColor(QColor(0,220,0));
            break;
    }
    painter->setPen(pen);

    //Проход по всем якорям для получения полного смещения
    qreal dx=target->pos().x();
    qreal dy=target->pos().y();
    qreal s = (qreal)( qMin(painter->device()->width(), painter->device()->height()) ) / _coreState.scale;
    if(target->hasAnchor()) {
        getFullOffset(_objects[target->anchor()], &dx, &dy, painter->device());
    }
    painter->translate(_coreState.offset * s);
    painter->translate(dx*s, dy*s);

    painter->rotate(target->course());

    switch(target->type()) {
        case Target::Type_Ship:
            painter->drawLine(QLine(0,0,-5,-4));
            painter->drawLine(QLine(0,0,5,-4));
            painter->drawLine(QLine(-5,-4,-5,-20));
            painter->drawLine(QLine(5,-4,5,-20));
            painter->drawLine(QLine(-5,-20,5,-20));
            break;
        case Target::Type_Submarine:
            painter->drawLine(QLine(-5,0,5,0));
            painter->drawLine(QLine(-5,0,-5,-20));
            painter->drawLine(QLine(5,0,5,-15));
            painter->drawLine(QLine(-5,-20,5,-15));
            break;
        case Target::Type_Aircraft:
            painter->drawLine(QLine(0,0,0,-20));
            painter->drawLine(QLine(-5,-20,5,-20));
            break;
    }

    painter->restore();
}

void ObjectManager::drawPrimitive(QPainter *painter, Primitive *primitive)
{
    if(!painter || !primitive)
        return;

    painter->save();
    painter->setPen(primitive->pen());
    painter->setBrush(primitive->brush());

    //Проход по всем якорям для получения полного смещения
    qreal dx=0.0, dy=0.0;
    if(primitive->hasAnchor()) {
        getFullOffset(_objects[primitive->anchor()], &dx, &dy, painter->device());
    }

    //****МОЖНО СДЕЛАТЬ КРАСИВЕЕ****
    //Scalable значит, что pos() возвращает метры, иначе пиксели
    qreal s = (qreal)( qMin(painter->device()->width(), painter->device()->height()) ) / _coreState.scale;
    if(primitive->isScalable()) {
        painter->scale(s,s);
        painter->translate(_coreState.offset);
        painter->translate(dx, dy);
    } else {
        if(primitive->hasAnchor()) {
            //Домножаем на масштабный коэффициент, т.к. не применялась масштабная матрица как выше
            //Не применяем масштабную матрицу т.к. не scalable объекты должны рисоваться в пикселях
            painter->translate(_coreState.offset * s);
            painter->translate(dx*s, dy*s);
        }
    }
    //*****************************

    painter->rotate(primitive->rotation());

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

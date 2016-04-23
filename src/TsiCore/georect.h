#ifndef _GEORECT_H_
#define _GEORECT_H_

#include "geopoint.h"

class GeoRect {
public:
    GeoRect() {}
    GeoRect(const GeoPoint &topLeft, const GeoPoint &bottomRight)
        : m_topLeft(topLeft),m_bottomRight(bottomRight) {}
    GeoRect(const GeoPoint &topLeft, qreal width, qreal height)
        : m_topLeft(topLeft) {
        bool isOk=true;
        isOk&=m_bottomRight.setProjection(topLeft.projection());
        isOk&=m_bottomRight.setReper(topLeft.reperF(),topLeft.reperL());
        isOk&=m_bottomRight.setXYZ(topLeft.x()+width, topLeft.y()-height, topLeft.z());
        if(!isOk)
            qCritical() << "GeoRect: error in bottom right initialization";
    }

    bool setProjection(GeoPoint::Projection projection) {
        bool isOk=true;
        isOk&=m_topLeft.setProjection(projection);
        isOk&=m_bottomRight.setProjection(projection);
        return isOk;
    }
    bool setReper(qreal f, qreal l) {
        bool isOk=true;
        isOk&=m_topLeft.setReper(f,l);
        isOk&=m_bottomRight.setReper(f,l);
        return isOk;
    }

    void setTopLeft(const GeoPoint &topLeft) {m_topLeft=topLeft;}
    void setBottomRight(const GeoPoint &bottomRight) {m_bottomRight=bottomRight;}
    bool setSize(qreal width, qreal height) {
        bool isOk=true;
        isOk&=m_bottomRight.setProjection(m_topLeft.projection());
        isOk&=m_bottomRight.setReper(m_topLeft.reperF(),m_topLeft.reperL());
        isOk&=m_bottomRight.setXYZ(m_topLeft.x()+width, m_topLeft.y()-height, m_topLeft.z());
        return isOk;
    }

    GeoPoint topLeft() const {return m_topLeft;}
    GeoPoint bottomRight() const {return m_bottomRight;}
    qreal width() const {return m_bottomRight.x()-m_topLeft.x();}
    qreal height() const {return m_topLeft.y()-m_bottomRight.y();}
    qreal area() const {return width()*height();}

private:
    GeoPoint m_topLeft;
    GeoPoint m_bottomRight;
};

#endif //_GEORECT_H_

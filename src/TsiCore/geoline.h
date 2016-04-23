#ifndef _GEOLINE_H_
#define _GEOLINE_H_

#include <math.h>
#include "geopoint.h"

class GeoLine {
public:
    GeoLine() {}
    GeoLine(const GeoPoint &p1, const GeoPoint &p2)
        : m_p1(p1),m_p2(p2) {}
    GeoLine(const GeoPoint &p1, qreal dx2, qreal dy2)
        : m_p1(p1) {
        bool isOk=true;
        isOk&=m_p2.setProjection(p1.projection());
        isOk&=m_p2.setReper(p1.reperF(),p1.reperL());
        isOk&=m_p2.setXYZ(p1.x()+dx2, p1.y()+dy2, p1.z());
        if(!isOk)
            qCritical() << "GeoLine: error in p2 initialization";
    }

    bool setProjection(GeoPoint::Projection projection) {
        bool isOk=true;
        isOk&=m_p1.setProjection(projection);
        isOk&=m_p2.setProjection(projection);
        return isOk;
    }
    bool setReper(qreal f, qreal l) {
        bool isOk=true;
        isOk&=m_p1.setReper(f,l);
        isOk&=m_p2.setReper(f,l);
        return isOk;
    }

    void setPoints(const GeoPoint &p1, const GeoPoint &p2) {m_p1=p1;m_p2=p2;}
    void setPoints(const GeoPoint &p1, qreal dx2, qreal dy2) {
        m_p1=p1;
        bool isOk=true;
        isOk&=m_p2.setProjection(p1.projection());
        isOk&=m_p2.setReper(p1.reperF(),p1.reperL());
        isOk&=isOk=m_p2.setXYZ(p1.x()+dx2, p1.y()+dy2, p1.z());
        if(!isOk)
            qCritical() << "GeoLine: error in p2 setting";
    }

    GeoPoint p1() const {return m_p1;}
    GeoPoint p2() const {return m_p2;}
    qreal length() const {return sqrt(pow(p2.x()-p1.x(),2)+pow(p2.y()-p1.y(),2));}

private:
    GeoPoint m_p1;
    GeoPoint m_p2;
};

#endif //_GEOLINE_H_

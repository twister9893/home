#ifndef _GEOPOINT_H_
#define _GEOPOINT_H_

#include <QDebug>
#include "sysmath.h"

class GeoPoint {
public:
    enum Projection {
        Gauss=0,
        Mercator
    };

    GeoPoint()
        : m_x(0.0),m_y(0.0),m_f(0.0),m_l(0.0),m_altitudo(0.0), m_reperF(0.0),m_reperL(0.0), m_projection(Gauss) {}
//    GeoPoint(qreal reperF, qreal reperL, Projection projection=Gauss)
//        : m_x(0.0),m_y(0.0),m_f(0.0),m_l(0.0),m_altitudo(0.0), m_reperF(reperF),m_reperL(reperL), m_projection(projection) {}
    GeoPoint(qreal x, qreal y, qreal z=0.0, qreal reperF=0.0, qreal reperL=0.0, Projection projection=Gauss)
        : m_x(0.0),m_y(0.0),m_f(0.0),m_l(0.0),m_altitudo(z), m_reperF(reperF),m_reperL(reperL), m_projection(projection) {
        if(!setXYZ(x,y,z))
            qCritical() << "GeoPoint: error in XY initialization";
    }

    bool setProjection(Projection projection) {
        if(updateXY(m_reperF,m_reperL,projection)) {
            m_projection=projection;
            return true;
        }
        return false;
    }
    bool setReper(qreal f, qreal l) {
        if(updateXY(f,l,m_projection)) {
            m_reperF=f;
            m_reperL=l;
            return true;
        }
        return false;
    }

    bool setX(qreal x) {
        if(updateFL(m_reperF,m_reperL,m_projection)) {
            m_x=x;
            return true;
        }
        return false;
    }
    bool setY(qreal y) {
        if(updateFL(m_reperF,m_reperL,m_projection)) {
            m_y=y;
            return true;
        }
        return false;
    }
    bool setXYZ(qreal x, qreal y, qreal z=0.0) {
//        if(updateFL(m_reperF,m_reperL,m_projection)) {
            m_x=x;
            m_y=y;
            m_altitudo=z;
            return true;
//        }
//        return false;
    }

    bool setF(qreal f) {
        if(updateXY(m_reperF,m_reperL,m_projection)) {
            m_f=f;
            return true;
        }
        return false;
    }
    bool setL(qreal l) {
        if(updateXY(m_reperF,m_reperL,m_projection)) {
            m_l=l;
            return true;
        }
        return false;
    }
    bool setFLA(qreal f, qreal l, qreal altitudo=0.0) {
        if(updateXY(m_reperF,m_reperL,m_projection)) {
            m_f=f;
            m_l=l;
            m_altitudo=altitudo;
            return true;
        }
        return false;
    }
    void setA(qreal altitudo) {m_altitudo = altitudo;}

    Projection projection() const {return m_projection;}
    qreal reperF() const {return m_reperF;}
    qreal reperL() const {return m_reperL;}
    qreal x() const {return m_x;}
    qreal y() const {return m_y;}
    qreal z() const {return m_altitudo;}
    qreal f() const {return m_f;}
    qreal l() const {return m_l;}
    qreal altitudo() const {return m_altitudo;}

private:
    bool updateXY(qreal reperF, qreal reperL, Projection projection) {
        double x,y;
        int res=CFLXY(reperF,reperL,m_f,m_l,&x,&y,projection);
        if(!res) {
            m_x=x;
            m_y=y;
            return true;
        }
        return false;
    }
    bool updateFL(qreal reperF, qreal reperL, Projection projection) {
        double f,l;
        int res=CXYFL(reperF,reperL,m_x,m_y,&f,&l,projection);
        if(!res) {
            m_f=f;
            m_l=l;
            return true;
        }
        return false;
    }

    Projection m_projection;
    qreal m_reperF,m_reperL;
    qreal m_f,m_l;
    qreal m_x,m_y;
    qreal m_altitudo;
};

#endif //_GEOPOINT_H_

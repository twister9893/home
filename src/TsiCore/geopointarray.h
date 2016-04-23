#ifndef _GEOPOINTARRAY_H_
#define _GEOPOINTARRAY_H_

#include <QVector>
#include "geopoint.h"

class GeoPointArray : public QVector<GeoPoint> {
public:
    bool setProjection(GeoPoint::Projection projection) {
        bool isOk=true;
        foreach (GeoPoint point, *this) {isOk&=point.setProjection(projection);}
        return isOk;
    }
    bool setReper(qreal f, qreal l) {
        bool isOk=true;
        foreach (GeoPoint point, *this) {isOk&=point.setReper(f,l);}
        return isOk;
    }

//    qreal* dataXY() {
//        qreal data[] = new qreal[2*size()];
//        int i=0;
//        foreach (GeoPoint point, *this) {
//            data[i*2+0]=point.x();
//            data[i*2+1]=point.y();
//            ++i;
//        }
//        return data;
//    }
//    qreal* dataXYZ() {
//        qreal data[] = new qreal[3*size()];
//        int i=0;
//        foreach (GeoPoint point, *this) {
//            data[i*3+0]=point.x();
//            data[i*3+1]=point.y();
//            data[i*3+2]=point.z();
//            ++i;
//        }
//        return data;
//    }
};

#endif //_GEOPOINTARRAY_H_

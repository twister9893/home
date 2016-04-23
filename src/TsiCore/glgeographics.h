#ifndef _GLGEOGRAPHICS_H_
#define _GLGEOGRAPHICS_H_

#include <QPen>
#include <QBrush>

#include "georect.h"

class GlGeoGraphics {
public:
    void setPen(const QPen &pen) {m_pen=pen;}
    void setBrush(const QBrush &brush) {m_brush=brush;}

    QPen pen() const {return m_pen;}
    QBrush brush() const {return m_brush;}

    virtual void draw() const=0;
    virtual GeoRect boundingRect() const=0;

private:
    QPen m_pen;
    QBrush m_brush;
};

#endif //_GLGEOGRAPHICS_H_

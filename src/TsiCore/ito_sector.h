#ifndef ITO_SECTOR
#define ITO_SECTOR

#include "ito_arc.h"

class ItoSector : public ItoArc {
public:
    ItoSector(int id, const Point &center=Point(), double semiMajorAxis=0.0, double semiMinorAxis=0.0,
           double startAngle=0.0, double width=0.0,
           double innerSemiMajorAxis=0.0, double innerSemiMinorAxis=0.0)
        : ItoArc(id,center,semiMajorAxis,semiMinorAxis,startAngle,width),
          m_innerSemiMajorAxis(innerSemiMajorAxis),
          m_innerSemiMinorAxis(innerSemiMinorAxis) {}
    ItoSector(int id, int anchor, const Point &center=Point(), double semiMajorAxis=0.0, double semiMinorAxis=0.0,
           double startAngle=0.0, double width=0.0,
           double innerSemiMajorAxis=0.0, double innerSemiMinorAxis=0.0)
        : ItoArc(id,anchor,center,semiMajorAxis,semiMinorAxis,startAngle,width),
          m_innerSemiMajorAxis(innerSemiMajorAxis),
          m_innerSemiMinorAxis(innerSemiMinorAxis) {}

    void setInnerSemiMajorAxis(double innerSemiMajorAxis) {m_innerSemiMajorAxis=innerSemiMajorAxis;}
    void setInnerSemiMinorAxis(double innerSemiMinorAxis) {m_innerSemiMinorAxis=innerSemiMinorAxis;}

    double getInnerSemiMajorAxis() const {return m_innerSemiMajorAxis;}
    double getInnerSemiMinorAxis() const {return m_innerSemiMinorAxis;}
    Rect getBounding() const {

    }
    PrimitiveType getPrimitiveType() {return Primitive_Sector;}

    void draw() {
        if(!getVisibility())
            return;
    }

private:
    double m_innerSemiMajorAxis;
    double m_innerSemiMinorAxis;
};

#endif // ITO_SECTOR


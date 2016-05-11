#ifndef ITO_ELLIPSE
#define ITO_ELLIPSE

#include "ito_primitive.h"
#include "point.h"

class ItoEllipse : public ItoPrimitive {
public:
    ItoEllipse(int id, const Point &center=Point(), double semiMajorAxis=0.0, double semiMinorAxis=0.0)
        : ItoPrimitive(id),
          m_center(center),
          m_semiMajorAxis(semiMajorAxis),
          m_semiMinorAxis(semiMinorAxis) {}
    ItoEllipse(int id, int anchor, const Point &center=Point(), double semiMajorAxis=0.0, double semiMinorAxis=0.0)
        : ItoPrimitive(id,anchor),
          m_center(center),
          m_semiMajorAxis(semiMajorAxis),
          m_semiMinorAxis(semiMinorAxis) {}

    virtual void setPos(const Point &point) {m_center=point;}
    void setSemiMajorAxis(double semiMajorAxis) {m_semiMajorAxis=semiMajorAxis;}
    void setSemiMinorAxis(double semiMinorAxis) {m_semiMinorAxis=semiMinorAxis;}

    virtual Point getPos() const {return m_center;}
    double getSemiMajorAxis() const {return m_semiMajorAxis;}
    double getSemiMinorAxis() const {return m_semiMinorAxis;}
    virtual Rect getBounding() const {

    }
    virtual PrimitiveType getPrimitiveType() {return Primitive_Ellipse;}

    virtual void draw() {
        if(!getVisibility())
            return;
    }

private:
    Point m_center;
    double m_semiMajorAxis;
    double m_semiMinorAxis;
};

#endif // ITO_ELLIPSE


#ifndef ITO_ARC
#define ITO_ARC

#include "ito_ellipse.h"

class ItoArc : public ItoEllipse {
public:
    ItoArc(int id, const Point &center=Point(), double semiMajorAxis=0.0, double semiMinorAxis=0.0,
           double startAngle=0.0, double width=0.0)
        : ItoEllipse(id,center,semiMajorAxis,semiMinorAxis),
          m_startAngle(startAngle),
          m_width(width) {}
    ItoArc(int id, int anchor, const Point &center=Point(), double semiMajorAxis=0.0, double semiMinorAxis=0.0,
           double startAngle=0.0, double width=0.0)
        : ItoEllipse(id,anchor,center,semiMajorAxis,semiMinorAxis),
          m_startAngle(startAngle),
          m_width(width) {}

    void setStartAngle(double startAngle) {m_startAngle=startAngle;}
    void setWidth(double width) {m_width=width;}

    double getStartAngle() const {return m_startAngle;}
    double getWidth() const {return m_width;}
    virtual Rect getBounding() const {

    }
    virtual PrimitiveType getPrimitiveType() {return Primitive_Arc;}

    virtual void draw() {
        if(!getVisibility())
            return;
    }

private:
    double m_startAngle;
    double m_width;
};

#endif // ITO_ARC


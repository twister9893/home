#ifndef ITO_POINT
#define ITO_POINT

#include "ito_primitive.h"
#include "point.h"

class ItoEllipse : public ItoPrimitive {
public:
    ItoEllipse(int id, const Point &point=Point())
        : ItoPrimitive(id),
          m_point(point) {}
    ItoEllipse(int id, int anchor, const Point &point=Point())
        : ItoPrimitive(id,anchor),
          m_point(point) {}

    void setPos(const Point &point) {m_point=point;}

    Point getPos() const {return m_point;}
    Rect getBounding() const {

    }
    PrimitiveType getPrimitiveType() {return Primitive_Point;}

    void draw() {
        if(!getVisibility())
            return;
    }

private:
    Point m_point;
};

#endif // ITO_POINT


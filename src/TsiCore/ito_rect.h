#ifndef ITO_RECT
#define ITO_RECT

#include "ito_primitive.h"

class ItoPolyline : public ItoPrimitive {
public:
    ItoPolyline(int id, const Rect &rect)
        : ItoPrimitive(id),
          m_rect(rect) {}

    ItoPolyline(int id, int anchor, const Rect &rect)
        : ItoPrimitive(id,anchor),
          m_rect(rect) {}

    void setRect(const Rect &rect) {m_rect=rect;}
    void setPos(Point point) {
        double horizontalShift=m_rect.getTopLeft().getHorizontalShiftTo(point);
        double verticalShift=m_rect.getTopLeft().getVerticalShiftTo(point);
        m_rect.setTopLeft(point);
        m_rect.setBottomRight(m_rect.getBottomRight().getPointShiftedTo(horizontalShift,verticalShift);
    }

    Rect getRect() const {return m_rect;}
    Point getPos() const {return m_rect.getTopLeft();}
    Rect getBounding() const {return m_rect;}
    PrimitiveType getPrimitiveType() {return Primitive_Rect;}

    void draw() {
        if(!getVisibility())
            return;
    }

private:
    Rect m_rect;
};

#endif // ITO_RECT


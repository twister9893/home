#ifndef ITO_LINE
#define ITO_LINE

#include "ito_primitive.h"
#include "line.h"

class ItoLine : public ItoPrimitive {
public:
    ItoLine(int id, const Line &line)
        : ItoPrimitive(id),
          m_line(line) {}

    ItoLine(int id, int anchor,  const Line &line)
        : ItoPrimitive(id,anchor),
          m_line(line) {}

    void setLine(const Line &line) {m_line=line;}
    void setPos(Point point) {
        double horizontalShift=m_line.getP1().getHorizontalShiftTo(point);
        double verticalShift=m_line.getP1().getVerticalShiftTo(point);
        m_line.setP1(point);
        m_line.setP2(m_line.getP2().getPointShiftedTo(horizontalShift,verticalShift));
    }

    Line getLine() const {return m_line;}
    Point getPos() const {return m_line.getP1();}
    Rect getBounding() const {

    }
    PrimitiveType getPrimitiveType() {return Primitive_Line;}

    void draw() {
        if(!getVisibility())
            return;
    }

private:
    Line m_line;
};

#endif // ITO_LINE


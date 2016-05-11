#ifndef ITO_POLYGON
#define ITO_POLYGON

#include <vector>
#include "ito_primitive.h"

class ItoPolygon : public ItoPrimitive {
public:
    ItoPolygon(int id, const std::vector<Point> &points)
        : ItoPrimitive(id),
          m_points(points) {}

    ItoPolygon(int id, int anchor, const std::vector<Point> &points)
        : ItoPrimitive(id,anchor),
          m_points(points) {}

    void setPoints(const std::vector &points) {m_points=points;}
    void setPos(Point point) {
        double horizontalShift=m_points.front().getHorizontalShiftTo(point);
        double verticalShift=m_points.front().getVerticalShiftTo(point);
        for(std::vector<Point>::iterator i=m_points.begin(); i!=m_points.end(); ++i) {
            (*i)=(*i).getShiftedTo(horizontalShift,verticalShift);
        }
    }

    std::vector<Point> getPoints() const {return m_points;}
    Point getPos() const {return m_points.front();}
    Rect getBounding() const {

    }
    PrimitiveType getPrimitiveType() {return Primitive_Polygon;}

    void draw() {
        if(!getVisibility())
            return;
    }

private:
    std::vector<Point> m_points;
};

#endif // ITO_POLYGON


#ifndef RECT
#define RECT

#include "point.h"

class Rect {
public:
    Rect(const Point &topLeft=Point(), const Point &bottomRight=Point())
        : m_topLeft(topLeft),
          m_bottomRight(bottomRight) {}

    void setTopLeft(const Point &topLeft) {m_topLeft=topLeft;}
    void setBottomRight(const Point &bottomRight) {m_bottomRight=bottomRight;}

    Point getTopLeft() const {return m_topLeft;}
    Point getBottomRight() const {return m_bottomRight;}
    double getArea() const {
        return m_topLeft.getHorizontalShiftTo(m_bottomRight) * m_bottomRight.getVerticalShiftTo(m_topLeft);
    }

private:
    Point m_topLeft;
    Point m_bottomRight;
};

#endif // RECT


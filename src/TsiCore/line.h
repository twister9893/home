#ifndef LINE
#define LINE

#include "point.h"

class Line {
public:
    Line(const Point &p1=Point(), const Point &p2=Point())
        : m_p1(p1),
          m_p2(p2) {}

    void setP1(const Point &p1) {m_p1=p1;}
    void setP2(const Point &p2) {m_p2=p2;}

    Point getP1() const {return m_p1;}
    Point getP2() const {return m_p2;}
    double getLength() const {
        return m_p1.getDistanceTo(m_p2);
    }

private:
    Point m_p1;
    Point m_p2;
};

#endif // LINE


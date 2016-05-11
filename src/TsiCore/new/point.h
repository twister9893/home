#ifndef POINT
#define POINT

//#include "geo.h"

class Point {
public:
    enum Type {
        Geographic=0,
        Cartesian,
        Polar
    };

    virtual Type getType() const=0;
    virtual double getDistanceTo(const Point &coord) const=0;
    virtual double getHorizontalShiftTo(const Point &coord) const=0;
    virtual double getVerticalShiftTo(const Point &coord) const=0;
    virtual Point getPointShiftedTo(double horizontalShift, double verticalShift) const=0;
};

class GeoPoint : public Point {
public:
    enum System {
        WGS84=0,
        SK42,
        PZ90,
        PZ90_02
    };

    void setF(double f) {m_f=f;}
    void setL(double l) {m_l=l;}
    void setAltitute(double altitude) {m_altitude=altitude;}
    void setSystem(System system) {m_system=system;}

    double getF() const {return m_f;}
    double getL() const {return m_l;}
    double getAltitude() const {return m_altitude;}
    System getSystem() const {return m_system;}

    Type getType() const {return Geographic;}

    double getDistanceTo(const Point &coord) const {

    }

    double getHorizontalShiftTo(const Point &coord) const {

    }

    double getVerticalShiftTo(const Point &coord) const {

    }

    Point getPointShiftedTo(double horizontalShift, double verticalShift) const {

    }

private:
    double m_f;
    double m_l;
    double m_altitude;
    System m_system;
};

class CartesianPoint : public Point {
public:
    enum Unit {
        Meter=0,
        Pixel
    };

    void setX(double x) {m_x=x;}
    void setY(double y) {m_x=x;}
    void setZ(double z) {m_x=x;}
    void setUnit(Unit unit) {m_unit=unit;}

    double getX() const {return m_x;}
    double getY() const {return m_y;}
    double getZ() const {return m_z;}
    Unit getUnit() const {return m_unit;}

    Type getType() const {return Cartesian;}

    double getDistanceTo(const Point &coord) const {

    }

    double getHorizontalShiftTo(const Point &coord) const {

    }

    double getVerticalShiftTo(const Point &coord) const {

    }

    Point getPointShiftedTo(double horizontalShift, double verticalShift) const {

    }

private:
    double m_x;
    double m_y;
    double m_z;
    Unit m_unit;
};

class PolarPoint : public Point {
public:
    enum AngleReference {
        North=0,
        Course
    };

    void setAngle(double angle) {m_angle=angle;}
    void setDistance(double distance) {m_distance=distance;}
    void setZ(double z) {m_z=z;}
    void setAngleReference(AngleReference angleReference) {m_angleReference=angleReference;}

    double getAngle() const {return m_angle;}
    double getDistance() const {return m_distance;}
    double getZ() const {return m_z;}
    AngleReference getAngleReference() const {return m_angleReference;}

    Type getType() const {return Polar;}

    double getDistanceTo(const Point &coord) const {

    }

    double getHorizontalShiftTo(const Point &coord) const {

    }

    double getVerticalShiftTo(const Point &coord) const {

    }

    Point getPointShiftedTo(double horizontalShift, double verticalShift) const {

    }

private:
    double m_angle;
    double m_distance;
    double m_z;
    AngleReference m_angleReference;
};

#endif // POINT


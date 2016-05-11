#ifndef ITO_PRIMITIVE
#define ITO_PRIMITIVE

#include "ito_object.h"
#include "style.h"

class ItoPrimitive : public ItoObject {
public:
    enum PrimitiveType {
        Primitive_Point=0,
        Primitive_Line,
        Primitive_Rect,
        Primitive_Polyline,
        Primitive_Polygon,
        Primitive_Ellipse,
        Primitive_Arc,
        Primitive_Sector
    };

    ItoPrimitive(int id)
        : ItoObject(id) {}
    ItoPrimitive(int id, int anchor)
        : ItoObject(id,anchor) {}
    virtual ~ItoPrimitive();

    void setStyle(const Style & style) {m_style=style;}
    void setRotation(double angle) {m_rotation=angle;}

    Style getStyle() const {return m_style;}
    double getRotation() const {return m_rotation;}
    ObjectType getObjectType() const {return Object_Primitive;}


    virtual PrimitiveType getPrimitiveType() const=0;

private:
    Style m_style;
    double m_rotation;
};

#endif // ITO_PRIMITIVE


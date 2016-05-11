#ifndef ITO_OBJECT
#define ITO_OBJECT

#include "rect.h"

class ItoObject {
public:
    enum ObjectType {
        Object_Target=0,
        Object_Primitive
    };

    ItoObject(int id)
        : m_id(id),
          m_anchor(0),
          m_visibility(true) {}

    ItoObject(int id, int anchor)
        : m_id(id),
          m_anchor(anchor),
          m_visibility(true) {}

    virtual ~ItoObject();

    void setId(int id) {m_id=id;}
    void setAnchor(int id) {m_anchor=id;}
    void setVisibility(bool visibility) {m_visibility=visibility;}
    virtual void setPos(const Point &point)=0;

    int getId() const {return m_id;}
    int getAnchor() const {return m_anchor;}
    bool getVisibility() const {return m_visibility;}
    virtual Point getPos() const=0;
    virtual ObjectType getObjectType() const=0;
    virtual Rect getBounding() const=0;

    virtual void draw();

private:
    int m_id;
    int m_anchor;
    bool m_visibility;
};

#endif // ITO_OBJECT


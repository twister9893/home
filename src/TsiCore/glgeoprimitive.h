#ifndef _GLGEOPRIMITIVE_H_
#define _GLGEOPRIMITIVE_H_

#include <GL/gl.h>

#include "geopointarray.h"
#include "glgeographics.h"

class GlGeoPrimitive : public GlGeoGraphics {
public:
    GlGeoPrimitive()
        : m_type(GL_POINTS), m_vertexBuffer(0), m_indexBuffer(0) {}
    GlGeoPrimitive(GLenum type, GeoPointArray points)
        : m_type(type), m_vertexBuffer(0), m_indexBuffer(0) {
        setPoints(points);
    }

    bool setProjection(GeoPoint::Projection projection) {
        bool isOk=m_points.setProjection(projection);
        if(isOk)
            bufferizeVertexArray();
        return isOk;
    }
    bool setReper(qreal f, qreal l) {
        bool isOk=m_points.setReper(f,l);
        if(isOk)
            bufferizeVertexArray();
        return isOk;
    }

    void setType(GLenum type) {m_type=type;}
    void setPoints(GeoPointArray & points) {
        m_points=points;
        bufferizeVertexArray();
    }

    GLenum type() const {return m_type;}
    GeoPointArray points() const {return m_points;}

    void draw() const {
//        qDebug() << brush.color().redF() << brush.color().greenF() << brush.color().blueF();

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3,GL_DOUBLE,0,m_vertexBuffer);
        glColor4f(brush().color().redF(),brush().color().greenF(),brush().color().blueF(),brush().color().alphaF());
        glDrawElements(m_type,m_points.size(),GL_UNSIGNED_SHORT,m_indexBuffer);

//        if()
//        {
//            glColor4f(pen().color().redF(),pen().color().greenF(),pen().color().blueF(),pen().color().alphaF());
//            glDrawElements(GL_LINE_LOOP,m_points.size(),GL_UNSIGNED_SHORT,m_indexBuffer);
//        }
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    GeoRect boundingRect() const {
        return GeoRect();
    }

private:
    void bufferizeVertexArray() {
        m_vertexBuffer=(GLdouble*)realloc(m_vertexBuffer,m_points.size()*3*sizeof(GLdouble));
        m_indexBuffer=(GLushort*)realloc(m_indexBuffer,m_points.size()*sizeof(GLushort));
        int i=0;
        foreach (GeoPoint point, m_points) {
            m_vertexBuffer[i*3+0]=point.x();
            m_vertexBuffer[i*3+1]=point.y();
            m_vertexBuffer[i*3+2]=point.z();
            m_indexBuffer[i]=i;
            ++i;
        }
    }

    GLenum m_type;
    GeoPointArray m_points;
    GLdouble *m_vertexBuffer;
    GLushort *m_indexBuffer;
};

#endif //_GLGEOPRIMITIVE_H_

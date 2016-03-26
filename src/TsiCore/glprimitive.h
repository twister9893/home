#ifndef _GLPRIMITIVE_H_
#define _GLPRIMITIVE_H_

#include <GL/gl.h>
#include "matrix.h"

#include <sys/time.h>

class GlPrimitive
{
public:
    GlPrimitive() : m_type(0),m_vertices(0),m_vertexCount(0),m_indexes(0),m_indexCount(0),m_orderedIndexes(0),m_orderedIndexCount(0),
                    m_r(0),m_g(0),m_b(0),m_a(255),m_rContour(0),m_gContour(0),m_bContour(0),m_aContour(0),
                    m_pointSize(m_defaultPointSize),m_lineWidth(m_defaultLineWidth),m_transform(new Matrix3(OLD_TO_NEW)), m_isTransformed(false),
                    m_reperFL(std::pair<GLdouble,GLdouble>(0.0,0.0)) {}
    GlPrimitive(GLenum type) : m_type(type),m_vertices(0),m_vertexCount(0),m_indexes(0),m_indexCount(0),m_orderedIndexes(0),m_orderedIndexCount(0),
                               m_r(0),m_g(0),m_b(0),m_a(255),m_rContour(0),m_gContour(0),m_bContour(0),m_aContour(0),
                               m_pointSize(m_defaultPointSize),m_lineWidth(m_defaultLineWidth),m_transform(new Matrix3(OLD_TO_NEW)), m_isTransformed(false),
                               m_reperFL(std::pair<GLdouble,GLdouble>(0.0,0.0)) {}
    ~GlPrimitive() {/*if(m_transform) delete m_transform;*/}

    bool setType(GLenum type) {m_type = type; return true;}
    void setReperFL(GLdouble F, GLdouble L) {m_reperFL.first=F; m_reperFL.second=L; setVerticesFLZ(m_verticesFLZ,m_vertexCount);}
    bool setVerticesFLZ(GLdouble *verticesFLZ, GLushort vertexCount)
    {
        if(!(verticesFLZ && vertexCount))
            return false;
        if(m_verticesFLZ)
            free(m_verticesFLZ);
        m_verticesFLZ = verticesFLZ;
        m_vertexCount = vertexCount;

        m_vertices = (GLdouble*)realloc(m_vertices, m_vertexCount*3*sizeof(GLdouble));
        for(int i=0; i<m_vertexCount; ++i)
        {
            CFLXY(m_reperFL.first, m_reperFL.second, m_verticesFLZ[i*3+0], m_verticesFLZ[i*3+1], &m_vertices[i*3+0], &m_vertices[i*3+1]);
            m_vertices[i*3+2] = m_verticesFLZ[i*3+2];
        }
        return true;
    }
    bool setVertices(GLdouble *vertices, GLushort vertexCount)
    {
        if(!(vertices && vertexCount))
            return false;
        if(m_vertices)
            free(m_vertices);
        m_vertices = vertices;
        m_vertexCount = vertexCount;

        m_verticesFLZ = (GLdouble*)realloc(m_verticesFLZ, m_vertexCount*3*sizeof(GLdouble));
        for(int i=0; i<m_vertexCount; ++i)
        {
            CFLXY(m_reperFL.first, m_reperFL.second, m_vertices[i*3+0], m_vertices[i*3+1], &m_verticesFLZ[i*3+0], &m_verticesFLZ[i*3+1]);
            m_verticesFLZ[i*3+2] = m_vertices[i*3+2];
        }
        return true;
    }
    void clearVertices()
    {
        if(m_vertices)
        {
            free(m_vertices);
            m_vertices = 0;
        }
        if(m_verticesFLZ)
        {
            free(m_verticesFLZ);
            m_verticesFLZ = 0;
        }
        m_vertexCount = 0;
    }
    bool setIndexes(GLushort *indexes, GLushort indexCount)
    {
        if(!(indexes && indexCount))
            return false;
        if(m_indexes)
            free(m_indexes);
        m_indexes = indexes;
        m_indexCount = indexCount;
        return true;
    }
    void clearIndexes()
    {
        if(m_indexes)
        {
            free(m_indexes);
            m_indexes = 0;
        }
        m_indexCount = 0;
    }

    bool setContourIndexes(GLushort *indexes, GLushort indexCount)
    {
        if(!(indexes && indexCount))
            return false;
        if(m_orderedIndexes)
            free(m_orderedIndexes);
        m_orderedIndexes = indexes;
        m_orderedIndexCount = indexCount;
        return true;
    }
    void clearContourIndexes()
    {
        if(m_orderedIndexes)
        {
            free(m_orderedIndexes);
            m_orderedIndexes = 0;
        }
        m_orderedIndexCount = 0;
    }
    void addVertexFLZ(GLdouble F, GLdouble L, GLdouble z)
    {
        m_vertexCount++;
        m_verticesFLZ = (GLdouble*)realloc(m_verticesFLZ, 3*m_vertexCount*sizeof(GLdouble));
        m_verticesFLZ[m_vertexCount*3-3] = F;
        m_verticesFLZ[m_vertexCount*3-2] = L;
        m_verticesFLZ[m_vertexCount*3-1] = z;

        CFLXY(m_reperFL.first, m_reperFL.second, m_verticesFLZ[m_vertexCount*3-3], m_verticesFLZ[m_vertexCount*3-2], &m_vertices[m_vertexCount*3-3], &m_vertices[m_vertexCount*3-2]);
        m_vertices[m_vertexCount*3-1] = z;

        m_indexCount++;
        m_indexes = (GLushort*)realloc(m_indexes, m_indexCount*sizeof(GLushort));
        m_indexes[m_indexCount-1] = m_indexCount-1;

        m_orderedIndexCount++;
        m_orderedIndexes = (GLushort*)realloc(m_orderedIndexes, m_orderedIndexCount*sizeof(GLushort));
        m_orderedIndexes[m_orderedIndexCount-1] = m_orderedIndexCount-1;
    }
    void addVertexFL(GLdouble F, GLdouble L) {addVertexFLZ(F,L,0.0);}
    void addVertex(GLdouble x, GLdouble y, GLdouble z)
    {
        m_vertexCount++;
        m_vertices = (GLdouble*)realloc(m_vertices, 3*m_vertexCount*sizeof(GLdouble));
        m_vertices[m_vertexCount*3-3] = x;
        m_vertices[m_vertexCount*3-2] = y;
        m_vertices[m_vertexCount*3-1] = z;

        CFLXY(m_reperFL.first, m_reperFL.second, m_vertices[m_vertexCount*3-3], m_vertices[m_vertexCount*3-2], &m_verticesFLZ[m_vertexCount*3-3], &m_verticesFLZ[m_vertexCount*3-2]);
        m_verticesFLZ[m_vertexCount*3-1] = z;

        m_indexCount++;
        m_indexes = (GLushort*)realloc(m_indexes, m_indexCount*sizeof(GLushort));
        m_indexes[m_indexCount-1] = m_indexCount-1;

        m_orderedIndexCount++;
        m_orderedIndexes = (GLushort*)realloc(m_orderedIndexes, m_orderedIndexCount*sizeof(GLushort));
        m_orderedIndexes[m_orderedIndexCount-1] = m_orderedIndexCount-1;
    }
    inline void addVertex(GLdouble x, GLdouble y) {addVertex(x,y,0.0);}

    inline GLdouble* vertices() {return m_vertices;}
    inline GLdouble* verticesFLZ() {return m_verticesFLZ;}

    GLushort* indexes()
    {
//        if(m_vertexCount > m_indexCount)
        if(!m_indexes)
        {
            m_indexCount = m_vertexCount;
//            if(m_indexes)
//                free(m_indexes);
            m_indexes = getOrderedIndexes(m_indexCount);
        }
        return m_indexes;
    }

    GLushort* orderedIndexes()
    {
//        if(m_vertexCount > m_orderedIndexCount)
        if(!m_orderedIndexes)
        {
            m_orderedIndexCount = m_vertexCount;
//            if(m_orderedIndexes)
//                free(m_orderedIndexes);
            m_orderedIndexes = getOrderedIndexes(m_orderedIndexCount);
        }
        return m_orderedIndexes;
    }

    GLdouble* xAt(uint i)
    {
        if(i >= m_vertexCount)
            return 0;
        return &m_vertices[i*3];
    }
    GLdouble* yAt(uint i)
    {
        if(i >= m_vertexCount)
            return 0;
        return &m_vertices[i*3+1];
    }
    GLdouble* zAt(uint i)
    {
        if(i >= m_vertexCount)
            return 0;
        return &m_vertices[i*3+2];
    }

    inline GLdouble* xFirst() {return xAt(0);}
    inline GLdouble* yFirst() {return yAt(0);}
    inline GLdouble* zFirst() {return zAt(0);}

    inline GLdouble* xLast() {return xAt(m_vertexCount-1);}
    inline GLdouble* yLast() {return yAt(m_vertexCount-1);}
    inline GLdouble* zLast() {return zAt(m_vertexCount-1);}

    inline GLushort vertexCount() {return m_vertexCount;}
    inline GLushort indexCount() {return m_indexCount;}

    inline void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a=255) {m_r=r; m_g=g; m_b=b; m_a=a;}
    inline void setColorContour(GLubyte r, GLubyte g, GLubyte b, GLubyte a=255) {m_rContour=r; m_gContour=g; m_bContour=b; m_aContour=a;}

    inline GLubyte colorR() {return m_r;}
    inline GLubyte colorG() {return m_g;}
    inline GLubyte colorB() {return m_b;}
    inline GLubyte colorA() {return m_a;}

    inline GLubyte colorContourR() {return m_rContour;}
    inline GLubyte colorContourG() {return m_gContour;}
    inline GLubyte colorContourB() {return m_bContour;}
    inline GLubyte colorContourA() {return m_aContour;}

    void setPointSize(GLfloat pointSize) {m_pointSize = pointSize;}
    void setLineWidth(GLfloat lineWidth) {m_lineWidth = lineWidth;}

    GLfloat pointSize() {return m_pointSize;}
    GLfloat lineWidth() {return m_lineWidth;}

    void setTranslate(double dx, double dy) {*m_transform = m_transform->translate(dx,dy); m_isTransformed=true;}
    void setRotate(double angle) {*m_transform = m_transform->rotate(angle); m_isTransformed=true;}
    void setIdentity() {*m_transform = m_transform->identity(); m_isTransformed=false;}

    bool draw()
    {
        struct timeval tvs,tve;
        gettimeofday(&tvs,0);

        if(!m_vertices)
            return false;
        glPointSize(m_pointSize);
        glLineWidth(m_lineWidth);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        if(m_isTransformed)
        {
//          m_transform->print();
            double *m4=toMatrix4(m_transform->get());
            glMultTransposeMatrixd(m4);
            free(m4);
        }

        gettimeofday(&tve,0);
//        printf("DrawPolygon: prepareTime %d\n", tve.tv_usec - tvs.tv_usec);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3,GL_DOUBLE,0,m_vertices);
        glColor4ub(m_r,m_g,m_b,m_a);
        GLushort *_indexes = indexes();
        //printf("GlPrimitive:\nindexes %d\nvertices %d\n",m_indexCount, m_vertexCount);
        glDrawElements(m_type,m_indexCount,GL_UNSIGNED_SHORT,_indexes);

        gettimeofday(&tvs,0);
//        printf("DrawPolygon: polygonDraw %d\n", tvs.tv_usec - tve.tv_usec);

        if(m_rContour || m_gContour || m_bContour || m_aContour)
        {
            glColor4ub(m_rContour,m_gContour,m_bContour,m_aContour);
            GLushort *_orderedIndexes = orderedIndexes();
            glDrawElements(GL_LINE_LOOP,m_orderedIndexCount,GL_UNSIGNED_SHORT,_orderedIndexes);
//            printf("indexes: %d, vertices %d\n",m_orderedIndexCount, m_vertexCount);
            gettimeofday(&tve,0);
//            printf("DrawPolygon: contourDraw %d\n", tve.tv_usec - tvs.tv_usec);
        }

        glDisableClientState(GL_VERTEX_ARRAY);

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        return true;
    }

    GLdouble area()
    {
        if(!m_vertexCount)
            return 0.0;
        GLdouble minX=*xFirst(),minY=*yFirst(),maxX=*xFirst(),maxY=*yFirst();
        for(int i=1; i<m_vertexCount; ++i)
        {
            if(*xAt(i) < minX)
                minX = *xAt(i);
            if(*xAt(i) > maxX)
                maxX = *xAt(i);
            if(*yAt(i) < minY)
                minY = *yAt(i);
            if(*yAt(i) > maxY)
                maxY = *yAt(i);
        }
        return (maxX-minX)*(maxY-minY);
    }

    void print()
    {
        printf("[GL PRIMITIVE INFO]\n");
        printf("\tType: %d\n",m_type);
        printf("\tVertex count: %d\n",m_vertexCount);
        printf("\tIndex count: %d\n",m_indexCount);
        printf("\tColor: %d %d %d %d\n",m_r,m_g,m_b,m_a);
        printf("\tColor contour: %d %d %d %d\n",m_rContour,m_gContour,m_bContour,m_aContour);
        printf("\tPoint size: %.1f\n",m_pointSize);
        printf("\tLine width: %.1f\n",m_lineWidth);
        printf("\tArea: %.1f\n\n",area());
    }

    void clear()
    {
        clearVertices();
        clearIndexes();
        clearContourIndexes();
        m_type = 0;
        m_r = 0;
        m_g = 0;
        m_b = 0;
        m_a = 0;
        m_rContour = 0;
        m_gContour = 0;
        m_bContour = 0;
        m_aContour = 0;
        m_pointSize = m_defaultPointSize;
        m_lineWidth = m_defaultLineWidth;
        m_transform->identity();
    }

private:
    static GLushort* getOrderedIndexes(uint size)
    {
        GLushort* indexes = (GLushort*)malloc(size*sizeof(GLushort));
        for(uint i=0; i < size; i++)
            indexes[i] = i;
        return indexes;
    }

    double *toMatrix4(const double *matrix3) {
        double *matrix4 = (double*)malloc(16*sizeof(double));
        matrix4[0]=matrix3[0];  matrix4[1]=matrix3[1];  matrix4[2]=0.0;  matrix4[3]=matrix3[2];
        matrix4[4]=matrix3[3];  matrix4[5]=matrix3[4];  matrix4[6]=0.0;  matrix4[7]=matrix3[5];
        matrix4[8]=0.0;         matrix4[9]=0.0;         matrix4[10]=1.0; matrix4[11]=0.0;
        matrix4[12]=0.0;        matrix4[13]=0.0;        matrix4[14]=0.0; matrix4[15]=1.0;
        return matrix4;
    }

//    std::pair<GLdouble,GLdouble> m_topLeftFL;
//    std::pair<GLdouble,GLdouble> m_bottomRightFL;

    GLenum m_type;
    std::pair<GLdouble,GLdouble> m_reperFL;
    GLdouble *m_verticesFLZ;
    GLdouble *m_vertices;
    GLushort m_vertexCount;
    GLushort *m_indexes;
    GLushort m_indexCount;
    GLushort *m_orderedIndexes;
    GLushort m_orderedIndexCount;

    GLubyte m_r,m_g,m_b,m_a;
    GLubyte m_rContour,m_gContour,m_bContour,m_aContour;

    GLfloat m_pointSize;
    GLfloat m_lineWidth;

    Matrix3 *m_transform;
    bool m_isTransformed;

    static const GLfloat m_defaultPointSize = 8;
    static const GLfloat m_defaultLineWidth = 2;
};

#endif //_GLPRIMITIVE_H_

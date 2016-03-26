#ifndef _GLTESSELATOR_H_
#define _GLTESSELATOR_H_
//ПЕРЕДЕЛАТЬ НА КЛАСС

#include <GL/glu.h>
#include <ogrsf_frmts.h>
#include <vector>

typedef struct MapPolygon
{
    GLenum polygonType;
    GLdouble* pVertexFL;
    GLdouble* pVertex;
    GLushort vertexCount;
    GLushort vertexExternalCount;
    GLushort* pIndexes;
    GLushort indexesCount;
    GLenum type;
    OGREnvelope envFL;
    OGREnvelope env;
    GLdouble area;
    GLdouble minDepth;
    GLdouble maxDepth;
    GLfloat color[3];
    GLubyte colorb[3];
} MapPolygon;

MapPolygon* pTessPolygon=0;
GLUtesselator* ptess=0;

GLushort* pTessIndexHelper=0;
GLushort TessIndexHelperMax=0;

std::vector<GLushort> tessIndexes;
GLushort tessIndexesCount=0;

void tessBegin(GLenum type)
{
//    printf("tessBegin: %d\n",type);
    pTessPolygon->type=type;
    tessIndexesCount=0;
    tessIndexes.erase(tessIndexes.begin(),tessIndexes.end());
}

void tessEnd()
{
//    printf("tessEnd\n");
    pTessPolygon->indexesCount=tessIndexesCount;
    pTessPolygon->pIndexes=(GLushort*)malloc(sizeof(GLushort)*tessIndexesCount);
    for (int i=0;i<tessIndexesCount;i++)
        pTessPolygon->pIndexes[i]=tessIndexes[i];
}

void tessVertex(void* vertex_data)
{
    GLushort* pv=(GLushort*)vertex_data;
//    printf("tessVertex: %d %f %f\n",*pv,pTessPolygon->pVertexFL[(*pv)*3+0],pTessPolygon->pVertexFL[(*pv)*3+1]);
    tessIndexes.push_back(*pv);
    tessIndexesCount++;
}

void tessCombine(GLdouble coords[3],void* vertex_data[4],GLfloat weight[4],void** outData)
{
    printf("tessCombine\n");
}

void tessError(GLenum errno)
{
    printf("tessError: %d\n",errno);
}

void tessEdgeFlag(GLboolean flag)
{

}

void tesselatePolygon(MapPolygon* pPolygon,std::vector<int>* pstart,std::vector<int>* pcount)
{
    int cur;
    std::vector<int>::iterator it;

    pTessPolygon=pPolygon;
    if (!ptess)
    {
        ptess=gluNewTess();

        gluTessCallback(ptess,GLU_TESS_BEGIN,(void (*)())tessBegin);
        gluTessCallback(ptess,GLU_TESS_END,(void (*)())tessEnd);
        gluTessCallback(ptess,GLU_TESS_VERTEX,(void (*)())tessVertex);
        gluTessCallback(ptess,GLU_TESS_COMBINE,(void (*)())tessCombine);
        gluTessCallback(ptess,GLU_TESS_ERROR,(void (*)())tessError);
        gluTessCallback(ptess,GLU_TESS_EDGE_FLAG,(void (*)())tessEdgeFlag);

        TessIndexHelperMax=1024;
        pTessIndexHelper=(GLushort*)malloc(sizeof(GLushort)*TessIndexHelperMax);
        for (int i=0;i<TessIndexHelperMax;i++)
            pTessIndexHelper[i]=i;
    }

    if (pTessPolygon->vertexCount>=TessIndexHelperMax)
    {
        TessIndexHelperMax+=(TessIndexHelperMax*2>pTessPolygon->vertexCount)?TessIndexHelperMax:pTessPolygon->vertexCount*2;
        pTessIndexHelper=(GLushort*)realloc(pTessIndexHelper,sizeof(GLushort)*TessIndexHelperMax);
        for (int i=0;i<TessIndexHelperMax;i++)
            pTessIndexHelper[i]=i;
    }
//    printf("beginPolygon\n");
    gluTessBeginPolygon(ptess,0);
    for (it=pstart->begin(),cur=0;it!=pstart->end();it++,cur++)
    {
//	    printf("iterator %d, start %d, count %d\n",cur,(*pstart)[cur],(*pcount)[cur]);
//	    printf("beginContour\n");
        gluTessBeginContour(ptess);
        for (int i=0;i<(*pcount)[cur];i++)
        {
//    		    printf("%d: %f %f\n",*(pTessIndexHelper+(*pstart)[cur]+i),*(pTessPolygon->pVertexFL+(*pstart)[cur]*3+i*3),*(pTessPolygon->pVertexFL+(*pstart)[cur]*3+i*3+1));
            gluTessVertex(ptess,pTessPolygon->pVertexFL+(*pstart)[cur]*3+i*3,pTessIndexHelper+(*pstart)[cur]+i);
        }
//	    printf("endContour\n");
        gluTessEndContour(ptess);
    }
//    printf("endPolygon\n");
    gluTessEndPolygon(ptess);
}

#endif //_GLTESSELATOR_H_

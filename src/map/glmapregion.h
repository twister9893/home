#ifndef _GLMAPREGION_H_
#define _GLMAPREGION_H_

#include <vector>
#include <stdio.h>
#include "glprimitive.h"

#define PT_DEPARE 1
#define PT_LNDARE 2
#define PT_MAX    3

class GlMapRegion
{
public:

    class GlMapLayer
    {
    public:
        enum Type
        {
            Depare=1,
            Lndare
        };

        GlMapLayer()
            : m_type(Depare){}
        GlMapLayer(Type type, std::vector<GlPrimitive> polygons)
            : m_type(type), m_polygons(polygons) {}

        void setType(Type type) {m_type = type;}
        void setPolygons(std::vector<GlPrimitive> polygons) {m_polygons = polygons;}

        Type getType() {return m_type;}
        std::vector<GlPrimitive> & getPolygons() {return m_polygons;}

        GLubyte getR(bool isNight=false)
        {
            switch(m_type)
            {
            case Depare: return (isNight)?35:115;
            case Lndare: return (isNight)?70:200;
            }
        }
        GLubyte getG(bool isNight=false)
        {
            switch(m_type)
            {
            case Depare: return (isNight)?50:180;
            case Lndare: return (isNight)?60:185;
            }
        }
        GLubyte getB(bool isNight=false)
        {
            switch(m_type)
            {
            case Depare: return (isNight)?50:240;
            case Lndare: return (isNight)?50:120;
            }
        }
        GLubyte getA(bool isNight=false)
        {
            switch(m_type)
            {
            case Depare: return (isNight)?255:255;
            case Lndare: return (isNight)?255:255;
            }
        }

    private:
        Type m_type;
        std::vector<GlPrimitive> m_polygons;
    };

    GlMapRegion() {}
    GlMapRegion(const char *fileName, double f0, double l0, int mercator=0) {load(fileName,f0,l0,mercator);}

//    int load(const char *fileName, double f0, double l0, int mercator=0)
//    {
//        struct timeval tvs,tve;
//        gettimeofday(&tvs,0);

//        FILE *mapFile = fopen(fileName, "rb");
//        if(!mapFile)
//        {
//            printf("Load map ERROR: %s: No such file\n",fileName);
//            return 0;
//        }
//        m_fileName = fileName;
//        int vc=0;
//        int polygonCount = 0;
//        while(!feof(mapFile))
//        {
//            std::pair<GLenum,GlPrimitive> polygon;
//            fread(&(polygon.first), sizeof(GLenum), 1, mapFile);
//            GLenum type=0;
//            fread(&type, sizeof(GLenum), 1, mapFile);
////            polygon.second.setType(type);
//            polygon.second.setType(type);
////            fread(/*&(polygon.minDepth)*/0, sizeof(GLdouble), 1, mapFile);
//            fseek(mapFile,sizeof(GLdouble),SEEK_CUR);
////            fread(/*&(polygon.maxDepth)*/0, sizeof(GLdouble), 1, mapFile);
//            fseek(mapFile,sizeof(GLdouble),SEEK_CUR);

////            fread(&m_topLeftFL.first, sizeof(GLdouble), 1, mapFile);
//            fseek(mapFile,sizeof(GLdouble),SEEK_CUR);
////            fread(&m_bottomRightFL.second, sizeof(GLdouble), 1, mapFile);
//            fseek(mapFile,sizeof(GLdouble),SEEK_CUR);
////            fread(&m_bottomRightFL.first, sizeof(GLdouble), 1, mapFile);
//            fseek(mapFile,sizeof(GLdouble),SEEK_CUR);
////            fread(&m_topLeftFL.second, sizeof(GLdouble), 1, mapFile);
//            fseek(mapFile,sizeof(GLdouble),SEEK_CUR);

//            GLushort externalVertexCount=0;
//            fread(&externalVertexCount, sizeof(GLushort), 1, mapFile);
////            fseek(mapFile,sizeof(GLushort),SEEK_CUR);
//            GLushort vertexCount=0;
//            fread(&vertexCount, sizeof(GLushort), 1, mapFile);
////            printf("Read polygon %d: Vertex count %d, type %d\n", polygonCount, vertexCount, type);
//            for(int j = 0; j < vertexCount*3; j+=3) {
//                GLdouble F,L;
//                fread(&F, sizeof(GLdouble), 1, mapFile);
//                fread(&L, sizeof(GLdouble), 1, mapFile);
//                GLdouble x,y,z;
//                fread(&z, sizeof(GLdouble), 1, mapFile);
//                CFLXY(f0,l0,L,F,&x,&y, mercator);
//                polygon.second.addVertex(x,y,z/2);
//            }
//            vc+=vertexCount;

//            GLushort *contourIndexes = (GLushort*)malloc(externalVertexCount*sizeof(GLushort));
//            for(int i=0; i<externalVertexCount; ++i)
//                contourIndexes[i]=i;
//            polygon.second.setContourIndexes(contourIndexes,externalVertexCount);
////            printf("External indexes: %d\n",externalVertexCount);

//            GLushort indexCount;
//            GLushort *indexes;
//            fread(&indexCount, sizeof(GLushort), 1, mapFile);
//            indexes=(GLushort*)malloc(sizeof(GLushort)*indexCount);
//            memset(indexes, 0, sizeof(GLushort)*indexCount);
//            for(int j = 0; j < indexCount; j++) {
//              fread(&(indexes[j]), sizeof(GLushort), 1, mapFile);
//            }
//            polygon.second.setIndexes(indexes, indexCount);
////            polygon.second.print();
//            m_polygons.push_back(polygon);
//            ++polygonCount;
//        }
////        printf("Read polygons: FINISH\n");
//        fclose(mapFile);

//        sort(m_polygons.begin(),m_polygons.end(),comparePolygon);

////        printf("Load map FINISH: vertices %d (size %u kbytes)\n",vc,(uint)(sizeof(GLfloat)*3*vc/1024));
//        gettimeofday(&tve,0);
//        printf("Load map time: %d\n", tve.tv_usec - tvs.tv_usec);
//        return 1;
//    }

//    int load(const char *fileName, double f0, double l0, int mercator=0)
//    {
//        struct timeval tvs,tve;
//        gettimeofday(&tvs,0);

//        FILE *mapFile = fopen(fileName, "rb");
//        if(!mapFile)
//        {
//            printf("Load map ERROR: %s: No such file\n",fileName);
//            return 0;
//        }
//        m_fileName = fileName;
//        int vc=0;
//        int polygonCount = 0;

//        fseek(mapFile,0,SEEK_END);
//        long fileSize = ftell(mapFile);
////        printf("FILE SIZE: %d\n", fileSize);
//        rewind(mapFile);
//        char *data = (char*)malloc(fileSize);
//        fread(data,fileSize,1,mapFile);
//        fclose(mapFile);

//        long pos=0;
//        while(pos < fileSize)
//        {
//            std::pair<GLenum,GlPrimitive> polygon;
//            memcpy(&(polygon.first), &data[pos], sizeof(GLenum));
//            pos += sizeof(GLenum);

//            GLenum type=0;
//            memcpy(&type, &data[pos], sizeof(GLenum));
//            pos += sizeof(GLenum);
//            polygon.second.setType(type);

//            pos += sizeof(GLdouble)*6;
////            fread(/*&(polygon.minDepth)*/0, sizeof(GLdouble), 1, mapFile);
////            fread(/*&(polygon.maxDepth)*/0, sizeof(GLdouble), 1, mapFile);
////            fread(&m_topLeftFL.first, sizeof(GLdouble), 1, mapFile);
////            fread(&m_bottomRightFL.second, sizeof(GLdouble), 1, mapFile);
////            fread(&m_bottomRightFL.first, sizeof(GLdouble), 1, mapFile);
////            fread(&m_topLeftFL.second, sizeof(GLdouble), 1, mapFile);

//            GLushort externalVertexCount=0;
//            memcpy(&externalVertexCount, &data[pos], sizeof(GLushort));
//            pos += sizeof(GLushort);

//            GLushort vertexCount=0;
//            memcpy(&vertexCount, &data[pos], sizeof(GLushort));
//            pos += sizeof(GLushort);

//            for(int j = 0; j < vertexCount*3; j+=3)
//            {
//                GLdouble F,L;
//                memcpy(&F, &data[pos], sizeof(GLdouble));
//                pos += sizeof(GLdouble);
//                memcpy(&L, &data[pos], sizeof(GLdouble));
//                pos += sizeof(GLdouble);

//                GLdouble x,y,z;
//                memcpy(&z, &data[pos], sizeof(GLdouble));
//                pos += sizeof(GLdouble);
//                CFLXY(f0,l0,L,F,&x,&y, mercator);
//                polygon.second.addVertex(x,y,z/2);
//            }
//            vc+=vertexCount;

//            GLushort *contourIndexes = (GLushort*)malloc(externalVertexCount*sizeof(GLushort));
//            for(int i=0; i<externalVertexCount; ++i)
//                contourIndexes[i]=i;
//            polygon.second.setContourIndexes(contourIndexes,externalVertexCount);
////            printf("External indexes: %d\n",externalVertexCount);

//            GLushort indexCount;
//            memcpy(&indexCount, &data[pos], sizeof(GLushort));
//            pos += sizeof(GLushort);

//            GLushort *indexes;
//            indexes=(GLushort*)malloc(sizeof(GLushort)*indexCount);
//            memset(indexes, 0, sizeof(GLushort)*indexCount);
//            for(int j = 0; j < indexCount; j++)
//            {
//                memcpy(&(indexes[j]), &data[pos], sizeof(GLushort));
//                pos += sizeof(GLushort);
//            }
//            polygon.second.setIndexes(indexes, indexCount);
////            polygon.second.print();
//            m_polygons.push_back(polygon);
//            ++polygonCount;
//        }
////        printf("Read polygons: FINISH\n");

//        sort(m_polygons.begin(),m_polygons.end(),comparePolygon);

////        printf("Load map FINISH: vertices %d (size %u kbytes)\n",vc,(uint)(sizeof(GLfloat)*3*vc/1024));
//        gettimeofday(&tve,0);
//        printf("Load map time: %d\n", tve.tv_usec - tvs.tv_usec);
//        return 1;
//    }

    int load(const char *fileName)
    {
        struct timeval tvs,tve;
        gettimeofday(&tvs,0);

        FILE *mapFile = fopen(fileName, "rb");
        if(!mapFile)
        {
            printf("Load map ERROR: %s: No such file\n",fileName);
            return 0;
        }
        m_fileName = fileName;
        int vc=0;
//        int polygonCount = 0;

        fseek(mapFile,0,SEEK_END);
        long fileSize = ftell(mapFile);
//        printf("FILE SIZE: %d\n", fileSize);
        rewind(mapFile);
        char *data = (char*)malloc(fileSize);
        fread(data,fileSize,1,mapFile);
        fclose(mapFile);

        long pos=0;
        memcpy(&m_topLeftFL.first, &data[pos], sizeof(GLdouble));
        pos += sizeof(GLdouble);
        memcpy(&m_topLeftFL.second, &data[pos], sizeof(GLdouble));
        pos += sizeof(GLdouble);
        memcpy(&m_bottomRightFL.first, &data[pos], sizeof(GLdouble));
        pos += sizeof(GLdouble);
        memcpy(&m_bottomRightFL.second, &data[pos], sizeof(GLdouble));
        pos += sizeof(GLdouble);

        GLubyte layerCount;
        memcpy(&layerCount, &data[pos], sizeof(GLubyte));
        pos += sizeof(GLubyte);

        for(int i=0; i<layerCount; ++i)
        {
            GlMapLayer layer;

            GLenum layerType;
            memcpy(&layerType, &data[pos], sizeof(GLenum));
            pos += sizeof(GLenum);
            layer.setType(layerType);

            GLuint polygonCount;
            memcpy(&polygonCount, &data[pos], sizeof(GLuint));
            pos += sizeof(GLuint);

            for(int j=0; j<polygonCount; ++j)
            {
                GlPrimitive polygon;

                GLenum polygonType;
                memcpy(&polygonType, &data[pos], sizeof(GLenum));
                pos += sizeof(GLenum);
                polygon.setType(polygonType);

                GLushort externalVertexCount=0;
                memcpy(&externalVertexCount, &data[pos], sizeof(GLushort));
                pos += sizeof(GLushort);

                GLushort vertexCount=0;
                memcpy(&vertexCount, &data[pos], sizeof(GLushort));
                pos += sizeof(GLushort);

                for(int j = 0; j < vertexCount*3; j+=3)
                {
                    GLdouble F,L,z;
                    memcpy(&F, &data[pos], sizeof(GLdouble));
                    pos += sizeof(GLdouble);
                    memcpy(&L, &data[pos], sizeof(GLdouble));
                    pos += sizeof(GLdouble);
                    memcpy(&z, &data[pos], sizeof(GLdouble));
                    pos += sizeof(GLdouble);
                    polygon.addVertex(F,L,z/2);
                }
                vc+=vertexCount;

                GLushort *contourIndexes = (GLushort*)malloc(externalVertexCount*sizeof(GLushort));
                for(int i=0; i<externalVertexCount; ++i)
                    contourIndexes[i]=i;
                polygon.setContourIndexes(contourIndexes,externalVertexCount);
    //            printf("External indexes: %d\n",externalVertexCount);

                GLushort indexCount;
                memcpy(&indexCount, &data[pos], sizeof(GLushort));
                pos += sizeof(GLushort);

                GLushort *indexes;
                indexes=(GLushort*)malloc(sizeof(GLushort)*indexCount);
                memset(indexes, 0, sizeof(GLushort)*indexCount);
                for(int j = 0; j < indexCount; j++)
                {
                    memcpy(&(indexes[j]), &data[pos], sizeof(GLushort));
                    pos += sizeof(GLushort);
                }
                polygon.setIndexes(indexes, indexCount);
                layer.getPolygons().push_back(polygon);
            }
            sort(layer.getPolygons().begin(),layer.getPolygons().end(),comparePolygon);
            m_layers.push_back(layer);
        }

        gettimeofday(&tve,0);
        printf("Load map time: %d\n", tve.tv_usec - tvs.tv_usec);

        return 1;
    }

    void setCorners(std::pair<double,double> topLeftFL, std::pair<double,double> bottomRightFL);
    void setLayers(std::vector<GlMapLayer> layers) {m_layers = layers;}
    void addLayer(GlMapLayer layer) {m_layers.push_back(layer);}

    const char* getFileName() {return m_fileName.c_str();}
    std::pair<double,double> getTopLeftCorner() {return m_topLeftFL;}
    std::pair<double,double> getBottomRightCorner() {return m_bottomRightFL;}
    std::vector<GlMapLayer> & getLayers() {return m_polygons;}

    void draw(bool isNightMode)
    {
        int setCTime=0;
        int drawTime=0;
        for(std::vector< std::pair<GLenum,GlPrimitive> >::iterator i = m_polygons.begin(); i != m_polygons.end(); ++i)
        {
            struct timeval tvs,tve;
            gettimeofday(&tvs,0);
            if((*i).first == PT_LNDARE)
            {
                GLshort r=m_lndareNightR, g=m_lndareNightG, b=m_lndareNightB, a=m_lndareNightA;
                GLshort r1=m_lndareR, g1=m_lndareG, b1=m_lndareB, a1=m_lndareA;
                if(isNightMode)
                {
                    (*i).second.setColor(r,g,b,a);
                    (*i).second.setColorContour(r/2,g/2,b/2,a);
                }
                else
                {
                    (*i).second.setColor(r1,g1,b1,a1);
                    (*i).second.setColorContour(r1/2,g1/2,b1/2,a1);
                }
            }
            else
            if((*i).first == PT_DEPARE)
            {
                GLshort r=m_depareNightR, g=m_depareNightG, b=m_depareNightB, a=m_depareNightA;
                GLshort r1=m_depareR, g1=m_depareG, b1=m_depareB, a1=m_depareA;
                GLshort colorOffset=0;
                if((*i).second.zFirst())
                    colorOffset = *(*i).second.zFirst() / 3;
                r+=colorOffset; g+=colorOffset; b+=colorOffset;
                if((*i).second.zFirst())
                {
                    if(*(*i).second.zFirst() > -5)
                    {
                        r1+=colorOffset; g1+=colorOffset; b1+=colorOffset;
                    }
                    else
                    {
                        r1=212; g1=234; b1=238;
                    }
                }
                r=(r<0)?0:r; g=(g<0)?0:g; b=(b<0)?0:b;
                r1=(r1<0)?0:r1; g1=(g1<0)?0:g1; b1=(b1<0)?0:b1;

                if(isNightMode)
                {
                    (*i).second.setColor(r,g,b,a);
                    (*i).second.setColorContour(r/2,g/2,b/2,a);
                }
                else
                {
                    (*i).second.setColor(r1,g1,b1,a1);
                    (*i).second.setColorContour(r1/2,g1/2,b1/2,a1);
                }
            }
            gettimeofday(&tve,0);
//            printf("DrawMap: setColors time %d\n", tve.tv_usec-tvs.tv_usec);
            setCTime += tve.tv_usec-tvs.tv_usec;
            (*i).second.setLineWidth(1.5);
            (*i).second.draw();
            gettimeofday(&tvs,0);
//            printf("DrawMap: drawPolygon time %d\n", tvs.tv_usec-tve.tv_usec);
            drawTime += tvs.tv_usec-tve.tv_usec;
        }
//        printf("DrawMap: setColors time %d\n", setCTime);
//        printf("DrawMap: drawPolygon time %d\n", drawTime);
    }

    void print()
    {
        printf("[GL MAP REGION INFO]\n");
        printf("\tFile name: %s\n",m_fileName.c_str());
        printf("\tTop left corner: %.2f  %.2f\n",m_topLeftFL.first, m_topLeftFL.second);
        printf("\tBottom right corner: %.2f  %.2f\n",m_bottomRightFL.first, m_bottomRightFL.second);
        printf("\tPolygon count: %d\n",m_polygons.size());
        int vertexCount=0;
        for(std::vector< std::pair<GLenum,GlPrimitive> >::iterator i = m_polygons.begin(); i != m_polygons.end(); ++i)
            vertexCount += (*i).second.vertexCount();
        printf("\tVertex count: %d\n",vertexCount);
    }

private:
    static bool comparePolygon(std::pair<GLenum,GlPrimitive> a, std::pair<GLenum,GlPrimitive> b)
    {
        return a.second.area()>b.second.area();
    }

    std::string m_fileName;
    std::pair<double,double> m_topLeftFL;
    std::pair<double,double> m_bottomRightFL;
    std::vector<GlMapLayer> m_layers;
};

#endif //_GLMAPREGION_H_

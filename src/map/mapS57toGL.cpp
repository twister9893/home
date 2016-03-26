#include <GL/glu.h>

#include <dirent.h>
#include <stdio.h>
#include <vector>

#include <ogrsf_frmts.h>
#include "system.h"

#include "gltesselator.h"

double f0=54.724423;
double l0=19.808993;

GLuint polygonCount=0;

int mercator = 0;

char areaStrings[][8]=
{
    "NONE",
    "DEPARE",
    "LNDARE",
};

#define PT_DEPARE 1
#define PT_LNDARE 2
#define PT_MAX    3

#define MAP_MAX 10000

//typedef struct MapPolygon
//{
//    GLenum polygonType;
//    GLdouble* pVertexFL;
//    GLdouble* pVertex;
//    GLushort vertexCount;
//    GLushort vertexExternalCount;
//    GLushort* pIndexes;
//    GLushort indexesCount;
//    GLenum type;
//    OGREnvelope envFL;
//    OGREnvelope env;
//    GLdouble area;
//    GLdouble minDepth;
//    GLdouble maxDepth;
//    GLfloat color[3];
//    GLubyte colorb[3];
//} MapPolygon;

std::vector<MapPolygon> polygons;

//MapPolygon* pTessPolygon=0;
//GLUtesselator* ptess=0;

//GLushort* pTessIndexHelper=0;
//GLushort TessIndexHelperMax=0;

//std::vector<GLushort> tessIndexes;
//GLushort tessIndexesCount=0;

//void tessBegin(GLenum type)
//{
////    printf("tessBegin: %d\n",type);
//    pTessPolygon->type=type;
//    tessIndexesCount=0;
//    tessIndexes.erase(tessIndexes.begin(),tessIndexes.end());
//}

//void tessEnd()
//{
////    printf("tessEnd\n");
//    pTessPolygon->indexesCount=tessIndexesCount;
//    pTessPolygon->pIndexes=(GLushort*)malloc(sizeof(GLushort)*tessIndexesCount);
//    for (int i=0;i<tessIndexesCount;i++)
//        pTessPolygon->pIndexes[i]=tessIndexes[i];
//}

//void tessVertex(void* vertex_data)
//{
//    GLushort* pv=(GLushort*)vertex_data;
////    printf("tessVertex: %d %f %f\n",*pv,pTessPolygon->pVertexFL[(*pv)*3+0],pTessPolygon->pVertexFL[(*pv)*3+1]);
//    tessIndexes.push_back(*pv);
//    tessIndexesCount++;
//}

//void tessCombine(GLdouble coords[3],void* vertex_data[4],GLfloat weight[4],void** outData)
//{
//    printf("tessCombine\n");
//}

//void tessError(GLenum errno)
//{
//    printf("tessError: %d\n",errno);
//}

//void tessEdgeFlag(GLboolean flag)
//{

//}

//void tesselatePolygon(MapPolygon* pPolygon,std::vector<int>* pstart,std::vector<int>* pcount)
//{
//    int cur;
//    std::vector<int>::iterator it;

//    pTessPolygon=pPolygon;
//    if (!ptess)
//    {
//        ptess=gluNewTess();

//        gluTessCallback(ptess,GLU_TESS_BEGIN,(void (*)())tessBegin);
//        gluTessCallback(ptess,GLU_TESS_END,(void (*)())tessEnd);
//        gluTessCallback(ptess,GLU_TESS_VERTEX,(void (*)())tessVertex);
//        gluTessCallback(ptess,GLU_TESS_COMBINE,(void (*)())tessCombine);
//        gluTessCallback(ptess,GLU_TESS_ERROR,(void (*)())tessError);
//        gluTessCallback(ptess,GLU_TESS_EDGE_FLAG,(void (*)())tessEdgeFlag);

//        TessIndexHelperMax=1024;
//        pTessIndexHelper=(GLushort*)malloc(sizeof(GLushort)*TessIndexHelperMax);
//        for (int i=0;i<TessIndexHelperMax;i++)
//            pTessIndexHelper[i]=i;
//    }

//    if (pTessPolygon->vertexCount>=TessIndexHelperMax)
//    {
//        TessIndexHelperMax+=(TessIndexHelperMax*2>pTessPolygon->vertexCount)?TessIndexHelperMax:pTessPolygon->vertexCount*2;
//        pTessIndexHelper=(GLushort*)realloc(pTessIndexHelper,sizeof(GLushort)*TessIndexHelperMax);
//        for (int i=0;i<TessIndexHelperMax;i++)
//            pTessIndexHelper[i]=i;
//    }
////    printf("beginPolygon\n");
//    gluTessBeginPolygon(ptess,0);
//    for (it=pstart->begin(),cur=0;it!=pstart->end();it++,cur++)
//    {
////	    printf("iterator %d, start %d, count %d\n",cur,(*pstart)[cur],(*pcount)[cur]);
////	    printf("beginContour\n");
//        gluTessBeginContour(ptess);
//        for (int i=0;i<(*pcount)[cur];i++)
//        {
////    		    printf("%d: %f %f\n",*(pTessIndexHelper+(*pstart)[cur]+i),*(pTessPolygon->pVertexFL+(*pstart)[cur]*3+i*3),*(pTessPolygon->pVertexFL+(*pstart)[cur]*3+i*3+1));
//            gluTessVertex(ptess,pTessPolygon->pVertexFL+(*pstart)[cur]*3+i*3,pTessIndexHelper+(*pstart)[cur]+i);
//        }
////	    printf("endContour\n");
//        gluTessEndContour(ptess);
//    }
////    printf("endPolygon\n");
//    gluTessEndPolygon(ptess);
//}

void loadContour(MapPolygon* pPolygon,OGRLinearRing* pRing,int start,int count)
{
    int isCW;
    OGRPoint point;

    isCW=pRing->isClockwise();
    for (int i=0;i<count;i++)
    {
        pRing->getPoint(isCW?count-i-1:i,&point);
        pPolygon->pVertexFL[start*3+i*3+0]=point.getX();
        pPolygon->pVertexFL[start*3+i*3+1]=point.getY();
        pPolygon->pVertexFL[start*3+i*3+2]=-pPolygon->minDepth;
    }
}

void loadLayer(int type,OGRDataSource* pDS)
{
    OGRLayer* pLayer;
//    OGRFeatureDefn* pLayerDefn;
    OGRFeature* pFeature;
    OGRGeometry* pGeometry;
//    OGRwkbGeometryType geoType;
    OGREnvelope env,envXY;
    struct timeval tvs,tv;

    if (!type || type>=PT_MAX) return;

    gettimeofday(&tvs,0);
    pLayer=pDS->GetLayerByName(areaStrings[type]);
    if (pLayer)
    {

        printf("Feature count: %d\n",pLayer->GetFeatureCount(1));
        if (pLayer->GetExtent(&env,1)==OGRERR_NONE)
        {
            printf("(%f  %f), (%f %f)\n",env.MinY,env.MinX,env.MaxY,env.MaxX);
            CFLXY(f0, l0,env.MinY,env.MinX, &envXY.MinX, &envXY.MinY,mercator);
            CFLXY(f0, l0,env.MaxY,env.MaxX, &envXY.MaxX, &envXY.MaxY,mercator);
            printf("(%f  %f), (%f %f)\n",envXY.MinX,envXY.MinY,envXY.MaxX,envXY.MaxY);
        }

        if (pLayer->GetExtent(&env,1)==OGRERR_NONE)
        {
//            if (minf>env.MinY) minf=env.MinY;
//            if (minl>env.MinX) minl=env.MinX;
//            if (maxf<env.MaxY) maxf=env.MaxY;
//            if (maxl<env.MaxX) maxl=env.MaxX;
        }
        pLayer->ResetReading();
        pFeature=pLayer->GetNextFeature();

        while (pFeature)
        {
            //printf("Name: %s\n",pFeature->GetDefnRef()->GetName());
            pGeometry=pFeature->GetGeometryRef();
            if (pGeometry && pGeometry->getGeometryType()==wkbPolygon)
            {
//		char* str;
                OGRPolygon* pPolygon;
                OGRLinearRing* pRing;
//                OGRPoint point;
                MapPolygon newPolygon={0,};
                int numVertex=0;
                std::vector<int> start;
                std::vector<int> count;
                int curStart=0;
//		int interiorCount=0;
//		printf("GeometryName: %s %d\n",pGeometry->getGeometryName(),pGeometry->getGeometryType());
//		pGeometry->exportToWkt(&str);
//		puts(str);
//		free(str);
                newPolygon.polygonType=type;

                for (int i=0;i<pFeature->GetFieldCount();i++)
                    if (pFeature->IsFieldSet(i))
                    {
//			printf("%s: %s\n",pFeature->GetFieldDefnRef(i)->GetNameRef(),pFeature->GetFieldAsString(i));
                        if (!strcmp(pFeature->GetFieldDefnRef(i)->GetNameRef(),"DRVAL1"))
                        {
                            newPolygon.minDepth=pFeature->GetFieldAsInteger(i);
//                            if (maxMapDepth<newPolygon.minDepth) maxMapDepth=newPolygon.minDepth; //цвет берется по минимальной глубине полигона
//                            printf("minDepth %f for type %d\n",newPolygon.minDepth, type);
                        }
                        if (!strcmp(pFeature->GetFieldDefnRef(i)->GetNameRef(),"DRVAL2"))
                        {
                            newPolygon.maxDepth=pFeature->GetFieldAsInteger(i);
//                printf("maxDepth %f for type %d\n",newPolygon.maxDepth, type);
                        }
                    }

                pPolygon=(OGRPolygon*)pGeometry;

                pRing=pPolygon->getExteriorRing();
                curStart=0;
                numVertex=pRing->getNumPoints() - (pRing->get_IsClosed()?1:0);
                newPolygon.vertexExternalCount=numVertex;
//                printf("LOAD MAP external vertex count %d\n", numVertex);
//		printf("> start %d, count %d\n",curStart,numVertex);
                start.push_back(curStart);
                count.push_back(numVertex);
                curStart+=numVertex;

                for (int i=0;i<pPolygon->getNumInteriorRings();i++)
                {
                    int num=pPolygon->getInteriorRing(i)->getNumPoints() - (pPolygon->getInteriorRing(i)->get_IsClosed()?1:0);
                    numVertex+=num;
//		    printf("> start %d, count %d\n",curStart,num);
                    start.push_back(curStart);
                    count.push_back(num);
                    curStart+=num;
                }

//		printf("numPoints %d (%d), isClosed %d, isClockwise %d, numInterior %d\n",pRing->getNumPoints(),numVertex,pRing->get_IsClosed(),pRing->isClockwise(),pPolygon->getNumInteriorRings());

                polygons.push_back(newPolygon);
                pRing->getEnvelope(&polygons[polygonCount].envFL);
                polygons[polygonCount].vertexCount=numVertex;
                polygons[polygonCount].pVertexFL=(GLdouble*)malloc(sizeof(GLdouble)*3*polygons[polygonCount].vertexCount);
                polygons[polygonCount].pVertex=(GLdouble*)malloc(sizeof(GLdouble)*3*polygons[polygonCount].vertexCount);

                loadContour(&polygons[polygonCount],pRing,start[0],count[0]);
                for (int i=0;i<pPolygon->getNumInteriorRings();i++)
                    loadContour(&polygons[polygonCount],pPolygon->getInteriorRing(i),start[i+1],count[i+1]);

                tesselatePolygon(&polygons[polygonCount],&start,&count);
                polygonCount++;
            }
            delete pFeature;
            if (polygonCount>=MAP_MAX) break;
            pFeature=pLayer->GetNextFeature();
        }

    }
    gettimeofday(&tv,0);
    printf("Loaded %s: %d in %u\n",areaStrings[type],polygonCount,(int)((tv.tv_sec-tvs.tv_sec)*1000000+(tv.tv_usec-tvs.tv_usec)));
}

//int convertMap(const char *fileName, const char *sourceDir, const char *destDir)
//{
//    OGRDataSource* pDS;
//    int vc=0;

//    OGRRegisterAll();

//    char fullMapName[255];
////    printf("source: %s\n", sourceDir);
////    printf("END: %c\n", sourceDir[sizeof(sourceDir)-1]);
//    if(&sourceDir[sizeof(sourceDir)-1] == "/")
//        sprintf(fullMapName, "%s%s", sourceDir,fileName);
//    else
//        sprintf(fullMapName, "%s/%s", sourceDir,fileName);
////    printf("mapdir: %s\n", fullMapName);

//    char fullMapNameNew[255];
//    if(&destDir[sizeof(destDir)-1] == "/")
//        sprintf(fullMapNameNew, "%s%s.bin", destDir,fileName);
//    else
//        sprintf(fullMapNameNew, "%s/%s.bin", destDir,fileName);

////    printf("new mapdir: %s\n", fullMapNameNew);

//    FILE *mapFile = fopen(fullMapNameNew, "wb");
//    if(!mapFile)
//    {
//        puts("mapS57toGL.cpp convertMap function ERROR: dest directory does not exist");
//        return 0;
//    }

//    pDS=OGRSFDriverRegistrar::Open(fullMapName,0);
//    if (!pDS) return 0;

//    loadLayer(PT_LNDARE,pDS);
//    loadLayer(PT_DEPARE,pDS);

////    printf("Fi: %f - %f, La: %f - %f\n",minf,maxf,minl,maxl);
////    printf("f0 %f, l0 %f\n",f0,l0);

//    for(int i=0;i<polygonCount;++i)
//    {
//        //printf("processPolygonColor %d\n", i);
////        processPolygonColor(&map[i]);
//        //printf("processEnvelope %d\n", i);
////        processEnvelope(&map[i]);

//        vc+=map[i].vertexCount;

//        fwrite(&(map[i].polygonType), sizeof(GLenum), 1, mapFile);
//        fwrite(&(map[i].type), sizeof(GLenum), 1, mapFile);
//        //fwrite(&(map[i].colorb[0]), 1, 1, mapFile);
//        //fwrite(&(map[i].colorb[1]), 1, 1, mapFile);
//        //fwrite(&(map[i].colorb[2]), 1, 1, mapFile);
//        fwrite(&(map[i].minDepth), sizeof(GLdouble), 1, mapFile);
//        fwrite(&(map[i].maxDepth), sizeof(GLdouble), 1, mapFile);
//        fwrite(&(map[i].envFL.MinX), sizeof(GLdouble), 1, mapFile);
//        fwrite(&(map[i].envFL.MinY), sizeof(GLdouble), 1, mapFile);
//        fwrite(&(map[i].envFL.MaxX), sizeof(GLdouble), 1, mapFile);
//        fwrite(&(map[i].envFL.MaxY), sizeof(GLdouble), 1, mapFile);
//        fwrite(&(map[i].vertexExternalCount), sizeof(GLushort), 1, mapFile);
//        fwrite(&(map[i].vertexCount), sizeof(GLushort), 1, mapFile);
//        for(int j = 0; j < map[i].vertexCount * 3; j++) {
//          fwrite(&(map[i].pVertexFL[j]), sizeof(GLdouble), 1, mapFile);
//        }
//        fwrite(&(map[i].indexesCount), sizeof(GLushort), 1, mapFile);
//        for(int j = 0; j < map[i].indexesCount; j++) {
//          fwrite(&(map[i].pIndexes[j]), sizeof(GLushort), 1, mapFile);
//        }
//    }

//    printf("Load map OK [vertices:%d]\n", vc);

//    fclose(mapFile);
//    return 1;
//}
int convertMap(const char *fileName, const char *sourceDir, const char *destDir)
{
    OGRDataSource* pDS;
    int vc=0;

    OGRRegisterAll();

    char fullMapName[255];
    if(&sourceDir[sizeof(sourceDir)-1] == "/")
        sprintf(fullMapName, "%s%s", sourceDir,fileName);
    else
        sprintf(fullMapName, "%s/%s", sourceDir,fileName);

    char fullMapNameNew[255];
    if(&destDir[sizeof(destDir)-1] == "/")
        sprintf(fullMapNameNew, "%s%s.bin", destDir,fileName);
    else
        sprintf(fullMapNameNew, "%s/%s.bin", destDir,fileName);

    FILE *mapFile = fopen(fullMapNameNew, "wb");
    if(!mapFile)
    {
        puts("mapS57toGL.cpp convertMap function ERROR: dest directory does not exist");
        return 0;
    }

    pDS=OGRSFDriverRegistrar::Open(fullMapName,0);
    if (!pDS) return 0;


    GLdouble Ftl=-90.0,Ltl=180.0,Fbr=90.0,Lbr=-180.0;
    fseek(mapFile,4*sizeof(GLdouble),SEEK_CUR);

    GLubyte layerCount=PT_MAX-1;
    fwrite(&layerCount, sizeof(GLubyte), 1, mapFile);

    for(int i=1; i<PT_MAX; ++i)
    {
        polygonCount=0;
        polygons.clear();
        loadLayer(i,pDS);

        GLenum layerType=i;
        fwrite(&layerType, sizeof(GLenum), 1, mapFile);
        fwrite(&polygonCount, sizeof(GLuint), 1, mapFile);

        for(int j=0;j<polygonCount;++j)
        {
            vc+=polygons[j].vertexCount;
            if(polygons[j].envFL.MinY < Fbr)
                Fbr=polygons[j].envFL.MinY;
            if(polygons[j].envFL.MinX < Ltl)
                Ltl=polygons[j].envFL.MinX;
            if(polygons[j].envFL.MaxY > Ftl)
                Ftl=polygons[j].envFL.MaxY;
            if(polygons[j].envFL.MaxX > Lbr)
                Lbr=polygons[j].envFL.MaxX;

//            fwrite(&(polygons[j].envFL.MaxY), sizeof(GLdouble), 1, mapFile);
//            fwrite(&(polygons[j].envFL.MinX), sizeof(GLdouble), 1, mapFile);
//            fwrite(&(polygons[j].envFL.MinY), sizeof(GLdouble), 1, mapFile);
//            fwrite(&(polygons[j].envFL.MaxX), sizeof(GLdouble), 1, mapFile);
            fwrite(&(polygons[j].polygonType), sizeof(GLenum), 1, mapFile);

            fwrite(&(polygons[j].vertexExternalCount), sizeof(GLushort), 1, mapFile);
            fwrite(&(polygons[j].vertexCount), sizeof(GLushort), 1, mapFile);
            for(int j = 0; j < polygons[j].vertexCount * 3; j++) {
              fwrite(&(polygons[j].pVertexFL[j]), sizeof(GLdouble), 1, mapFile);
            }
            fwrite(&(polygons[j].indexesCount), sizeof(GLushort), 1, mapFile);
            for(int j = 0; j < polygons[j].indexesCount; j++) {
              fwrite(&(polygons[j].pIndexes[j]), sizeof(GLushort), 1, mapFile);
            }
        }
    }
    rewind(mapFile);
    fwrite(&Ftl, sizeof(GLdouble), 1, mapFile);
    fwrite(&Ltl, sizeof(GLdouble), 1, mapFile);
    fwrite(&Fbr, sizeof(GLdouble), 1, mapFile);
    fwrite(&Lbr, sizeof(GLdouble), 1, mapFile);

    fclose(mapFile);

    printf("Load map OK [vertices:%d]\n", vc);

    return 1;
}

int main(int argc,char* argv[])
{
    if(argc < 3)
    {
        printf("USAGE !!! : mapS57toGL.e [sourceDir] [destDir]\n");
        return 1;
    }

    DIR *mapDir = opendir(argv[1]); //rewinddir("./maps/"); set to 0 entry
    struct dirent *entry=NULL;
    while((entry = readdir(mapDir)) != NULL)
    {
        if(strncmp(entry->d_name, ".", 2) && strncmp(entry->d_name, "..", 3))
        {
            printf("%s\n", entry->d_name);
            convertMap(entry->d_name, argv[1], argv[2]);
        }
    }

    return 0;
}

//#define TEST_PRIM

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <vector>
#include <list>
#include <algorithm>

#include <dirent.h>

#include <FTGL/ftgl.h>

static FTFont* font=NULL;
static FTSimpleLayout layout;
static FTFont* fontLimb=NULL;
static FTSimpleLayout layoutLimb;
static FTFont* fontNote=NULL;
/*static */FTSimpleLayout layoutNote;
static const char* fontname="../data/font/DejaVuSans.ttf";

#include "system.h"
//#include "matrix.h"

#include "glmapregion.h"
#include "glnotificationmanager.h"
#include "gltesselator.h"

#define WINDOW_X 1024
#define WINDOW_Y 1024

int wnd=0;

int draw_lines=0;
int do_blend=1;

// под масштабом понимается радиус
GLfloat scale=16.0;
GLfloat toScale=16.0;
GLfloat alpha=0;

int draw_primary=1;
int draw_texture=1;
int draw_traces=0;

int draw_loupe=1;
int linseEffect=1;
int loupeX = 0;
int loupeY = 0;
GLfloat loupeScale = 2.0;
GLfloat toLoupeScale = 2.0;
bool lmbPressed = false;
bool rmbPressed = false;

int need_update_map=1;
unsigned int cur_offset=0;

//double f0=54.724293;
//double l0=19.809148;
double f0=54.724423;
double l0=19.808993;
double FourOld=0.0;
double LourOld=0.0;
//double   f0=54.7242;
//double   l0=19.8091;
//double f0=59.7;
//double l0=24.1;
double minf=360,maxf=0,minl=360,maxl=0;
GLfloat posX=0.0;
GLfloat posY=0.0;
GLfloat toPosX=0.0;
GLfloat toPosY=0.0;
GLfloat angle=0.0;
GLfloat toAngle=0.0;
GLfloat mangle=0.0;
GLfloat toMangle=0.0;
uint ghostTime = 0;
double ourGhostX = 0.0;
double ourGhostY = 0.0;
double ourGhostK = 0.0;
//GLfloat posXold=0.0;
//GLfloat posYold=0.0;
GLdouble width=WINDOW_X;
GLdouble height=WINDOW_Y;
GLdouble lw=1.5;
char prim_porog=2;
char povorot[2]={-10,0};
GLint zaychik[2]={0,};
int prim_test_res=0;
int prim_test_pel=0;
int use_shader=1;
int dop_peleng=1;

int mercator=0;
int fps=0;
int dofps=0;
int do_animation = 1;

int selected=0;
int selected_point=0;
int do_selection=0;
uint selectedKeyOtog=0;

int draw_isobates=1;

int software=0;

void render();
void selectOtogTarget();
void clearTexture(GLubyte fbo);

uint skolTask=0;
uint skolTaskPrev=0;

bool ODmode = false;
bool ODmodePrev = false;

bool Nmode = false;
bool NightMode = false;

bool showNadv=1,showVozd=1,showPodv=1,showOur=1,showEnemy=1;
MSG11FormNadv formNadv;
MSG11FormVozd formVozd;

GLdouble maxMapDepth=0;

bool compareMapPolygon(const MapPolygon& a,const MapPolygon& b)
{
    return a.area<b.area;
}

#define MAP_MAX 10000
std::vector<MapPolygon> polygons;
//int polygonCount=0;
MapPolygon testMap;

GLdouble* pBigVertex;
GLuint bigVertexCount;
GLuint* pBigIndexes;
GLuint bigIndexesCount;
GLubyte* pBigColors;
GLuint bigBufferObjects[3];
#define BIG_VERTEX_DATA 0
#define BIG_COLOR_DATA 1
#define BIG_INDEX_DATA 2

//GlMapRegion _map;
std::vector<GlMapRegion> _map;

std::map<uint,GlPrimitive> _traces;
std::map<uint,GlPrimitive> _graphics;
std::map<uint,GlPrimitive> _trajectories;
std::vector<uint> _trajectoryShow;
std::vector<uint> _graphicsShow;
uint _ourTrajKey = 0;

//template<typename T>
std::vector<uint>::iterator find(std::vector<uint> vec, uint value)
{
    for(std::vector<uint>::iterator i=vec.begin(); i!=vec.end(); ++i)
        if((*i) == value)
            return i;
    return vec.end();
}

Animation animScale;
Animation animPosX;
Animation animPosY;
Animation animAngle;
Animation animMangle;
Animation animLoupeScale;


GlNotificationManager *noteManager;


void tesselatePolygon(MapPolygon* pPolygon,std::vector<int>* pstart,std::vector<int>* pcount);
// void tesselateGraphPolygon(GraphPolygon* pPolygon);
void _tesselatePolygon(GLdouble *vertices, GLushort vertexCount, GLushort **indexes, GLushort *indexCount);

// Define targa header. This is only used locally.
#pragma pack (push, 1)
typedef struct
{
	GLbyte	identsize;              // Size of ID field that follows header (0)
	GLbyte	colorMapType;           // 0 = None, 1 = paletted
	GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;          // First colour map entry
	unsigned short	colorMapLength;         // Number of colors
	unsigned char 	colorMapBits;   // bits per palette entry
	unsigned short	xstart;                 // image x origin
	unsigned short	ystart;                 // image y origin
	unsigned short	width;                  // width in pixels
	unsigned short	height;                 // height in pixels
	GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
	GLbyte	descriptor;             // image descriptor
} TGAHEADER;
#pragma pack (pop)


////////////////////////////////////////////////////////////////////
// Allocate memory and load targa bits. Returns pointer to new buffer,
// height, and width of texture, and the OpenGL format of data.
// Call free() on buffer when finished!
// This only works on pretty vanilla targas... 8, 24, or 32 bit color
// only, no palettes, no RLE encoding.
GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE *pFile;			// File pointer
	TGAHEADER tgaHeader;		// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;			// Pixel depth;
	GLbyte	*pBits = NULL;          // Pointer to bits
	size_t sz;

	// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_BGR_EXT;
	*iComponents = GL_RGB8;

	// Attempt to open the fil
	pFile = fopen(szFileName, "rb");
	if (pFile == NULL)
		return NULL;

	// Read in header (binary)
	sz=fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);
	if(sz!=18) printf("ERROR read TGA header: %d (%d)\n",(int)sz,18);


	// Do byte swap for big vs little endian
#ifdef __APPLE__
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
	LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
	LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
	LITTLE_ENDIAN_WORD(&tgaHeader.width);
	LITTLE_ENDIAN_WORD(&tgaHeader.height);
#endif


	// Get width, height, and depth of texture
    *iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	// Calculate size of image buffer
	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error. This should catch RLE or other
	// weird formats that I don't want to recognize
	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}

	// Set OpenGL format expected
	switch (sDepth)
	{
	case 3:     // Most likely case
		*eFormat = GL_BGR_EXT;
		*iComponents = GL_RGB8;
		break;
	case 4:
		*eFormat = GL_BGRA_EXT;
		*iComponents = GL_RGBA8;
		break;
	case 1:
		*eFormat = GL_LUMINANCE;
		*iComponents = GL_LUMINANCE8;
		break;
	};


	// Done with File
	fclose(pFile);

	// Return pointer to image data
	return pBits;
}

// SHADERS ---------------------------------------
#define MAX_INFO_LOG_SIZE 2048

#define PRIM0     0
#define PRIM1     1
#define PRIM2     2
#define PRIM3     3
#define PRIM4     4
#define PRIM5     5
#define PRIM6     6
#define PRIM7     7
#define LOUPE     8
#define TOTAL_SHADERS 9

GLint whichShader = PRIM0;             // current shader
GLuint fShader[TOTAL_SHADERS], progObj[TOTAL_SHADERS];  // shader object names
GLboolean needsValidation[TOTAL_SHADERS];
const char *shaderNames[TOTAL_SHADERS] = {"prim0","prim1","prim2","prim3","prim4","prim5","prim6","prim7","loupe"};
const char *shaderDesc[TOTAL_SHADERS] = {"map","map+prim1","map+prim2","map+fade prim1","map+fade prim2","map+prim1+prim2","map+p1+p2+all","map+fade p1+p2", "+loupe"};

// Load shader from disk into a null-terminated string
GLchar *LoadShaderText(const char *fileName)
{
	GLchar *shaderText = NULL;
	GLuint shaderLength = 0;
	FILE *fp;
	size_t sz;

	fp = fopen(fileName, "r");
	if (fp != NULL)
	{
		while (fgetc(fp) != EOF)
		{
			shaderLength++;
		}
		rewind(fp);
		shaderText = (GLchar *)malloc(shaderLength+1);
		if (shaderText != NULL)
		{
			sz=fread(shaderText, 1, shaderLength, fp);
			if(sz!=shaderLength) printf("ERROR read shader text: %d (%d)\n",(int)sz,shaderLength);
		}
		shaderText[shaderLength] = '\0';
		fclose(fp);
	}

	return shaderText;
}

// Compile shaders
void PrepareShader(GLint shaderNum)
{
	char fullFileName[255];
	GLchar *fsString;
	const GLchar *fsStringPtr[1];
	GLint success;

	// Create shader objects and specify shader text
	sprintf(fullFileName, "../data/shaders/%s.fs", shaderNames[shaderNum]);
	fsString = LoadShaderText(fullFileName);
	if (!fsString)
	{
		fprintf(stderr, "Unable to load \"%s\"\n", fullFileName);
		exit(0);
	}
	fShader[shaderNum] = glCreateShader(GL_FRAGMENT_SHADER);
	fsStringPtr[0] = fsString;
	glShaderSource(fShader[shaderNum], 1, fsStringPtr, NULL);
	free(fsString);

	// Compile shaders and check for any errors
	glCompileShader(fShader[shaderNum]);
	glGetShaderiv(fShader[shaderNum], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(fShader[shaderNum], MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in fragment shader #%d compilation!\n", shaderNum);
		fprintf(stderr, "Info log: %s\n", infoLog);
		exit(0);
	}

	// Create program object, attach shader, then link
	progObj[shaderNum] = glCreateProgram();
	glAttachShader(progObj[shaderNum], fShader[shaderNum]);

	glLinkProgram(progObj[shaderNum]);
	glGetProgramiv(progObj[shaderNum], GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetProgramInfoLog(progObj[shaderNum], MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in program #%d linkage!\n", shaderNum);
		fprintf(stderr, "Info log: %s\n", infoLog);
		exit(0);
	}

	// Program object has changed, so we should revalidate
	needsValidation[shaderNum] = GL_TRUE;
}

// SHADERS END -----------------------------------


GLdouble pPrimVertex[3*WINDOW_Y/2];
GLubyte pPrimColors[4*WINDOW_Y/2];
GLuint primCount=0;
GLbyte* pImage=0;
GLint iWidth, iHeight, iComponents;
GLenum eFormat;

#define TEXID_MAP   0
#define TEXID_PRIM1 1
#define TEXID_PRIM2 2
#define TEXID_LOUPE 3
GLuint texID[4];

#define FBOID_MAP  0
#define FBOID_PRIM1  1
#define FBOID_PRIM2  2
#define FBOID_LOUPE 3
GLuint fboID[4];

GLuint loupeTex=0;
GLuint loupeFbo=0;

GLfloat texCoordOffsets[18];

void loadPrimary()
{
	primCount=WINDOW_Y/2;
	GLfloat xInc, yInc;
	for (int i=0;i<WINDOW_Y/2;i++)
	{
		pPrimVertex[i*3+0]=0;
		pPrimVertex[i*3+1]=i+0.5;
		pPrimVertex[i*3+2]=0;
	}

	GLubyte* pData=(GLubyte*)malloc(1*WINDOW_X*WINDOW_Y*4);

	memset(pData,0,1*WINDOW_X*WINDOW_Y*4);
	glGenTextures(3,texID);
	glGenFramebuffersEXT(3,fboID);

	for (int i=0;i<3;i++)
	{
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D,texID[i]);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,WINDOW_X,WINDOW_Y,0,GL_RGBA,GL_UNSIGNED_BYTE,pData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboID[i]);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_TEXTURE_2D, texID[i],0);
	}
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
	glActiveTexture(GL_TEXTURE0);

	free(pData);
	xInc = 1.0f / (GLfloat)WINDOW_X;
	yInc = 1.0f / (GLfloat)WINDOW_Y;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			texCoordOffsets[(((i*3)+j)*2)+0] = (-1.0f * xInc) + ((GLfloat)i * xInc);
			texCoordOffsets[(((i*3)+j)*2)+1] = (-1.0f * yInc) + ((GLfloat)j * yInc);
		}
	}
}

GLuint texIDMean=0;

void loadMeans()
{
	GLbyte *pBytes;
	GLint iWidth, iHeight, iComponents;
	GLenum eFormat;
	glGenTextures(1,&texIDMean);
	glBindTexture(GL_TEXTURE_2D,texIDMean);
	pBytes = gltLoadTGA("../data/map/means.tga", &iWidth, &iHeight,&iComponents, &eFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight,0, eFormat, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);
	glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}


void setWindowTitle()
{
	char str[256];
    char elemnames[][16]={"NONE","DEPARE","LNDARE"};
    sprintf(str,"%s Map M: %.1f, %s (%d-%d)",shaderDesc[whichShader],scale,
            selected?elemnames[polygons[selected-1].polygonType]:"",
            selected?(int)polygons[selected-1].minDepth:0,
            selected?(int)polygons[selected-1].maxDepth:0);
	glutSetWindowTitle(str);
}

void _doTransformationsForNMode();

void resize(GLsizei w,GLsizei h)
{
	GLfloat aspect;
//    printf("resize %d, %d\n",w,h);
	if (!h) h=1;
	width=w;
	height=h;

	aspect=(GLfloat)w/(GLfloat)h;

	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w<=h)
        glOrtho(-scale,scale,-scale/aspect,scale/aspect,100,-100);
    else
        glOrtho(-scale*aspect,scale*aspect,-scale,scale,100,-100);
    glRotatef(mangle,1.0,0.0,0.0);
    glRotatef(angle,0.0,0.0,1.0);
    glTranslatef(posX,posY,0);
    //printf("Shift on %.2f : %.2f (km)\n",posX,posY);
    glMatrixMode(GL_MODELVIEW);
//    puts("resize");
//	glLoadIdentity();
    need_update_map=1;
}

void processSelectionPointDown(int x, int y)
{
	y=height-y-1;
	GLint viewport[4];
	GLdouble mvmtx[16],projmtx[16];
	GLdouble wx,wy,wz;

	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvmtx);
	glGetDoublev(GL_PROJECTION_MATRIX,projmtx);

	gluUnProject(x,y,0,mvmtx,projmtx,viewport,&wx,&wy,&wz);
    polygons[selected-1].pVertex[(selected_point-1)*3+0]=wx;
    polygons[selected-1].pVertex[(selected_point-1)*3+1]=wy;
}


void processSelectionPoint(int x, int y)
{
	y=height-y-1;
	GLint viewport[4];
	GLdouble mvmtx[16],projmtx[16];
	GLdouble wx,wy,wz;

	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvmtx);
	glGetDoublev(GL_PROJECTION_MATRIX,projmtx);
    for (int i=0;i<polygons[selected-1].vertexCount;i++)
	{
        gluProject(polygons[selected-1].pVertex[i*3+0],polygons[selected-1].pVertex[i*3+1],0,mvmtx,projmtx,viewport,&wx,&wy,&wz);
//	printf(">> %f %f -> (%f %f):(%d %d)\n",map[selected-1].pVertex[i*3+0],map[selected-1].pVertex[i*3+1],wx,wy,x,y);
		if (abs((int)wx-x)<5 && abs((int)wy-y)<5)
		{
			selected_point=i+1;
			printf("FOUND %d\n",selected_point);
			break;
		}
	}
}

void processSelection(int x, int y)
{
    printf("Mouse click on (pixels)\t\t%d\t:  %d\n",x,y);
	GLfloat aspect;
	GLuint selectArray[128]={0,};
	GLint hits, viewport[4];

	do_selection=1;

	glSelectBuffer(128,selectArray);
	glGetIntegerv(GL_VIEWPORT,viewport);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glRenderMode(GL_SELECT);

    glLoadIdentity();
    gluPickMatrix(x,viewport[3]-y+viewport[1],2,2,viewport);

    aspect=(GLfloat)viewport[2]/(GLfloat)viewport[3];
    if (viewport[2]<=viewport[3])
        glOrtho(-scale,scale,-scale/aspect,scale/aspect,1,-2);
    else
        glOrtho(-scale*aspect,scale*aspect,-scale,scale,1,-2);
    glRotatef(angle,0,0,1);
    glTranslatef(posX,posY,0);

	selectOtogTarget();

	hits=glRenderMode(GL_RENDER);
    
    if(sys.ourShip.isSet(MSG6SF_F) && sys.ourShip.isSet(MSG6SF_L))
    {
        double Xm, Ym;
        Xm = (x - WINDOW_X/2)*scale*2 / WINDOW_X - posX;
        Ym = -(y - WINDOW_Y/2)*scale*2 / WINDOW_Y - posY;
        double Fm, Lm;
        CXYFL(f0,l0,Xm,Ym,&Fm,&Lm);
        CFLXY(sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),Fm,Lm,&Xm,&Ym);
        printf("Mouse click on (km)\t\t%.2f\t:  %.2f\n",Xm,Ym);
        printf("Mouse click on (grad)\t\t%.2f\t:  %.2f\n",Fm,Lm);
        double P,D;
        xyinpd(Xm,Ym,&P,&D);
        printf("Mouse click on (grad-km)\t%.2f\t:  %.2f\n",P,D);
        
        MSG12_SkolArbitrary skol;
        skol.setTaskNum(skolTask);
        skol.setF(Fm);
        skol.setL(Lm);
        skol.setP(P);
        skol.setD(D);
        skol.save();
    }

	if (hits>0)
	{
		printf("hits %d, top %d (%x)\n",hits,selectArray[3],selectArray[3]);
		for(int i=0;i<hits;i++)
			printf("%d ",selectArray[3+i*4]);
		printf("\n");

		MSG7_Skol skol;
		skol.setKeyOtog(selectArray[3]);
		printf("skol for %d\n",skolTask);
		skol.setTaskNum(skolTask);
		skol.save();

        selectedKeyOtog = selectArray[3];
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}

int scrollAnchorX=0;
int scrollAnchorY=0;
double oldPosX=0.0;
double oldPosY=0.0;

void setScale(GLfloat, bool animate = true);
void setLoupeScale(GLfloat, bool animate = true);

void mouse(int button,int state, int x, int y)
{
    //printf("button %d, state %d, x %d, y %d\n",button,state,x,y);
    if(button==3 && state==GLUT_DOWN)
    {
        if(!rmbPressed)
        {
            if(toScale >= 2.0)
                setScale(toScale/2);
//                toScale = scale/2;
        }
        else
        {
            if(toLoupeScale < 16.0)
                setLoupeScale(toLoupeScale*2);
            printf("RMB pressed, loupeScale = %.4f\n", toLoupeScale);
        }
    }
    else if(button==4 && state==GLUT_DOWN)
    {
        if(!rmbPressed)
        {
            if(toScale < 2048.0)
                setScale(toScale*2);
//            toScale = scale*2;
        }
        else
        {
            if(toLoupeScale >= 2.0)
                setLoupeScale(toLoupeScale/2);
            printf("RMB pressed, loupeScale = %.4f\n", toLoupeScale);
        }
    }
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
		processSelection(x,y);
        lmbPressed = true;
        scrollAnchorX = x;
        scrollAnchorY = y;
        oldPosX = posX;
        oldPosY = posY;
    }
    else
    {
        lmbPressed = false;
    }
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        rmbPressed = true;
        loupeX = x;
        loupeY = y;
    }
    else if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP)
    {
        rmbPressed = false;
    }
    
/*
	if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		selected=0;
		selected_point=0;
	}
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		selected?processSelectionPoint(x,y):processSelection(x,y);
	if (button==GLUT_LEFT_BUTTON && state==GLUT_UP && selected_point)
		processSelectionPointDown(x,y);
*/
}
void setPos(GLfloat newX, GLfloat newY, bool animate = true);
void mouseMotion(int x, int y)
{
	if (selected_point)
		processSelectionPointDown(x,y);
    if (lmbPressed)
    {        
        if(!ODmode)
//        {
//            toPosX = oldPosX + (x-scrollAnchorX)*scale*2/WINDOW_X;
//            toPosY = oldPosY - (y-scrollAnchorY)*scale*2/WINDOW_Y;
//        }
        setPos(oldPosX + (x-scrollAnchorX)*scale*2/WINDOW_X, oldPosY - (y-scrollAnchorY)*scale*2/WINDOW_Y, false);
        //printf("Mouse motion with LMB: %d : %d\n", x, y);
    }
    if(rmbPressed)
    {
        loupeX = x;
        loupeY = y;
    }
}

void reloadTrajectories();
void setNmode(bool);
void setODmode(bool state)
{
    printf("[ODmode] Status: %d\n", state);
    if(state)
    {
        ODmode = true;
        double dx,dy;
        CFLXY(f0,l0,sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),&dx,&dy);
        setPos(-dx-ourGhostX, -dy-ourGhostY);
        noteManager->addNote("OD mode ON");
    }
    else
    {
        ODmode = false;
//        ourGhostX = 0.0;
//        ourGhostY = 0.0;
        if(Nmode)
            setNmode(false);
        noteManager->addNote("OD mode OFF");
    }
    reloadTrajectories();
//    need_update_map=1;
}
void setAngle(GLfloat newAngle, bool animate = true);
void setNmode(bool state)
{
    printf("[Nmode] Status: %d\n", state);
    if(state)
    {
         Nmode = true;
         if(!ODmode)
            setODmode(true);
         if(ghostTime)
             setAngle(ourGhostK);
         else
             setAngle(sys.ourShip.getKgrad());
         noteManager->addNote("Nose mode ON");
    }
    else
    {
        Nmode = false;
        setAngle(0.0);
        ourGhostK = 0.0;
        noteManager->addNote("Nose mode OFF");
    }
}

void setNightMode(bool state)
{
    printf("[NightMode] Status: %d\n", state);
    if(state)
    {
        NightMode = true;
        glClearColor(0.2f, .25f, .25f, 1.0f);
        noteManager->addNote("Night mode ON");
    }
    else
    {
        NightMode = false;
        glClearColor(0.67f, .753f, .694f, 1.0f);
        noteManager->addNote("Night mode OFF");
    }
    need_update_map=1;
}

void setScale(GLfloat newScale, bool animate)
{
    toScale = newScale;
    if(animate)
    {
        animScale.setBegValue(scale);
        animScale.setEndValue(newScale);
        animScale.start(400);
    }
    else
    {
        scale = toScale;
        resize(width,height);
    }
}

void setLoupeScale(GLfloat newScale, bool animate)
{
    toLoupeScale = newScale;
    if(animate)
    {
        animLoupeScale.setBegValue(loupeScale);
        animLoupeScale.setEndValue(newScale);
        animLoupeScale.start(400);
    }
    else
    {
        loupeScale = toLoupeScale;
        resize(width,height);
    }
}

void setPos(GLfloat newX, GLfloat newY, bool animate)
{
    toPosX = newX;
    toPosY = newY;
    if(animate)
    {
        animPosX.setBegValue(posX);
        animPosX.setEndValue(newX);
        animPosX.start(400);

        animPosY.setBegValue(posY);
        animPosY.setEndValue(newY);
        animPosY.start(400);
    }
    else
    {
        posX = toPosX;
        posY = toPosY;
        resize(width,height);
    }
}

void setAngle(GLfloat newAngle, bool animate)
{
    toAngle = newAngle;
    if(animate)
    {
        if(fabs(angle - newAngle) > fabs(fabs(angle - newAngle) - 360.0))
            newAngle -= 360.0;

//        printf("new angle: %.1f\n", newAngle);
        if(animAngle.getState() != Animation::State_Started)
        {
            animAngle.setBegValue(angle);
            animAngle.setEndValue(newAngle);
            animAngle.start(400);
        }
        else
            animAngle.setEndValue(newAngle);
    }
    else
    {
        angle = newAngle;
        resize(width, height);
    }
}

void reloadMap();
uint ghostTestTime = 0;
void keyboard(unsigned char key, int x, int y)
{
    //printf("%d\n",key);
	switch (key)
	{
	case '-':
        if(toScale < 2048.0)
            setScale(toScale*2);
		break;
	case '+':
        if(toScale >= 2.0)
            setScale(toScale/2);
		break;
	case 'w':
        if(!ODmode)
        setPos(posX, posY-scale/10);
		break;
	case 's':
        if(!ODmode)
        setPos(posX, posY+scale/10);
		break;
	case 'a':
        if(!ODmode)
        setPos(posX+scale/10, posY);
		break;
	case 'd':
        if(!ODmode)
        setPos(posX-scale/10, posY);
		break;
	case ' ':
		draw_lines=draw_lines?0:1;
		glPolygonMode(GL_FRONT,draw_lines?GL_LINE:GL_FILL);
		need_update_map=1;
		break;
	case 'b':
		do_blend=do_blend?0:1;
//	    do_blend?glEnable(GL_BLEND):glDisable(GL_BLEND);
		break;
	case 'i':
		draw_isobates=draw_isobates?0:1;
		need_update_map=1;
		break;
	case 'o':
		if (alpha>0) alpha-=0.1;
		glAlphaFunc(GL_GEQUAL,alpha);
		break;
	case 'p':
//	    if(alpha<1) alpha+=0.1;
//	    glAlphaFunc(GL_GEQUAL,alpha);
		draw_primary=draw_primary?0:1;
		break;
	case 't':
		dop_peleng=dop_peleng?0:1;
		printf("dop_peleng %d\n",dop_peleng);
		break;
	case 'r':
//	    use_shader=use_shader?0:1;
		whichShader=(whichShader+1)%TOTAL_SHADERS;
		setWindowTitle();
		break;
	case 'n':
//		lw-=0.1;
//		printf("%f\n",lw);
		break;
	case 'm':
//		lw+=0.1;
//		printf("%f\n",lw);
        mercator=(mercator)?0:1;
        printf("mercator=%d\n", mercator);
        reloadMap();
        need_update_map=1;
		break;
	case 'k':
		if (prim_porog) prim_porog--;
		break;
	case 'l':
		if (prim_porog<15) prim_porog++;
		break;
#ifdef TEST_PRIM
	case '<':
		if (prim_test_res) prim_test_res--;
		printf("prim_test_res %d\n",prim_test_res);
		break;
	case '>':
		if (prim_test_res<511) prim_test_res++;
		printf("prim_test_res %d\n",prim_test_res);
		break;
	case 'K':
		if (prim_test_pel) prim_test_pel--;
		printf("prim_test_pel %d\n",prim_test_pel);
		break;
	case 'L':
		prim_test_pel=(prim_test_pel+1)%4096;
		printf("prim_test_res %d\n",prim_test_pel);
		break;
#else
	case '<':
		povorot[0]--;
		printf("povorot %d\n",povorot[0]);
		break;
	case '>':
		povorot[0]++;
		printf("povorot %d\n",povorot[0]);
		break;
#endif
	case 27:
		glutDestroyWindow(wnd);
		break;
    case '[':
    {
        (NightMode)?setNightMode(false):setNightMode(true);
        break;
    }
    case ']':
    {
        do_animation=(do_animation)?0:1;
        break;
    }
    case '\\':
        (ODmode)?setODmode(false):setODmode(true);
        break;
    case '\'':
        (Nmode)?setNmode(false):setNmode(true);
        break;
    case ';':
        draw_traces=(draw_traces)?0:1;
        printf("[Traces] Status: %d\n", draw_traces);
        break;
    case '8':
        toMangle += 1.0;
        break;
    case '5':
        toMangle -= 1.0;
        break;
    case '7':
        linseEffect=(linseEffect)?0:1;
	default:
		break;
	}
}

void timer(int value)
{
	if(!dofps)
		printf("fps: %d offset %u\n",dofps?dofps:fps,cur_offset);
	fps = 0;
	need_update_map=1;
	glutPostRedisplay();
	glutTimerFunc(dofps?1000/dofps:1000,timer,0);
}

#pragma pack (push, 1)

struct prim_header
{
unsigned short pack:8;
unsigned short kvant:4;
unsigned short proreg:4;

	unsigned short discrets;

	unsigned short um;

	unsigned short peleng;

	unsigned short sost;
};

#pragma pack (pop)

// resport: 0 если считан port1, 1 - если port2, иначе не выставляется

int error_prim_file=0;

int createSocket(int port)
{
  int val = 1;
  int fd,res;
  fd=socket (AF_INET, SOCK_DGRAM, 0);
  if (fd < 0)
  {
    perror ("create socket: ");
	return 0;
  }
  if (setsockopt (fd, SOL_SOCKET, SO_BROADCAST, &val, sizeof (val)) < 0)
  {
    perror ("setsockopt SO_BROADCAST: ");
	return 0;
  }
  struct sockaddr_in my_addr;

  my_addr.sin_family = AF_INET;
  my_addr.sin_addr.s_addr = htonl (INADDR_ANY);
  my_addr.sin_port = htons (port?2101:2104);

  res=bind (fd, (struct sockaddr *) &my_addr, sizeof (my_addr));
  printf("res %d\n",res);

  if(res<0)
  {
    perror ("bind: ");
	return 0;
  }
  fcntl (fd, F_SETFL, O_NONBLOCK);
  return fd;
};

int readPeleng(int port, GLubyte* pixels)
{
	unsigned char data[2048];
	struct prim_header *phdr=(struct prim_header*)data;
	unsigned char* pdiscrets=data+sizeof(struct prim_header);
#define PRIM_RADIUS (WINDOW_Y/2)
#define TABLE_SIZE 10
#define DISCRET_MAX 2303
	unsigned int dnum[TABLE_SIZE]={127,255,511,767,1023,1279,1535,1791,2047,DISCRET_MAX}; // если номер дискрета меньше или равно, то взять по этому индексу значение длины
	double dlen[TABLE_SIZE]={3.75,3.75,3.75,7.5,15,30,60,120,240,480};
	double len_start; // текущее расстояние до начала отметки в метрах, увеличивается на длину дискрета при обработке дискретов
	double len_val; // текущая длина дискрета
	unsigned char val0,val1; // амплитуда дискрета - два значения в байте (ближний и дальний в этой паре)
	double pixel_len=scale*1000.0/PRIM_RADIUS; // сколько в пикселе метров
	int start_pixel,end_pixel; // начальная и конечная точки растра, которые закрасит текущий дискрет
	static int start=1;
	unsigned int discrets;
	int peleng;
	static int fd[2]={0,};
	struct sockaddr_in addr;
	unsigned int size = sizeof (addr);
	int res;


	if (start)
	{
		fd[0]=createSocket(0);
		fd[1]=createSocket(1);
		if(!fd[0] || !fd[1])
		{
			error_prim_file=1;
			return -1;
		}
		start=0;
	}
	res=recvfrom(fd[port],data,2048,0,(struct sockaddr *) &addr, &size);
	//printf("recv prim %d port %d\n",res,port);
	if(res<=0)
		{
		return -1;
	}
	discrets=htons(phdr->discrets);
	peleng=htons(phdr->peleng);
	len_start=0;
	for (unsigned int curd=0;curd<discrets;) //в байте 2 дискрета - поэтому прибавлять цикл сразу на 2
	{
				int len;
		for (len=0;len<TABLE_SIZE;len++) //количество дискретов в таблице четное, поэтому длины в метрах для обоих дискретов в байте - одинаковы
			if (curd<=dnum[len]) break;
		len_val=dlen[len];
		val0=pdiscrets[curd/2]>>4; // ближний дискрет находится в старших 4-х битах (в байте 2 дискрета - значит для смещения делим на 2 номер дискрета)
		val1=pdiscrets[curd/2]&0xf; // а дальний в младших

		if (val0<prim_porog) val0=0;
		if (val1<prim_porog) val1=0;

		start_pixel=floor(len_start/pixel_len);
		if (start_pixel>=PRIM_RADIUS) break; //отметка за лимбом
		end_pixel=floor((len_start+len_val)/pixel_len);
		if (end_pixel>=PRIM_RADIUS) end_pixel=PRIM_RADIUS-1; // если конец отметки за лимбом - ставим конец на последний пиксель
//		printf("%d: val0 %d, len %.2f + %.2f, pixel %d - %d (%.2f-%.2f)(%.2f-%.2f)\n",curd,val0,len_start,len_val,start_pixel,end_pixel,start_pixel*pixel_len,start_pixel*pixel_len+pixel_len,end_pixel*pixel_len,end_pixel*pixel_len+pixel_len);
		for (int j=start_pixel;j<=end_pixel;j++)
			if (val0>pixels[j]) pixels[j]=val0;
		len_start+=len_val;
		curd++;

		start_pixel=floor(len_start/pixel_len);
		if (start_pixel>=PRIM_RADIUS) break; //отметка за лимбом
		end_pixel=floor((len_start+len_val)/pixel_len);
		if (end_pixel>=PRIM_RADIUS) end_pixel=PRIM_RADIUS-1; // если конец отметки за лимбом - ставим конец на последний пиксель
//		printf("%d: val1 %d, len %f + %f, pixel %d - %d\n",curd,val1,len_start,len_val,start_pixel,end_pixel);
		for (int j=start_pixel;j<=end_pixel;j++)
			if (val1>pixels[j]) pixels[j]=val1;
		len_start+=len_val;
		curd++;
	}
	return peleng;
}

void clearTexture(GLubyte fbo)
{
	glPushAttrib(GL_VIEWPORT_BIT|GL_COLOR_BUFFER_BIT);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboID[fbo]);
	glClearColor(0,0,0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);

	glPopAttrib();
}

void setPrimColors(GLubyte* pPixels,int port)
{
	for (GLuint i=0;i<primCount;i++)
	{
		pPrimColors[i*4+0]=0;
		pPrimColors[i*4+1]=(port==0)?(pPixels[i]*255.0/15.0):0;
		pPrimColors[i*4+2]=(port==1)?(pPixels[i]*255.0/15.0):0;
		pPrimColors[i*4+3]=pPixels[i]?255:0;
	}
}


int updateTexture(int resport)
{
	GLubyte pixels[WINDOW_Y/2]={0,};
	static GLint curpel[2]={0,2000};

#ifdef TEST_PRIM
	for (int i=0;i<WINDOW_Y/2;i++)
		pixels[i]=0xf;
	pixels[128]=0;

	curpel[resport]++;
	if (curpel[resport]>=4096) curpel[resport]=0;
#else
	if (error_prim_file) return 0;
	curpel[resport]=readPeleng(resport,pixels);

	if (curpel[resport]<0) return 0;
#endif
	zaychik[resport]=curpel[resport];
	setPrimColors(pixels,resport);

	glPushAttrib(GL_VIEWPORT_BIT|GL_COLOR_BUFFER_BIT);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboID[FBOID_PRIM1+resport]);


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	glViewport(0,0,WINDOW_X,WINDOW_Y);
	glOrtho(-WINDOW_X/2,WINDOW_X/2,-WINDOW_Y/2,WINDOW_Y/2,1,-2);

	glMatrixMode(GL_MODELVIEW);

	glColor4f(0,1,0,1.0);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3,GL_DOUBLE,0,pPrimVertex);
	glColorPointer(4,GL_UNSIGNED_BYTE,0,pPrimColors);

	glPushMatrix();
	glRotatef(-((float)curpel[resport]+povorot[resport])*360.0/4096.0,0,0,1); // убрать херню!!!! (povorot)
	glDrawElements(GL_POINTS,primCount-20,GL_UNSIGNED_SHORT,pTessIndexHelper);
	glPopMatrix();

	if (dop_peleng)
	{
		glPushMatrix();
		glRotatef(-((float)curpel[resport]+0.5+povorot[resport])*360.0/4096.0,0,0,1); // убрать херню!!!! (povorot)
		glDrawElements(GL_POINTS,primCount-20,GL_UNSIGNED_SHORT,pTessIndexHelper);
		glPopMatrix();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);

	glPopAttrib();
	return 1;
}

void drawPrimary()
{
	GLdouble aspect;
	{
#ifndef TEST_PRIM
		int i;
		for(i=0;i<10;i++)
			if(!updateTexture(0)) break;
		for(i=0;i<10;i++)
			if(!updateTexture(1)) break;
#else
		updateTexture(0);
		updateTexture(1);
#endif
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();

		glLoadIdentity();
		aspect=width/height;
		if (width<=height)
			glOrtho(-width/2,width/2,-height/2/aspect,height/2/aspect,1,-2);
		else
			glOrtho(-(width/2)*aspect,(width/2)*aspect,-height/2,height/2,1,-2);
		glMatrixMode(GL_MODELVIEW);

		if (use_shader)
		{
			GLfloat curpel[2];
//    whichShader=PRIMARY;
			glUseProgram(progObj[whichShader]); // рисуем карту с шейдером

			// Validate our shader before first use
			if (needsValidation[whichShader])
			{
				GLint success;

				glValidateProgram(progObj[whichShader]);
				glGetProgramiv(progObj[whichShader], GL_VALIDATE_STATUS, &success);
				if (!success)
				{
					GLchar infoLog[MAX_INFO_LOG_SIZE];
					glGetProgramInfoLog(progObj[whichShader], MAX_INFO_LOG_SIZE, NULL, infoLog);
					fprintf(stderr, "Error in program #%d validation!\n", whichShader);
					fprintf(stderr, "Info log: %s\n", infoLog);
					exit(0);
				}

				needsValidation[whichShader] = GL_FALSE;
			}
			GLint uniformLoc = glGetUniformLocation(progObj[whichShader], "samplerMap");
			if (uniformLoc != -1)
			{
				glUniform1i(uniformLoc, FBOID_MAP);
			}
			uniformLoc = glGetUniformLocation(progObj[whichShader], "samplerPrim1");
			if (uniformLoc != -1)
			{
				glUniform1i(uniformLoc, FBOID_PRIM1);
			}
			uniformLoc = glGetUniformLocation(progObj[whichShader], "samplerPrim2");
			if (uniformLoc != -1)
			{
				glUniform1i(uniformLoc, FBOID_PRIM2);
			}

			/*
			    uniformLoc = glGetUniformLocation(progObj[whichShader], "tc_offset");
			    if (uniformLoc != -1)
			    {
			        glUniform2fv(uniformLoc, 9, texCoordOffsets);
			    }
			*/
			curpel[0]=sin(rad(zaychik[0]*360.0/4096.0));
			curpel[1]=cos(rad(zaychik[0]*360.0/4096.0));
			uniformLoc = glGetUniformLocation(progObj[whichShader], "curpel1");
			if (uniformLoc != -1)
			{
				glUniform2fv(uniformLoc, 1, curpel);
			}
			curpel[0]=sin(rad(zaychik[1]*360.0/4096.0));
			curpel[1]=cos(rad(zaychik[1]*360.0/4096.0));
			uniformLoc = glGetUniformLocation(progObj[whichShader], "curpel2");
			if (uniformLoc != -1)
			{
				glUniform2fv(uniformLoc, 1, curpel);
			}
		}
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(-WINDOW_X/2,-WINDOW_Y/2,0);

		glTexCoord2f(1,0);
		glVertex3f(WINDOW_X/2,-WINDOW_Y/2,0);

		glTexCoord2f(1,1);
		glVertex3f(WINDOW_X/2,WINDOW_Y/2,0);

		glTexCoord2f(0,1);
		glVertex3f(-WINDOW_X/2,WINDOW_Y/2,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		if (use_shader)
			glUseProgram(0);

		glEnable(GL_BLEND);

		if (whichShader==1 || whichShader==3 || whichShader==5 || whichShader==6 || whichShader==7)
		{
			glPushMatrix();
			glRotatef(-zaychik[0]*360.0/4096.0,0,0,1);
			glColor4f(0.3,0.5,0.3,0.5);

			glLineWidth(lw);
			glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,WINDOW_Y/2,0);
			glEnd();
			glLineWidth(1);
			glPopMatrix();
		}

		if (whichShader==2 || whichShader==4 || whichShader==5 || whichShader==6 || whichShader==7)
		{
			glPushMatrix();
			glRotatef(-zaychik[1]*360.0/4096.0,0,0,1);
			glColor4f(0.3,0.3,0.5,0.5);

			glLineWidth(lw);
			glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,WINDOW_Y/2,0);
			glEnd();
			glLineWidth(1);
			glPopMatrix();
		}

		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);

	}
}

void updateMap()
{
    //printf("Update map: software %d\n", software);

	if(!software)
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboID[FBOID_MAP]);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    for(std::vector<GlMapRegion>::iterator i=_map.begin(); i!=_map.end(); ++i)
    {
        (*i).draw(NightMode);
    }
//    _map.draw(NightMode);

	if(!software)
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
}

void processGraphics();
void processTrajectories();
void processTargets();
void processGhosts();

int loupeSize = 384;
void updateLoupe()
{
    glViewport(0,0,loupeSize,loupeSize);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    float mult = (width/loupeSize)*loupeScale;
    glOrtho(-scale/mult,scale/mult,-scale/mult,scale/mult,100,-100);
    glTranslatef(-(loupeX-width/2)*scale*2/width, (loupeY-height/2)*scale*2/height, 0);
    glRotatef(mangle,1.0,0.0,0.0);
    glRotatef(angle,0.0,0.0,1.0);
    glTranslatef(posX, posY, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, loupeFbo);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

//    glColor4f(1.0,0.0,0.0,1.0);

//    glBegin(GL_TRIANGLES);
//    glVertex2f(-0.5,-0.5);
//    glVertex2f(0.5,-0.5);
//    glVertex2f(0.0,0.5);
//    glEnd();

    GLfloat oldScale = scale;
    scale = scale*(width/loupeSize) / mult;

    for(std::vector<GlMapRegion>::iterator i=_map.begin(); i!=_map.end(); ++i)
    {
        (*i).draw(NightMode);
    }

    processGraphics();
    processTrajectories();
    processTargets();
    if(ghostTime > 0)
        processGhosts();

    glBindFramebuffer(GL_FRAMEBUFFER,0);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glViewport(0,0,width,height);

    scale = oldScale;
}

void drawLimb()
{
	// Рисуем лимб
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-width/2,width/2,-height/2,height/2,1000,-1000);
    glRotatef(mangle,1.0,0.0,0.0);
    glRotatef(angle,0.0,0.0,1.0);

//    glLineWidth(1.5);
//    glBegin(GL_LINES);
//    if(NightMode)
//        glColor3f(0.65,0.7,0.7);
//    else
//        glColor3f(0,0,0);
//    glVertex3f(0,0,0);
//    glColor4ub(0,0,0,0);
//    glVertex3f(0,0,512);
//    glEnd();

    if(NightMode)
        glColor3f(0.65,0.7,0.7);
    else
        glColor3f(0,0,0);
    glMatrixMode(GL_MODELVIEW);
	for(int i=0;i<=359;i++)
	{
		glPushMatrix();
        glRotatef(-i,0,0,1);

        int len;
        int offset;
        if(i%90)
        {
            glLineWidth(lw);
            len=(i%10)?10:20;
            offset=25;
        }
        else
        {
            glLineWidth(lw);
            len=30;
            offset=35;
        }

		glBegin(GL_LINES);
        glVertex3f(0,height/2-offset,0);
        glVertex3f(0,height/2-offset+len,0);
		glEnd();
		glPopMatrix();
	}

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(0,0,0,1);
    glTranslatef(-8,height/2-60,0.0);
//    glRotatef(-angle,0,0,1);
    layoutLimb.Render("N");
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,0,0,1);
    glTranslatef(-10,height/2-60,0.0);
//    glRotatef(-angle-90,0,0,1);
    layoutLimb.Render("W");
    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0,0,1);
    glTranslatef(-6,height/2-60,0.0);
//    glRotatef(-angle-180,0,0,1);
    layoutLimb.Render("S");
    glPopMatrix();

    glPushMatrix();
    glRotatef(270,0,0,1);
    glTranslatef(-6,height/2-60,0.0);
//    glRotatef(-angle-270,0,0,1);
    layoutLimb.Render("E");
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glLineWidth(1);

    glMatrixMode(GL_MODELVIEW);
}

void drawTargetSymbol(MSG1_Target* ptarg, bool isGhost = false)
{
    glLineWidth(1.5);

    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
        double Xtarget = ptarg->getXkm();
        double Ytarget = ptarg->getYkm();
//        double dxOur=0.0,dyOur=0.0;
//        if(sys.ourShip.isSet(MSG6SF_F) || sys.ourShip.isSet(MSG6SF_L))
//            CFLXY(f0,l0,sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),&dxOur,&dyOur);
//        Xtarget += dxOur;
//        Ytarget += dyOur;

//        //Только для проигрывания маневра в режиме относительного движения (полагаем, что цели для которых не задана траектория неподвижны)
//        if(ODmode && !isGhost && ghostTime)
//        {
//            Xtarget -= ourGhostX;
//            Ytarget -= ourGhostY;
//        }
//        _doTransformationsForNMode();
		
        glTranslatef(Xtarget,Ytarget,0);
		if(ptarg->isSet(MSG1SF_K))
			glRotatef(-ptarg->getKgrad(),0,0,1);

        GLdouble aspect=width/height;
        if (width<=height)
            glScalef(scale/(width/2),scale/aspect/(height/2),1);
        else
            glScalef(scale*aspect/(width/2),scale/(height/2),1);

        float alpha = isGhost?0.5:1.0;
		if(ptarg->isSet(MSG1SF_GO))
			switch(ptarg->getGO())
			{
				case GosOp_OUR:
					glColor4f(1,0,0,alpha);
					break;
				case GosOp_ENEMY:
					glColor4f(0,0,1,alpha);
					break;
				default:
					glColor4f(0,0.75,0,alpha);
			}
		else glColor4f(0,0.75,0,alpha);
        
		glBegin(ptarg->getTargetType()==TargetType_VOZD?GL_LINES:GL_LINE_LOOP);
			if(ptarg->getTargetType()==TargetType_NADV)
			{
				glVertex3f(0,12,0);
				glVertex3f(-6,6,0);
				glVertex3f(-6,-12,0);
				glVertex3f(6,-12,0);
				glVertex3f(6,6,0);
			}
			else if(ptarg->getTargetType()==TargetType_PODV)
			{
				glVertex3f(-5,12,0);
				glVertex3f(-5,-12,0);
				glVertex3f(5,-2,0);
				glVertex3f(5,12,0);
			}
			else if(ptarg->getTargetType()==TargetType_VOZD)
			{
				glVertex3f(-8,11,0);
				glVertex3f(8,11,0);
				glVertex3f(0,11,0);
				glVertex3f(0,-11,0);
			}

        glEnd();
    glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
//        _doTransformationsForNMode();
		glTranslatef(Xtarget,Ytarget,0);
        //Ориентируем формуляр горизонтально
        glRotatef(-angle,0.0,0.0,1.0);
//        if(Nmode)
//        {
//         if(ghostTime)
//             //Для прогнозируемого положения СК, если таковое имеется
//             glRotatef(-ourGhostK,0.0,0.0,1.0);
//         else
//             //Для истинного положения СК
//             glRotatef(-sys.ourShip.getKgrad(),0.0,0.0,1.0);
//        }
        
        aspect=width/height;
        if (width<=height)
            glScalef(scale/(width/2),scale/aspect/(height/2),1);
        else
            glScalef(scale*aspect/(width/2),scale/(height/2),1);

		glTranslatef(12,-5,0);
		if(ptarg->sour()==OtogSour_NONE && ptarg->num()==0)
			layout.Render(L"0");
		else if( (ptarg->getTargetType()==TargetType_NADV && formNadv!=MSG11FormNadv_Znak)
			|| (ptarg->getTargetType()==TargetType_VOZD && formVozd!=MSG11FormVozd_Znak)
			|| (ptarg->getTargetType()==TargetType_PODV && formNadv!=MSG11FormNadv_Znak)
            || ptarg->getKey() == selectedKeyOtog
			)
		{
			wchar_t wstr[128];
			int orderNum;
			std::wstring str;
			orderNum=ptarg->getOrderNum();
			if(orderNum==-1)
				str=ptarg->getSourNumString();
			else
			{
				swprintf(wstr,128,L"%d",orderNum);
				str=wstr;
			}
			if(ptarg->getTargetType()==TargetType_NADV &&
                (formNadv==MSG11FormNadv_PD || formNadv==MSG11FormNadv_PDKV || formNadv==MSG11FormNadv_Full || ptarg->getKey() == selectedKeyOtog))
			{
				swprintf(wstr,128,L"\nП %.1f°\nД %.1f мл",ptarg->getPgrad(),ptarg->getDml());
				str+=wstr;
			}
			if(ptarg->getTargetType()==TargetType_PODV &&
                (formNadv==MSG11FormNadv_PD || formNadv==MSG11FormNadv_PDKV || formNadv==MSG11FormNadv_Full || ptarg->getKey() == selectedKeyOtog))
			{
				swprintf(wstr,128,L"\nП %.1f°\nД %.1f км",ptarg->getPgrad(),ptarg->getDkm());
				str+=wstr;
			}
			if(ptarg->getTargetType()==TargetType_VOZD &&
                (formVozd==MSG11FormVozd_PD || formVozd==MSG11FormVozd_PDKV || formVozd==MSG11FormVozd_Full || ptarg->getKey() == selectedKeyOtog))
			{
				swprintf(wstr,128,L"\nП %.1f°\nД %.1f км",ptarg->getPgrad(),ptarg->getDkm());
				str+=wstr;
			}
			if((ptarg->getTargetType()==TargetType_NADV || ptarg->getTargetType()==TargetType_PODV)
                && (formNadv==MSG11FormNadv_KV || formNadv==MSG11FormNadv_PDKV || formNadv==MSG11FormNadv_Full || ptarg->getKey() == selectedKeyOtog)
				&& ptarg->isSet(MSG1SF_K) && ptarg->isSet(MSG1SF_V)
				)
			{
				swprintf(wstr,128,L"\nK %.1f°\nV %.1f уз",ptarg->getKgrad(),ptarg->getVuz());
				str+=wstr;
			}
			if(ptarg->getTargetType()==TargetType_VOZD &&
                (formVozd==MSG11FormVozd_KV || formVozd==MSG11FormVozd_PDKV || formVozd==MSG11FormVozd_Full || ptarg->getKey() == selectedKeyOtog)
				&& ptarg->isSet(MSG1SF_K) && ptarg->isSet(MSG1SF_V))
			{
				swprintf(wstr,128,L"\nK %.1f°\nV %.1f м/с",ptarg->getKgrad(),ptarg->getVms());
				str+=wstr;
			}
            if(ptarg->getTargetType()==TargetType_VOZD && (formVozd==MSG11FormVozd_Full || ptarg->getKey() == selectedKeyOtog))
			{
				if(ptarg->isSet(MSG1SF_H))
				{
					swprintf(wstr,128,L"\nH %.1f км",ptarg->getHkm());
					str+=wstr;
				}
				MSG3_OtogTableList otlist;
				int first=1;
				otlist.query="sourOtog=",ptarg->getSour(),"and numOtog=",ptarg->getNum();
				for(MSG3_OtogTable *pot=otlist.select();pot;pot=otlist.next())
				{
					MSG2_SourTarget starg(pot->getSour(),pot->getNum());
					if(starg.isLoaded())
					{
						if(first)
						{
							str+=L"\n";
							first=0;
						}
						else str+=L" ";
						str+=starg.getSourNumString();
					}
				}
			}
            if(ptarg->getTargetType()==TargetType_PODV && (formNadv==MSG11FormNadv_Full || ptarg->getKey() == selectedKeyOtog))
			{
				if(ptarg->isSet(MSG1SF_H))
				{
					swprintf(wstr,128,L"\nH %.1f км",ptarg->getHkm());
					str+=wstr;
				}
				MSG3_OtogTableList otlist;
				int first=1;
				otlist.query="sourOtog=",ptarg->getSour(),"and numOtog=",ptarg->getNum();
				for(MSG3_OtogTable *pot=otlist.select();pot;pot=otlist.next())
				{
					MSG2_SourTarget starg(pot->getSour(),pot->getNum());
					if(starg.isLoaded())
					{
						if(first)
						{
							str+=L"\n";
							first=0;
						}
						else str+=L" ";
						str+=starg.getSourNumString();
					}
				}
			}
            if(ptarg->getTargetType()==TargetType_NADV && (formNadv==MSG11FormNadv_Full || ptarg->getKey() == selectedKeyOtog))
			{
				MSG3_OtogTableList otlist;
				int first=1;
				otlist.query="sourOtog=",ptarg->getSour(),"and numOtog=",ptarg->getNum();
				for(MSG3_OtogTable *pot=otlist.select();pot;pot=otlist.next())
				{
					MSG2_SourTarget starg(pot->getSour(),pot->getNum());
					if(starg.isLoaded())
					{
						if(first)
						{
							str+=L"\n";
							first=0;
						}
						else str+=L" ";
						str+=starg.getSourNumString();
					}
				}
			}
			layout.Render(str.c_str());
		}
			//font->Render(ptarg->getSourNumString().c_str());
            //font->Render(L"АБВГДКЛМНОПРСТ0123456789");
    glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void drawTargetSymbolSel(double x,double y,double k,TargetType type)
{
	glPushMatrix();
//    double dxOur=0.0,dyOur=0.0;
//    if(sys.ourShip.isSet(MSG6SF_F) || sys.ourShip.isSet(MSG6SF_L))
//        CFLXY(f0,l0,sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),&dxOur,&dyOur);
//    x += dxOur;
//    y += dyOur;
        //Только для проигрывания маневра в режиме относительного движения (полагаем, что цели для которых не задана траектория неподвижны)
//        if(ODmode && ghostTime)
//        {
//            x -= ourGhostX;
//            y -= ourGhostY;
//        }
//        //Режим "Нос"
//        if(Nmode)
//        {
//            if(ghostTime)
//                //Для прогнозируемого положения СК, если таковое имеется
//                glRotatef(ourGhostK,0.0,0.0,1.0);
//            else
//                //Для истинного положения СК
//                glRotatef(sys.ourShip.getKgrad(),0.0,0.0,1.0);
//        }
    
		glTranslatef(x,y,0);
		glRotatef(-k,0,0,1);

		GLdouble aspect=width/height;
		if (width<=height)
			glScalef(scale/(width/2),scale/aspect/(height/2),1);
		else
			glScalef(scale*aspect/(width/2),scale/(height/2),1);

		glBegin(GL_POLYGON);
			if(type==TargetType_NADV)
			{
				glVertex3f(0,12,0);
				glVertex3f(-6,6,0);
				glVertex3f(-6,-12,0);
				glVertex3f(6,-12,0);
				glVertex3f(6,6,0);
			}
			else if(type==TargetType_PODV)
			{
				glVertex3f(-5,12,0);
				glVertex3f(-5,-12,0);
				glVertex3f(5,-2,0);
				glVertex3f(5,12,0);
			}
			else if(type==TargetType_VOZD)
			{
				glVertex3f(8,11,0);
				glVertex3f(-8,11,0);
				glVertex3f(-2,-11,0);
				glVertex3f(2,-11,0);
			}
		glEnd();
	glPopMatrix();
}

void _drawTrace(MSG1_Target *target)
{
    if(_traces.find(target->getKey()) == _traces.end())
    {
        GlPrimitive trace;
        trace.setType(GL_POINTS);
        trace.setColor(0,200,200,200);
        trace.setPointSize(5.0);
        _traces.insert(std::pair<uint,GlPrimitive>(target->getKey(),trace));
    }
    
    double X=target->getXkm(),Y=target->getYkm();
    double Xlast=0.0,Ylast=0.0;
//    CFLXY(f0,l0,target->getFgrad(),target->getLgrad(),&X,&Y);
    int lastIndex = _traces[target->getKey()].vertexCount() - 1;
    if(lastIndex >= 0)
    {
        Xlast = *(_traces[target->getKey()].xLast());
        Ylast = *(_traces[target->getKey()].yLast());
    }
    if((int)(X*100) != (int)(Xlast*100) || (int)(Y*100) != (int)(Ylast*100))
    {
        printf("Add trace: %.2f  %.2f\n",X,Y);
        _traces[target->getKey()].addVertex(X,Y);
        //_traces[target->getKey()].print();
    }
    
    glPushMatrix();
//    //Режим "Нос"
//    if(Nmode)
//    {
//        if(ghostTime)
//            //Для прогнозируемого положения СК, если таковое имеется
//            glRotatef(ourGhostK,0.0,0.0,1.0);
//        else
//            //Для истинного положения СК
//            glRotatef(sys.ourShip.getKgrad(),0.0,0.0,1.0);
//    }
//    //Только для проигрывания маневра в режиме относительного движения (полагаем, что графические объекты неподвижны)
//    if(ODmode && ghostTime)
//        glTranslatef(-ourGhostX, -ourGhostY, 0.0);
    
    _traces[target->getKey()].draw();
    glPopMatrix();
}

int _bufferizeSimpleGraphics(std::pair<uint,GlPrimitive> *buf, MSG251_GraphElem *msg)
{
    if(!buf || !msg)
        return 0;

    buf->first = msg->getKey();
    if(msg->isSet(MSG251SF_COLOR))
        buf->second.setColor(msg->getColorR(),msg->getColorG(),msg->getColorB(),msg->getColorA());
    if(msg->isSet(MSG251SF_COLORCONTOUR))
        buf->second.setColorContour(msg->getColorContourR(),msg->getColorContourG(),msg->getColorContourB(),msg->getColorContourA());
    if(msg->isSet(MSG251SF_POINTSIZE))
        buf->second.setPointSize(msg->getPointSize());
    if(msg->isSet(MSG251SF_LINEWIDTH))
        buf->second.setLineWidth(msg->getLineWidth());
    
    MSG250_GraphPointList pointList;
    pointList.query = "elemId=",msg->getKey(),"order by pointNum";
    for(MSG250_GraphPoint *point = pointList.select(); point; point = pointList.next())
    {      
        double X,Y;
        printf("PIXELS: %d\n", msg->getPixels());
        if(msg->isSet(MSG251SF_KEYOTOG) || msg->getPixels())
        {
            X = point->getVal1();
            Y = point->getVal2();
        }
        else
        {
            CFLXY(f0,l0,point->getVal1(),point->getVal2(),&X,&Y);
//             printf("Bufferize simple graphics:\n"
//                                              "\tFL: %.2f  %.2f\n"
//                                              "\tXY: %.2f  %.2f\n", point->getVal1(), point->getVal2(),X,Y);
        }
        buf->second.addVertex(X,Y);
        printf("Bufferize simple graphics: add vertex %.2f : %.2f\n", X,Y);
    }
    
    switch(msg->getElemType())
    {
        case MSG251ElemType_POINTS:
            buf->second.setType(GL_POINTS);
            break;
        case MSG251ElemType_LINES:
            buf->second.setType(GL_LINE_STRIP);
            break;
        case MSG251ElemType_POLYGON:
            buf->second.setType(GL_TRIANGLES);
            GLushort *indexes;
            GLushort indexCount;
            _tesselatePolygon(buf->second.vertices(),buf->second.vertexCount(),&indexes,&indexCount);
            buf->second.setIndexes(indexes,indexCount);
            break;
        default:
            buf->second.setType(GL_POINTS);
            break;
    }
    
    return 1;
}

int _bufferizeEllipseBasedGraphics(std::pair<uint,GlPrimitive> *buf, MSG251_GraphElem *msg)
{
    if(!buf || !msg)
        return 0;

    double Xc=0.0,Yc=0.0;               //Координаты центра
    double Xa=0.0,Ya=0.0;               //Координаты точки, определяющей положение первой полуоси
    double Xb=0.0,Yb=0.0;               //Координаты точки, определяющей длину второй полуоси
    double Xs=0.0,Ys=0.0;               //Координаты точки, определяющей начальный угол для дуги
    double Xw=0.0,Yw=0.0;               //Координаты точки, определяющей ширину дуги
    double Xr1=0.0,Yr1=0.0;             //Координаты точки, определяющей положение первой полуоси молого эллипса пара-сектора
    double Xr2=0.0,Yr2=0.0;             //Координаты точки, определяющей положение второй полуоси молого эллипса пара-сектора
    
    MSG250_GraphPointList points;
    points.query="elemId=",msg->getKey(),"order by pointNum";
    MSG250_GraphPoint *point = points.select();
    if(!point)
        return 0;
    if(msg->isSet(MSG251SF_KEYOTOG) || msg->getPixels())
    {
        Xc = point->getVal1();
        Yc = point->getVal2();
        
        point = points.next();
        if(!point)
            return 0;
        Xa = point->getVal1();
        Ya = point->getVal2();
        
        point = points.next();
        if(!point)
            return 0;
        Xb = point->getVal1();
        Yb = point->getVal2();
        
        if(msg->getElemType() == MSG251ElemType_ELLIPSE_ARC || msg->getElemType() == MSG251ElemType_SECTOR || msg->getElemType() == MSG251ElemType_PARASECTOR)
        {
            point = points.next();
            if(!point)
                return 0;
            Xs = point->getVal1();
            Ys = point->getVal2();
            
            point = points.next();
            if(!point)
                return 0;
            Xw = point->getVal1();
            Yw = point->getVal2();
            
            if(msg->getElemType() == MSG251ElemType_PARASECTOR)
            {
                point = points.next();
                if(!point)
                    return 0;
                Xr1 = point->getVal1();
                Yr1 = point->getVal2();
                
                point = points.next();
                if(!point)
                    return 0;
                Xr2 = point->getVal1();
                Yr2 = point->getVal2();
            }
        }
    }
    else
    {
        CFLXY(f0,l0,point->getVal1(),point->getVal2(),&Xc,&Yc);
        point = points.next();
        if(!point)
            return 0;
        CFLXY(f0,l0,point->getVal1(),point->getVal2(),&Xa,&Ya);
        point = points.next();
        if(!point)
            return 0;
        CFLXY(f0,l0,point->getVal1(),point->getVal2(),&Xb,&Yb);
        
        if(msg->getElemType() == MSG251ElemType_ELLIPSE_ARC || msg->getElemType() == MSG251ElemType_SECTOR || msg->getElemType() == MSG251ElemType_PARASECTOR)
        {
            point = points.next();
            if(!point)
                return 0;
            CFLXY(f0,l0,point->getVal1(),point->getVal2(),&Xs,&Ys);
            
            point = points.next();
            if(!point)
                return 0;
            CFLXY(f0,l0,point->getVal1(),point->getVal2(),&Xw,&Yw);
            
            if(msg->getElemType() == MSG251ElemType_PARASECTOR)
            {
                point = points.next();
                if(!point)
                    return 0;
                CFLXY(f0,l0,point->getVal1(),point->getVal2(),&Xr1,&Yr1);
                
                point = points.next();
                if(!point)
                    return 0;
                CFLXY(f0,l0,point->getVal1(),point->getVal2(),&Xr2,&Yr2);
            }
        }
    }
    
    double R1=0.0,R2=0.0,direction=0.0; //Длины полуосей и направление по первой полуоси (от севера по часовой стрелке в градусах)
    direction = atan2(Xa-Xc, Ya-Yc);
    R1 = sqrt(pow(Xa-Xc,2) + pow(Ya-Yc,2));
    R2 = sqrt(pow(Xb-Xc,2) + pow(Yb-Yc,2));
    
    printf("Bufferize ellipse:\n\tdirection: %.1f\n"
                               "\tR1:        %.1f\n"
                               "\tR2:        %.1f\n", grad(direction), R1, R2);
    
    double startAngle = 0.0;
    double widthAngle = 360.0;
    double r1 = 0.0, r2 = 0.0;
    //Если дуга, то рассчитываем ее ширину и начальный угол
    if(msg->getElemType() == MSG251ElemType_ELLIPSE_ARC || msg->getElemType() == MSG251ElemType_SECTOR || msg->getElemType() == MSG251ElemType_PARASECTOR)
    {
        
        startAngle = grad(atan2(Xs-Xc,Ys-Xc)) - grad(direction);
        startAngle += (startAngle < 0.0)?360.0:0.0;
        widthAngle = grad(atan2(Xw-Xc,Yw-Xc)) - startAngle - grad(direction);
        //printf("WIDTH: %.2f\n",widthAngle);
        widthAngle += (widthAngle < 0.0)?360.0:0.0;
        if((int)widthAngle == 0)
            widthAngle = 360.0;
        printf("Bufferize ellipse arc:\n\tstartAngle:   %.2f\n"
                                     "\twidthAngle:   %.2f\n", startAngle,widthAngle);
        
        if(msg->getElemType() == MSG251ElemType_PARASECTOR)
        {
            r1 = sqrt(pow(Xr1,2)+pow(Yr1,2));
            r2 = sqrt(pow(Xr2,2)+pow(Yr2,2));
        }
    }
    
    const double step = 5.0;
    buf->first = msg->getKey();
    if(msg->isSet(MSG251SF_COLOR))
        buf->second.setColor(msg->getColorR(),msg->getColorG(),msg->getColorB(),msg->getColorA());
    if(msg->isSet(MSG251SF_COLORCONTOUR))
        buf->second.setColorContour(msg->getColorContourR(),msg->getColorContourG(),msg->getColorContourB(),msg->getColorContourA());
    if(msg->isSet(MSG251SF_POINTSIZE))
        buf->second.setPointSize(msg->getPointSize());
    if(msg->isSet(MSG251SF_LINEWIDTH))
        buf->second.setLineWidth(msg->getLineWidth());
    
    double currentWidth = 0.0;
    
    bool isLast = false;
    while(!isLast)
    {
        if(currentWidth > widthAngle)
        {
            currentWidth = widthAngle;
            isLast = true;
        }
        else if((int)(currentWidth*1000) == (int)(widthAngle*1000))
            isLast = true;
        
        double p = R1*R2 / sqrt(pow(R1,2)*pow(sin(rad(startAngle+currentWidth)),2) + pow(R2,2)*pow(cos(rad(startAngle+currentWidth)),2));
        //Точка на эллипсе
        double Xtmp;
        double Ytmp;
        Xtmp = p*sin(rad(startAngle + currentWidth));
        Ytmp = p*cos(rad(startAngle + currentWidth));
        //printf("Ellipse contour: %.2f  %.2f\n", Xtmp, Ytmp);
        
        //Поворачиваем систему координат на угол поворота эллипса
        buf->second.addVertex(Xtmp*cos(direction) + Ytmp*sin(direction) + Xc, -Xtmp*sin(direction) + Ytmp*cos(direction) + Yc);
        if(!isLast)
            currentWidth += step;
    }
    
    switch(msg->getElemType())
    {
        case MSG251ElemType_ELLIPSE_ARC:
            buf->second.setType(GL_LINE_STRIP);
            break;
        case MSG251ElemType_ELLIPSE:
        {
            buf->second.setType(GL_POLYGON);
            break;
        }
        case MSG251ElemType_SECTOR: 
        {
            buf->second.addVertex(Xc,Yc);
            buf->second.setType(GL_POLYGON);
            break;
        }
        case MSG251ElemType_PARASECTOR:
        {
            isLast = false;
            while(!isLast)
            {
                if(currentWidth < 0.0)
                {
                    currentWidth = 0.0;
                    isLast = true;
                }
                else if((int)(currentWidth*1000) == 0)
                    isLast = true;
                
                double p = r1*r2 / sqrt(pow(r1,2)*pow(sin(rad(startAngle+currentWidth)),2) + pow(r2,2)*pow(cos(rad(startAngle+currentWidth)),2));
                //Точка на эллипсе
                double Xtmp;
                double Ytmp;
                Xtmp = p*sin(rad(startAngle + currentWidth));
                Ytmp = p*cos(rad(startAngle + currentWidth));
                //printf("Ellipse contour: %.2f  %.2f\n", Xtmp, Ytmp);
                
                buf->second.addVertex(Xtmp*cos(direction) + Ytmp*sin(direction) + Xc, -Xtmp*sin(direction) + Ytmp*cos(direction) + Yc);
                if(!isLast)
                    currentWidth -= step;
            }
            buf->second.setType(GL_TRIANGLES);
            GLushort *indexes;
            GLushort indexCount;
            _tesselatePolygon(buf->second.vertices(),buf->second.vertexCount(),&indexes,&indexCount);
            buf->second.setIndexes(indexes,indexCount);
            break;
        }
        default:
            return 0;
    }
    printf("Bufferize ellipse finish:\n\tvertex count: %d\n\tindex count:  %d\n",buf->second.vertexCount(), buf->second.indexCount());
    return 1;
}

int _bufferizeGraphics(std::pair<uint,GlPrimitive> *buf, MSG251_GraphElem *msg)
{
    switch(msg->getElemType())
    {
        case MSG251ElemType_POINTS:
        case MSG251ElemType_LINES:
        case MSG251ElemType_POLYGON:
            return _bufferizeSimpleGraphics(buf, msg);
        case MSG251ElemType_ELLIPSE:
        case MSG251ElemType_ELLIPSE_ARC:
        case MSG251ElemType_SECTOR:
        case MSG251ElemType_PARASECTOR:    
            return _bufferizeEllipseBasedGraphics(buf, msg);
        default:
            break;
    }
    return 0;
}

void _doTransformationsForNMode()
{
    //Режим "Нос"
    if(Nmode)
    {
        if(ghostTime)
            //Для прогнозируемого положения СК, если таковое имеется
            glRotatef(ourGhostK,0.0,0.0,1.0);
        else
            //Для истинного положения СК
            glRotatef(sys.ourShip.getKgrad(),0.0,0.0,1.0);
    }
}

void _doTransformationsFor(MSG251_GraphElem *gelem/*, bool isGhost = false*/)
{
    //ПРЕОБРАЗОВАНИЯ КООРДИНАТ

    if(gelem->isSet(MSG251SF_KEYOTOG))
    {
        double dxForGhost=0.0,dyForGhost=0.0,dkForGhost=0.0;
        if(ghostTime)
        {
            MessageList<MSG451_Trajectory> trajList;
            if(skolTask)
                trajList.query="keyOtog=",gelem->getKeyOtog(),"and taskNum=",skolTask;
            else
                trajList.query="keyOtog=",gelem->getKeyOtog();
            for(MSG451_Trajectory *ptraj = trajList.select(); ptraj; ptraj = trajList.next())
            {
                double F0,L0,K0,F,L,K;
                MSG451_Trajectory traj(ptraj->getKey());
                if(!traj.isLoaded())
                    continue;
                traj.getParams(0,&F0,&L0,&K0,0);
                traj.getParams(ghostTime,&F,&L,&K,0);
                CFLXY(F0,L0,F,L,&dxForGhost,&dyForGhost);
                dkForGhost=K-K0;
            }
        }

        double dxOur=0.0,dyOur=0.0;
        if(sys.ourShip.isSet(MSG6SF_F) || sys.ourShip.isSet(MSG6SF_L))
            CFLXY(f0,l0,sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),&dxOur,&dyOur);
        if(gelem->getKeyOtog())
        {
            MSG1_Target target(gelem->getKeyOtog());
            glTranslatef(target.getXkm()+dxOur+dxForGhost, target.getYkm()+dyOur+dyForGhost, 0.0);
            glRotatef(-target.getKgrad()-dkForGhost, 0.0,0.0,1.0);
        }
        else
        {
            glTranslatef(dxOur+dxForGhost, dyOur+dyForGhost, 0.0);
            glRotatef(-sys.ourShip.getKgrad()-dkForGhost, 0.0,0.0,1.0);
        }
    }

    if(gelem->getPixels())
    {
        GLdouble aspect=width/height;
        if (width<=height)
            glScalef(scale/(width/2),scale/aspect/(height/2),1);
        else
            glScalef(scale*aspect/(width/2),scale/(height/2),1);
    }
}

void selectOtogTarget()
{
	glInitNames();
	glPushName(0);

    double dx=0.0,dy=0.0;
    if(sys.ourShip.isSet(MSG6SF_F) || sys.ourShip.isSet(MSG6SF_L))
        CFLXY(f0,l0,sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),&dx,&dy);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(dx,dy,0.0);

	MSG1_TargetList lst;
	for(MSG1_Target* ptarg=lst.select();ptarg;ptarg=lst.next())
	{
		glLoadName(ptarg->getKey());
		drawTargetSymbolSel(ptarg->getXkm(),ptarg->getYkm(),ptarg->isSet(MSG1SF_K)?ptarg->getKgrad():0,ptarg->getTargetType());
	}

    glPopMatrix();

	glutSwapBuffers();
}

void drawMeans()
{
	Mean meanN[6]={Mean_AK176,Mean_AK630_1,Mean_AK630_2,Mean_PALMA,Mean_PURGA,Mean_3R60};
	float meanSize[6]={45,35,35,35,35,35};
	double meanP[6]={350,130,230,10,270,90};
	double meanD[6]={470,470,470,460,455,455};
	float meanTX[6][4]={
		{0.0,   1.0/3, 1.0/3, 0.0},
		{1.0/3, 2.0/3, 2.0/3, 1.0/3},
		{2.0/3, 1.0,   1.0,   2.0/3},
		{0.0,   1.0/3, 1.0/3, 0.0},
		{1.0/3, 2.0/3, 2.0/3, 1.0/3},
		{2.0/3, 1.0,   1.0,   2.0/3}
	};
	float meanTY[6][4]={
		{1.0,1.0,2.0/3,2.0/3},
		{1.0,1.0,2.0/3,2.0/3},
		{1.0,1.0,2.0/3,2.0/3},
		{2.0/3,2.0/3,1.0/3,1.0/3},
		{2.0/3,2.0/3,1.0/3,1.0/3},
		{2.0/3,2.0/3,1.0/3,1.0/3},
	};
	GLint viewport[4];
	GLdouble mvmtx[16],projmtx[16];
	GLdouble wx,wy,wz;
	GLdouble aspect=width/height;

	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvmtx);
	glGetDoublev(GL_PROJECTION_MATRIX,projmtx);

	glColor3f(1.0,0,0);

	MessageList<MSG9_CU> culist;
	for(MSG9_CU* pcu=culist.select();pcu;pcu=culist.next())
	{
		for(int i=0;i<6;i++)
			if(meanN[i]==pcu->getMean())
			{
				MSG1_Target targ(pcu->getSourOtog(),pcu->getNumOtog());
				if(targ.isLoaded())
				{
					gluProject(targ.getXkm(),targ.getYkm(),0,mvmtx,projmtx,viewport,&wx,&wy,&wz);

					glPushMatrix();
					if (width<=height)
						glScalef(scale/(width/2),scale/aspect/(height/2),1);
					else
						glScalef(scale*aspect/(width/2),scale/(height/2),1);

					double x,y;
					pdinxy(Kugol2P(sys.ourShip.getKgrad(),meanP[i]),meanD[i]+(WINDOW_X==1200?88:0),&x,&y);

					//printf("draw line (%f, %f)-(%f %f)\n",x,y,wx,wy);
					glBegin(GL_LINES);
					glVertex3f(x,y,0);
					glVertex3f(wx-width/2,wy-height/2,0);
					glEnd();
					glPopMatrix();
				}
				break;
			}
	}

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texIDMean);
	glPushMatrix();

		if (width<=height)
			glScalef(scale/(width/2),scale/aspect/(height/2),1);
		else
			glScalef(scale*aspect/(width/2),scale/(height/2),1);

		for(int i=0;i<6;i++)
		{
			double x,y;
			glPushMatrix();
			pdinxy(Kugol2P(sys.ourShip.getKgrad(),meanP[i]),meanD[i]+(WINDOW_X==1200?88:0),&x,&y);
			glTranslatef(x,y,0);

			glBegin(GL_QUADS);
				glTexCoord2f(meanTX[i][0],meanTY[i][0]);
				glVertex3f(-meanSize[i],meanSize[i],0);

				glTexCoord2f(meanTX[i][1],meanTY[i][1]);
				glVertex3f(meanSize[i],meanSize[i],0);

				glTexCoord2f(meanTX[i][2],meanTY[i][2]);
				glVertex3f(meanSize[i],-meanSize[i],0);

				glTexCoord2f(meanTX[i][3],meanTY[i][3]);
				glVertex3f(-meanSize[i],-meanSize[i],0);
			glEnd();
			glPopMatrix();
		}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void calculateOurGhost(uint ghostTime)
{
    MSG451_Trajectory ourTraj(_ourTrajKey);
    if(!ourTraj.isLoaded())
        return;
    double Four,Lour;
    if(!ourTraj.getParams((double)ghostTime,&Four,&Lour,&ourGhostK,0))
        return;

    CFLXY(sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),Four,Lour,&ourGhostX,&ourGhostY);
}

//Ширина дуги, которая будет представлена в виде прямой, градусы
//double arcStep = 5.0;

//Шаг, секунды
const uint trajStep = 10;

int _bufferizeTrajectory(std::pair<uint,GlPrimitive> *buf, MSG451_Trajectory *msg, bool isODmode = false, uint ourTrajKey = 0)
{   
    if(!buf || !msg)
        return 0;
    buf->first = msg->getKey();
    if((msg->getKey() == ourTrajKey || !msg->getKeyOtog()) && isODmode)
        return 1;
    buf->second.setType(GL_LINE_STRIP);
    if(msg->isSet(MSG451SF_WIDTH))
        buf->second.setLineWidth(msg->getWidth());
    else
        buf->second.setLineWidth(2);
    if(msg->isSet(MSG451SF_COLOR))
        buf->second.setColor(msg->getColorR(), msg->getColorG(), msg->getColorB(), msg->getColorA());
    else
        buf->second.setColor(255,0,0,200);
    
    uint t = 0;
    bool isComplete = false;
    while (!isComplete && t < 86400/*сутки*/)
    {
        if(t > msg->getTrajTime() || !msg->getTrajTime())
        {
            t = msg->getTrajTime();
            isComplete = true;
        }
        double F,L,X,Y;
        if(!msg->getParams((double)t,&F,&L,0,0))
        {
            t += trajStep;
            continue;
        }
        if(isODmode && msg->getKeyOtog())
        {
            //puts("OD");
            MSG451_Trajectory ourTraj(ourTrajKey);
            double Four,Lour;
            if(!ourTraj.isLoaded())
            {
                Four = sys.ourShip.getFgrad();
                Lour = sys.ourShip.getLgrad();
            }
            else
                if(!ourTraj.getParams((double)t,&Four,&Lour,0,0))
                {
                    t += trajStep;
                    continue;
                }
            CFLXY(Four,Lour,F,L,&X,&Y);
        }
        else
        {
            CFLXY(f0,l0,F,L,&X,&Y);
        }
        printf("Bufferize trajectory point: XY %.2f : %.2f\n"
               "                            FL %.2f : %.2f\n",X,Y,F,L);
        buf->second.addVertex(X,Y);
        t += trajStep;
    }
    return 1;
}

void drawGhost(uint ghostTime, MSG451_Trajectory *ptraj)
{   
    if(ghostTime >= (uint)ptraj->getTrajTime())
        ghostTime = (uint)ptraj->getTrajTime() - 1;
    //printf("DRAW GHOST ON %d / %.2f\n", ghostTime, ptraj->getTrajTime());
    
    double Fghost=0.0,Lghost=0.0,Kghost=0.0;
    if(!ptraj->getParams((double)ghostTime,&Fghost,&Lghost,&Kghost,0))
        return;
//    printf("TRAJ PARAM ON %d: F=%.2f L=%.2f K=%.1f\n",ghostTime, Fghost, Lghost, Kghost);
    
    double Xghost, Yghost;
    if(ODmode && !ptraj->getKeyOtog())
    {   
        Xghost = 0.0;
        Yghost = 0.0;
    }
    else
    {
        MSG451_Trajectory ourTraj(_ourTrajKey);
        if(!ourTraj.isLoaded())
            return;
        double Four,Lour;
        if(!ourTraj.getParams((double)ghostTime,&Four,&Lour,&ourGhostK,0))
            return;
        CFLXY(Four,Lour,Fghost,Lghost,&Xghost,&Yghost);
    }

    MSG1_Target ghost;
    if(ptraj->getKeyOtog() != 0)
    {
        ghost.setSourNum(ptraj->getSourOtog(),ptraj->getNumOtog());
        ghost.load();
    }
    else
    {
        //Свой корабль
        ghost.setGO(GosOp_OUR);
        ghost.setTargetType(TargetType_NADV);
    }
    ghost.setXYkm(Xghost,Yghost);
    ghost.setKgrad(Kghost);
    drawTargetSymbol(&ghost, true);
}

void drawLoupe()
{
    if(linseEffect)
        glUseProgram(progObj[LOUPE]);
    else
        glUseProgram(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,loupeTex);

    GLint uniformLoc = glGetUniformLocation(progObj[LOUPE], "sampler");
    if (uniformLoc != -1)
    {
        glUniform1i(uniformLoc, 0);
    }

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, 1,-1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(loupeX - width/2, -loupeY + height/2, 0.0);
    
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(-loupeSize/2, -loupeSize/2);

    glTexCoord2f(0,1);
    glVertex2f(-loupeSize/2, loupeSize/2);

    glTexCoord2f(1,1);
    glVertex2f(loupeSize/2, loupeSize/2);

    glTexCoord2f(1,0);
    glVertex2f(loupeSize/2, -loupeSize/2);
    glEnd();


    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    glUseProgram(0);
}

void reloadTrajectories()
{
    for(std::map<uint,GlPrimitive>::iterator i = _trajectories.begin(); i != _trajectories.end(); i++)
    {
        MSG451_Trajectory traj((*i).first);
        if(!traj.isLoaded())
            continue;
//        _trajectories.erase(traj.getKey());
        std::pair<uint,GlPrimitive> buf;
        if(_bufferizeTrajectory(&buf,&traj,ODmode,_ourTrajKey))
            (*i).second = buf.second;
    }
}

void reloadGraphics()
{
    for(std::map<uint,GlPrimitive>::iterator i = _graphics.begin(); i != _graphics.end(); i++)
    {
        MSG251_GraphElem gelem((*i).first);
        if(!gelem.isLoaded())
            continue;
//        _graphics.erase(gelem.getKey());
        std::pair<uint,GlPrimitive> buf;
        if(_bufferizeGraphics(&buf,&gelem))
            (*i).second = buf.second;
    }
}

void processAnimation()
{
//    if(toScale-scale > 0.001)
//    {
//        if(do_animation)
//            scale += (toScale-scale)/10;
//        else
//            scale = toScale;
//        resize(width,height);
//        setWindowTitle();
//        clearTexture(FBOID_PRIM1);
//        clearTexture(FBOID_PRIM2);
//    }
//    else if(scale-toScale > 0.001)
//    {
//        if(do_animation)
//            scale -= (scale-toScale)/10;
//        else
//            scale = toScale;
//        resize(width,height);
//        setWindowTitle();
//        clearTexture(FBOID_PRIM1);
//        clearTexture(FBOID_PRIM2);
//    }
//    else
//        scale = toScale;

    if(fabs(toScale-scale) > 0.001)
    {
        if(do_animation)
            scale = animScale.getValue();
        else
            scale = toScale;
        resize(width,height);
        setWindowTitle();
        clearTexture(FBOID_PRIM1);
        clearTexture(FBOID_PRIM2);
    }

//    if(toLoupeScale-loupeScale > 0.001)
//    {
//        if(do_animation)
//            loupeScale += (toLoupeScale-loupeScale)/10;
//        else
//            loupeScale = toLoupeScale;
//    }
//    else if(loupeScale-toLoupeScale > 0.001)
//    {
//        if(do_animation)
//            loupeScale -= (loupeScale-toLoupeScale)/10;
//        else
//            loupeScale = toLoupeScale;
//    }
//    else
//        loupeScale = toLoupeScale;

    if(fabs(toLoupeScale-loupeScale) > 0.001)
    {
        if(do_animation)
            loupeScale = animLoupeScale.getValue();
        else
            loupeScale = toLoupeScale;
    }
    
//    if(toPosX - posX > 0.001)
//    {
//        if(do_animation)
//            posX += (toPosX-posX)/10;
//        else
//            posX = toPosX;
//        resize(width,height);
//    }
//    else if(posX - toPosX > 0.001)
//    {
//        if(do_animation)
//            posX -= (posX-toPosX)/10;
//        else
//            posX = toPosX;
//        resize(width,height);
//    }
//    else
//        posX = toPosX;

//    if(toPosY - posY > 0.001)
//    {
//        if(do_animation)
//            posY += (toPosY-posY)/10;
//        else
//            posY = toPosY;
//        resize(width,height);
//    }
//    else if(posY - toPosY > 0.001)
//    {
//        if(do_animation)
//            posY -= (posY-toPosY)/10;
//        else
//            posY = toPosY;
//        resize(width,height);
//    }
//    else
//        posY = toPosY;
    if(fabs(toPosX-posX) > 0.001 || fabs(toPosY-posY) > 0.001)
    {
        if(do_animation)
        {
            posX = animPosX.getValue();
            posY = animPosY.getValue();
        }
        else
        {
            posX = toPosX;
            posY = toPosY;
        }
        resize(width,height);
    }


//    if(toAngle - angle > 0.001)
//    {
//        if(toAngle-angle > 180.0)
//            toAngle-=360.0;
//        else
//        {
//            if(do_animation)
//                angle += (toAngle-angle)/10;
//            else
//                angle = toAngle;
//            resize(width,height);
//        }
//    }
//    else if(angle - toAngle > 0.001)
//    {
//        if(angle-toAngle > 180.0)
//            angle-=360.0;
//        else
//        {
//            if(do_animation)
//                angle -= (angle-toAngle)/10;
//            else
//                angle = toAngle;
//            resize(width,height);
//        }
//    }
//    else
//    {
//        while(angle < 0.0)
//            angle+=360.0;
//        while(angle > 360.0)
//            angle-=360.0;
//        toAngle = angle;
//    }
    if(fabs(toAngle - angle) > 0.001)
    {
        if(do_animation)
            angle = animAngle.getValue();
        else
            angle = toAngle;
//        printf("RESIZE: angle %.2f\n", angle);
        resize(width,height);
    }


    if(toMangle - mangle > 0.001)
    {
        if(do_animation)
            mangle += (toMangle-mangle)/10;
        else
            mangle = toMangle;
        resize(width,height);
    }
    else if(mangle - toMangle > 0.001)
    {
        if(do_animation)
            mangle -= (mangle-toMangle)/10;
        else
            mangle = toMangle;
        resize(width,height);
    }
    else
        mangle = toMangle;
}

void processGraphics()
{
    for(std::map<uint,GlPrimitive>::iterator i = _graphics.begin(); i != _graphics.end(); i++)
    {
        MSG251_GraphElem gelem((*i).first);
        if(!gelem.isLoaded())
            continue;
        if(skolTask && gelem.getTaskNum() != skolTask && find(_graphicsShow,(*i).first) == _graphicsShow.end())
            continue;
        glPushMatrix();
        _doTransformationsFor(&gelem);
        (*i).second.draw();
        glPopMatrix();
    }
}

void processTargets()
{
    //processTargets
    // рисуем свой корабль
    MSG1_Target ourShip(OtogSour_NONE,0);
    ourShip.setXYkm(0.0,0.0);
    
    ourShip.setKgrad(sys.ourShip.getKgrad());
    ourShip.setGO(GosOp_OUR);
    ourShip.setTargetType(TargetType_NADV);

    double dx=0.0,dy=0.0;
    if(sys.ourShip.isSet(MSG6SF_F) || sys.ourShip.isSet(MSG6SF_L))
        CFLXY(f0,l0,sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),&dx,&dy);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(dx,dy,0.0);
    //Проверка на наличие траектории
    MessageList<MSG451_Trajectory> trajList;
    if(skolTask)
        trajList.query = "keyOtog=",0,"and taskNum=",skolTask;
    else
        trajList.query = "keyOtog=",0;
    if(!ghostTime || !trajList.select() || !ODmode)
    {
        drawTargetSymbol(&ourShip);
        if(draw_traces)
            _drawTrace(&ourShip);
    }
    MSG1_TargetList lst;
    for(MSG1_Target* ptarg=lst.select();ptarg;ptarg=lst.next())
    {
        if(ptarg->getTargetType()==TargetType_NADV && !showNadv) continue;
        if(ptarg->getTargetType()==TargetType_PODV && !showPodv) continue;
        if(ptarg->getTargetType()==TargetType_VOZD && !showVozd) continue;
        if((ptarg->getGO()==GosOp_ENEMY || ptarg->getGO()==GosOp_NO || ptarg->getGO()==GosOp_NONE) && !showEnemy) continue;
        if(ptarg->getGO()==GosOp_OUR && !showOur) continue;
        if(skolTask)
            trajList.query = "keyOtog=",ptarg->getKey(),"and taskNum=",skolTask;
        else
            trajList.query = "keyOtog=",ptarg->getKey();
//        if(!ghostTime || !trajList.select())
        {
            drawTargetSymbol(ptarg);
            if(draw_traces)
                _drawTrace(ptarg);
        }
    }
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void processTrajectories()
{
    for(std::map<uint,GlPrimitive>::iterator i = _trajectories.begin(); i != _trajectories.end(); i++)
    {
        if((*i).first == _ourTrajKey && ODmode)
            continue;

        MSG451_Trajectory traj((*i).first);
        if(!traj.isLoaded())
            continue;
        if(skolTask && traj.getTaskNum() != skolTask && find(_trajectoryShow,(*i).first) == _trajectoryShow.end())
            continue;

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
//        _doTransformationsForNMode();

        double dxOur=0.0,dyOur=0.0;
        if(sys.ourShip.isSet(MSG6SF_F) || sys.ourShip.isSet(MSG6SF_L))
            CFLXY(f0,l0,sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),&dxOur,&dyOur);
        if(ODmode)
            glTranslatef(dxOur+ourGhostX,dyOur+ourGhostY,0.0);
        (*i).second.draw();
        //Точки на концах
        glPointSize(10);
        glColor4ub((*i).second.colorR(),(*i).second.colorG(),(*i).second.colorB(),(*i).second.colorA());
        glBegin(GL_POINTS);
        GLdouble *x,*y;
        x = (*i).second.xFirst();
        y = (*i).second.yFirst();
        if(x && y)
            glVertex2f(*x,*y);
        x = (*i).second.xLast();
        y = (*i).second.yLast();
        if(x && y)
            glVertex2f(*x,*y);
        glEnd();

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
}

void processGhosts()
{
    for(std::map<uint,GlPrimitive>::iterator i = _trajectories.begin(); i != _trajectories.end(); i++)
    {
        MSG451_Trajectory traj((*i).first);
        if(!traj.isLoaded())
            continue;
        if(skolTask && traj.getTaskNum() != skolTask && find(_trajectoryShow,(*i).first) == _trajectoryShow.end())
            continue;
        //Рисуем "призрака" на траектории
        double dx=0.0,dy=0.0;
        if(sys.ourShip.isSet(MSG6SF_F) || sys.ourShip.isSet(MSG6SF_L))
            CFLXY(f0,l0,sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),&dx,&dy);
        glPushMatrix();
//        if(ODmode)
        {
            dx+=ourGhostX;
            dy+=ourGhostY;
        }
        glTranslatef(dx,dy,0.0);
        drawGhost(ghostTime, &traj);
        glPopMatrix();
    }
}

GLubyte *pLoupe = 0;

void render()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	sys.waitMessage(0);

    processAnimation();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texID[0]);
    glPushMatrix();

    if (need_update_map)
    {
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        updateMap();
        need_update_map=0;
    }

    if (draw_primary && !software)
        drawPrimary();

    if (do_blend)
    {
//		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
    }

    processGraphics();
    processTrajectories();
    processTargets();
    if(ghostTime > 0)
        processGhosts();
    
    //taskChanged
    if(skolTask != skolTaskPrev)
    {
        char note[128]={0,};
        sprintf(note, "Task changed to %d",skolTask);
        noteManager->addNote(note);
        skolTaskPrev = skolTask;
    }

    if(rmbPressed)
    {
        updateLoupe();
        drawLoupe();
    }
    glLineWidth(1);

    if(ODmode)
    {
        drawLimb();
//        drawMeans();
    }


    //Пробуем оповещения
    //****************
    noteManager->process(3);
    //****************


    glPopMatrix();

    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_BLEND);

	glutSwapBuffers();
	fps++;
	do_selection=0;
	
}

void _tesselatePolygon(GLdouble *vertices, GLushort vertexCount, GLushort **indexes, GLushort *indexCount)
{
    MapPolygon newPolygon={0,};
    std::vector<int> start;
    std::vector<int> count;

    newPolygon.vertexCount = vertexCount;
    newPolygon.pVertexFL = (GLdouble*)malloc(sizeof(GLdouble)*3*vertexCount);
    memcpy(newPolygon.pVertexFL,vertices,sizeof(GLdouble)*3*vertexCount);

    start.push_back(0);
    count.push_back(vertexCount);
    tesselatePolygon(&newPolygon,&start,&count);
    
    *indexes=newPolygon.pIndexes;
    *indexCount=newPolygon.indexesCount;
}

void loadLoupe()
{
    pLoupe=(GLubyte*)malloc(loupeSize*loupeSize*4);
    memset(pLoupe,0,loupeSize*loupeSize*4);

    glGenTextures(1,&loupeTex);
    glGenFramebuffers(1,&loupeFbo);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,loupeTex);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,loupeSize,loupeSize,0,GL_RGBA,GL_UNSIGNED_BYTE,pLoupe);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindFramebuffer(GL_FRAMEBUFFER,loupeFbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, loupeTex,0);

    glBindFramebuffer(GL_FRAMEBUFFER,0);
//    glBindTexture(GL_TEXTURE_2D, 0);
}

void reloadMap()
{
    _map.clear();
    const char *path = "../data/mapsGL/";
    DIR *mapDir = opendir(path); //rewinddir("./maps/"); set to 0 entry
    struct dirent *entry=NULL;
    while((entry = readdir(mapDir)) != NULL)
    {
        GlMapRegion mapReg;
        if(strncmp(entry->d_name, ".", 2) && strncmp(entry->d_name, "..", 3))
        {
            printf("Read map %s\n", entry->d_name);
            std::string filePath = std::string(path) + std::string(entry->d_name);
            if(mapReg.load(filePath.c_str(), f0, l0, mercator))
            {
                mapReg.print();
                _map.push_back(mapReg);
            }
        }
    }
}

void msg1_del(MSG1_Target *pmsg)
{
    printf("[MSG DELETED]  MSG1_Target %d\n",pmsg->getKey());
    _traces.erase(pmsg->getKey());
}

void msg6_handler(MSG6_OurShip *pmsg)
{
    if(ODmode)
    {
        double dx,dy;
        CFLXY(f0,l0,pmsg->getFgrad(),pmsg->getLgrad(),&dx,&dy);
        setPos(-dx,-dy,false);
        if(Nmode)
            setAngle(pmsg->getKgrad());
    }
}

void msg11_handler(MSG11_ITOControl* pmsg)
{
    printf("[MSG RECEIVED] MSG11_ITOControl %d\n",pmsg->getKey());
    setScale(pmsg->getScale());
	printf("\tSet scale %f\n",scale);

	showEnemy=pmsg->getShowEnemy();
	showOur=pmsg->getShowOur();
	showNadv=pmsg->getShowNadv();
	showPodv=pmsg->getShowPodv();
	showVozd=pmsg->getShowVozd();
	formNadv=pmsg->getFormNadv();
	formVozd=pmsg->getFormVozd();
}

void msg200_handler(MSG200_WmCmd *pmsg)
{
    printf("[MSG RECEIVED] MSG200_WmCmd %d\n",pmsg->getKey());
	if(pmsg->getCmd()==MSG200Cmd_RAISE)
		skolTask=pmsg->getWndId();
}

void msg251_handler(MSG251_GraphElem *pmsg)
{
    printf("[MSG RECEIVED] MSG251_GraphElem %d\n",pmsg->getKey());
//    printf("\tRemove graphics %d from buffer\n",pmsg->getKey());
    _graphics.erase(pmsg->getKey());

    MSG251_GraphElem gelem(pmsg->getKey());
    if(!gelem.isLoaded())
        return;
    std::pair<uint,GlPrimitive> buf;
    if(_bufferizeGraphics(&buf,&gelem))
        _graphics.insert(buf);
}

void msg251_del(MSG251_GraphElem *pmsg)
{
    printf("[MSG DELETED]  MSG251_GraphElem %d\n",pmsg->getKey());
    printf("\tRemove graphics %d from buffer\n",pmsg->getKey());
    _graphics.erase(pmsg->getKey());
}

void msg252_handler(MSG252_GraphShow *pmsg)
{
    printf("[MSG RECEIVED] MSG252_GraphShow %d\n",pmsg->getKey());
    if(skolTask && pmsg->getTaskNum() != skolTask)
    {
        if(pmsg->getElemNum())
            _graphicsShow.push_back(pmsg->getKey());
        else
        {
            MessageList<MSG251_GraphElem> gelemList;
            gelemList.query="taskNum=",pmsg->getTaskNum(),"order by keyOtog";
            for(MSG251_GraphElem* pgelem=gelemList.select();pgelem;pgelem=gelemList.next())
                _graphicsShow.push_back(pgelem->getKey());
        }
    }
}

void msg252_del(MSG252_GraphShow *pmsg)
{
    printf("[MSG DELETED]  MSG251_GraphShow %d\n",pmsg->getKey());
    printf("\tRemove graphics %d from buffer\n",pmsg->getKey());
    if(skolTask && pmsg->getTaskNum() != skolTask)
    {
        std::vector<uint>::iterator i = find(_graphicsShow,pmsg->getKey());
        if(i != _graphicsShow.end())
            _graphicsShow.erase(i);
    }
}

void msg451_handler(MSG451_Trajectory *pmsg)
{
    printf("[MSG RECEIVED] MSG451_Trajectory %d\n",pmsg->getKey());
//    printf("\tRemove trajectory %d from buffer\n",pmsg->getKey());
    _trajectories.erase(pmsg->getKey());

    if(pmsg->isSet(MSG451SF_KEYOTOG) && !pmsg->getKeyOtog())
        _ourTrajKey = pmsg->getKey();

    MSG451_Trajectory traj(pmsg->getKey());
    if(!traj.isLoaded())
        return;
    std::pair<uint,GlPrimitive> buf;
    if(_bufferizeTrajectory(&buf,&traj,ODmode,_ourTrajKey))
        _trajectories.insert(buf);
}

void msg451_del(MSG451_Trajectory *pmsg)
{
    printf("[MSG DELETED]  MSG451_Trajectory %d\n",pmsg->getKey());
    printf("\tRemove trajectory %d from buffer\n",pmsg->getKey());
    _trajectories.erase(pmsg->getKey());
}

void msg452_handler(MSG452_TrajectoryTime *pmsg)
{
    if(skolTask && pmsg->getTaskNum() != skolTask)
        return;

    if(pmsg->getTime() != ghostTime)
    {
        ghostTime = pmsg->getTime();
        calculateOurGhost(ghostTime);

        if(ODmode)
        {
            double dx,dy;
            CFLXY(f0,l0,sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),&dx,&dy);
            setPos(-dx-ourGhostX, -dy-ourGhostY, false);
            if(Nmode)
                setAngle(ourGhostK, true);
        }
    }
}

void msg452_del(MSG452_TrajectoryTime *pmsg)
{
    printf("[MSG DELETED]  MSG452_TrajectoryTime %d\n",pmsg->getKey());
    printf("\tSet ghostTime to 0\n");

    ghostTime = 0;
//    for(std::map<uint,GlPrimitive>::iterator i = _graphics.begin(); i != _graphics.end(); i++)
//    {
//        MSG251_GraphElem gelem((*i).first);
//        if(!gelem.isLoaded())
//            continue;
//        if(gelem.isSet(MSG251SF_KEYOTOG))
//            (*i).second.setIdentity();
//    }
    need_update_map = 1;
}

void msg453_handler(MSG453_TrajectoryShow *pmsg)
{
    printf("[MSG RECEIVED] MSG453_TrajectoryShow %d\n",pmsg->getKey());
    if(skolTask && pmsg->getTaskNum() != skolTask)
    {
        if(pmsg->getTrajNum())
            _trajectoryShow.push_back(pmsg->getKey());
        else
        {
            MessageList<MSG451_Trajectory> trajList;
            trajList.query="taskNum=",pmsg->getTaskNum(),"order by keyOtog";
            for(MSG451_Trajectory* ptraj=trajList.select();ptraj;ptraj=trajList.next())
                _trajectoryShow.push_back(ptraj->getKey());
        }
    }
}

void msg453_del(MSG453_TrajectoryShow *pmsg)
{
    printf("[MSG DELETED]  MSG451_TrajectoryShow %d\n",pmsg->getKey());
    printf("\tRemove trajectory %d from buffer\n",pmsg->getKey());
    if(skolTask && pmsg->getTaskNum() != skolTask)
    {
        std::vector<uint>::iterator i = find(_trajectoryShow,pmsg->getKey());
        if(i != _trajectoryShow.end())
            _trajectoryShow.erase(i);
    }
}

int main(int argc,char* argv[])
{
	assert(sys.Init(argc,argv));
    sys.subscribeDel(msg1_del);
    sys.subscribe(msg6_handler);
	sys.subscribe(msg11_handler);
	sys.subscribe(msg200_handler);
    sys.subscribe(msg251_handler);
	sys.subscribeDel(msg251_del);
    sys.subscribe(msg252_handler);
    sys.subscribeDel(msg252_del);
    sys.subscribe(msg451_handler);
    sys.subscribeDel(msg451_del);
    sys.subscribe(msg452_handler);
    sys.subscribeDel(msg452_del);
    sys.subscribe(msg453_handler);
    sys.subscribeDel(msg453_del);

	if (argc<3)
	{
		printf("Usage: app G|M (Gauss|Mercator) FPS (0 - max fps)\n");
		mercator=0;
		dofps=0;
	}
	else {
		mercator=(argv[1][0]=='G')?0:1;
		dofps=atoi(argv[2]);
	}

	glutInit(&argc,argv);
//    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_STENCIL|GLUT_DEPTH);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(WINDOW_X,WINDOW_Y);
	wnd=glutCreateWindow("Map");

	printf("GL_VENDOR %s\n",glGetString(GL_VENDOR));
	printf("GL_RENDERER %s\n",glGetString(GL_RENDERER));
	printf("GL_VERSION %s\n",glGetString(GL_VERSION));
	printf("GL_SHADING_LANGUAGE_VERSION %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

	if(strstr((const char*)glGetString(GL_RENDERER),(const char*)"Software"))
	{
		printf("Software mode ON\n");
		software=1;
		dofps=10;
	}

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutTimerFunc(100,timer,0);
	if (!dofps)
		glutIdleFunc(render);

    glClearColor(0.67f, .753f, .694f, 1.0f);
//    glClearColor(0,0,0, 0);
//    glClearColor(0,1,0, 0);
//    glFrontFace(GL_CW);

	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);

	/*    glClearStencil(0);
	    glEnable(GL_STENCIL_TEST);
	    glStencilFunc(GL_EQUAL,0,0);
	    glStencilOp(GL_KEEP,GL_INCR,GL_INCR);
	*/
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GEQUAL,0);
//    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
//    glShadeModel(GL_SMOOTH);
//    glShadeModel(GL_FLAT);

	GLint iUnits;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &iUnits);
	printf("GL_MAX_TEXTURE_UNITS %d\n",iUnits);

	// Load and compile shaders
	for (int i = 0; i < TOTAL_SHADERS; i++)
	{
		PrepareShader(i);
	}

    reloadMap();

//    if(!_map.load("./map3.bin"))
//    {
//        loadMap();
//        _map.load("./map3.bin");
//    }

//    _map.print();
	loadPrimary();
	loadMeans();
    loadLoupe();

	setWindowTitle();

	//font=new FTPixmapFont(fontname);
	font=new FTTextureFont(fontname);
	//font=new FTBufferFont(fontname);
	//font=new FTPolygonFont(fontname);
	if(font->Error())
	{
		printf("Error open font %s\n",fontname);
		exit(1);
	}
	if(!font->FaceSize(13))
	{
		puts("Error set font size\n");
		exit(1);
	}
	layout.SetLineLength(400);
	layout.SetFont(font);
	layout.SetLineSpacing(0.7);

    fontLimb=new FTTextureFont(fontname);
    if(fontLimb->Error())
    {
        printf("Error open font %s\n",fontname);
        exit(1);
    }
    if(!fontLimb->FaceSize(21))
    {
        puts("Error set font size\n");
        exit(1);
    }

    layoutLimb.SetLineLength(400);
    layoutLimb.SetFont(fontLimb);
    layoutLimb.SetLineSpacing(0.7);

    fontNote=new FTTextureFont(fontname);
    if(fontNote->Error())
    {
        printf("Error open font %s\n",fontname);
        exit(1);
    }
    if(!fontNote->FaceSize(18))
    {
        puts("Error set font size\n");
        exit(1);
    }
    layoutNote.SetLineLength(400);
    layoutNote.SetFont(fontNote);
    layoutNote.SetLineSpacing(0.7);
//    printf("fontNote: %d\n", fontNote);
    noteManager = new GlNotificationManager(WINDOW_X, WINDOW_Y);
//    noteManager->setLayout(&layoutNote);

    GlNote prototype;
    prototype.setFont(fontname, 18);
//    prototype.setFont(fontNote);
    prototype.setTextColor(255,255,255);
    prototype.setBackColor(0,0,0,150);
    noteManager->setNotePrototype(prototype);

    animScale.setFunction(Animation::Function_Bow);
    animPosX.setFunction(Animation::Function_Bow);
    animPosY.setFunction(Animation::Function_Bow);
    animAngle.setFunction(Animation::Function_Bow);
    animMangle.setFunction(Animation::Function_Bow);
    animLoupeScale.setFunction(Animation::Function_Bow);

	glutMainLoop();

    //delete noteManager;
	puts("Bye");

	return 0;
}


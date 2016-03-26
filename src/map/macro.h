/****************************************************************************
*                                                                           *
*   MACROS                                                                  *
*                                                                           *
****************************************************************************/

#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#ifdef __BORLANDC__
  #include <alloc.h>
#else
  #define farcalloc calloc
  #define farrealloc realloc
  #define beep() fprintf(stdout,"==| beep |==\n")
#endif


#define AMIN(X,Y) ( ((X)<(Y)) ? (X) : (Y) )  /* minimum of X,Y             */
#define AMAX(X,Y) ( ((X)>(Y)) ? (X) : (Y) )  /* maximum of X,Y             */
#define AXOR(X1,X2) ( !(X1) + !(X2) ) /* ==1, if ((a && !b) || (!a && b))  */

/****************************************************************************
*                                                                           *
*   COMMON MACROS                                                           *
*                                                                           *
****************************************************************************/
/*   Points amount: per 10 grad of curve, ellipse,segm.                    */
#define DPG(ALEN)             ( (int)(R2G(ABS(ALEN))*0.1) )

/*   Banque accumulation (nakoplenie): ix = (1+0.01*i)^1/m - 1, for example:
     i4 = (1+0.15)^1/4-1, there i=15% - year percent, m=4 times a year     */
#define BACCUM(I,M)           ( pow(1.0+0.01*(I),1.0/(M)) - 1 )

/*   Banque expense (trata): vx=1/(1+ix) = (1+i)^(-1/12)                   */
#define BEXPEN(I,M)           pow(1.0+0.01*(I),-1.0/(M))

/*   Sum of K-members of geometry progression S=(1 + Q + Q^2 +...+ Q^K     */
#define GEOM(K,Q)             ( ( pow((Q),(K+1)) - 1 ) / ((Q)-1) )

/**/
#define ROUNDING(X)           ( (int)((X) + 0.5*SIGN(X)) )

/**/
#define MNOZ(X,Y)             ( (Y) * ROUNDING((X)/(Y)) )

/*   if X/Y = natural                                                      */
#define KRUGL(X,Y)       ( X0(X) || ( (X>=Y) && !((int)(X) % ((int)(Y))) ) )

//#define EVEN(X)               KRUGL(X,2)       /* chetniy   */
//#define ODD(X)                ( !EVEN(X) )     /* nechetniy */
#define ODD(X)                ( (X) % 2 )     /* nechetniy */
#define EVEN(X)               ( !ODD(X) )       /* chetniy   */

/*   simple sign(X)                                                        */
#define SIGN(X)               ( ((X)>=-NOL) ? 1 : -1 )

/*   random 1, -1                                                          */
#define SIGNUM                ( (rand()>RAND_MAX/2) ? 1 : -1 )

/*   random in [0..1]                                                      */
#define RANDOM                ( (LD)(rand())/(LD)(RAND_MAX) )

/*   random in [X1..X2]                                                    */
#define RANDOMXX(X1,X2)       ( (X1)+RANDOM*((X2)-(X1)) )

/*   = X*X                                                                 */
#define SQR(X)                ( (X)*(X) )

/*   = X*X*X                                                               */
#define CB(X)                 ( (X)*(X)*(X) )

/*   = module(X) = |X|                                                     */
//#define ABS(X)                ( ((X)<0) ? -(X) : (X) )

/*   to exchange X,Y through buf                                           */
#define EXCH(X,Y,BUF)         ( (BUF)=(X), (X)=(Y), (Y)=(BUF) )

/*   S(triangle)        ????????????????                                   */
#define STRI(X1,Y1,X2,Y2,X3,Y3) ( 0.5*                                     \
  fabsl(((X1)-(X3))*((Y2)-(Y3))-((X2)-(X3))*((Y1)-(Y3))) )

/**/
#define TIME2SEC(H,M,S,HUND) (3600*(H)+60*(M)+(S)+0.01*(HUND) )

/*   Radians to grad                                                       */
#define R2G(X)               ( 180.0L/M_PIl*(X) )
/*   Grad to radians                                                       */
#define G2R(X)               ( M_PIl/180.0L*(X) )
/*   To make radian in limits [0..2*Pi]                                    */
#define R2R(X)               ( (X) - 2*M_PIl*floor((X)/2/M_PIl) )

/*   Kilometers to miles                                                   */
#define KM2MIL(X)            ( 1000.0L/MILE*(X) )
/*   Miles to kilometers                                                   */
#define MIL2KM(X)            ( MILE/1000.0L*(X) )
/*   Knots to m/sec                                                        */
#define KNOT2MS(X)           ( MILE/3600.0L*(X) )
/*   m/sec to knots                                                        */
#define MS2KNOT(X)           ( 3600.0L/MILE*(X) )

/*   To increase or to decrease                                            */
#define MODDECR(X)           ( ((X)>0) ? (X)-1 : (X)+1 )

/*   if X inside [X1..X2] or [X2..X1]                                      */
#define INSIDE(X,X1,X2)      ( ( (X)>=(X1) && (X)<=(X2) ) ||               \
                               ( (X)>=(X2) && (X)<=(X1) ) )

/*   if X,Y inside [X1..X2] or [X2..X1]                                    */
#define INSIDE2(X,Y,X1,X2)   ( INSIDE(X,X1,X2) && INSIDE(Y,X1,X2) )

/*   if X inside [X1..X2] or [X2..X1] with the gap                         */
#define INSIDEZ(X,X1,X2)     INSIDE(X,(X1)-NOL,(X2)+NOL)

/*   if X is small, then make X=0                                          */
#define NUL(X)               ( INSIDE(X,-NOL,NOL) ? 0 : (X) )

/*   if X is close to A, then make X=A                                     */
#define NULA(A,X)            ( INSIDE((X)-(A),-NOL,NOL) ? (A) : (X) )

/*   if X in [A-B..A+B], then make X=A                                     */
#define NULAB(A,B,X)         ( INSIDE((X)-(A),-(B),B) ? (A) : (X) )

/*   To remove tail of mantissa: C=1E-13L (like that)                      */
#define NULC(C,X) ( (C)*(LI)((X)/(C)) )

/**/
#define MID3(X,Y,Z)          ( ((X)+(Y)+(Z))/3 )

/*   for loop - multiplyer for local variables and parameters              */
#define TSIK(I,IMIN,IMAX)    ( (LD)((I)-(IMIN))/((IMAX)-(IMIN)) )

/*   To get quadrant of angle                                              */
#define QUADRANT(X)          (                                             \
  INSIDE(X,0,M_PIl_2) ? 1 : (                                              \
  INSIDE(X,M_PIl_2, M_PIl) ? 2 : (                                         \
  (INSIDE(X,M_PIl,3*M_PIl_2) || INSIDE(X,-M_PIl_2,-M_PIl)) ? 3 : 4 )))

/****************************************************************************
*                                                                           *
*   STRING MACROS                                                           *
*                                                                           *
****************************************************************************/
/*   string -> float                                                       */
#define C2F(ST)               ( *(float *) (ST) )

/*   USI X -> UC X1,UC X2                                                  */
#define USI2UCUC(X,X1,X2)     ( {                                          \
  UC *C=(UC *)&(X);                                                        \
  (X1)=*C;                                                                 \
  (X2)=*(C+1); } )

/*   UC X1, UC X2 -> USI X                                                 */
#define UCUC2USI(X1,X2,X)     ( {                                          \
  UC *C=(UC *)&(X);                                                        \
  C[0]=(X1);                                                               \
  C[1]=(X2); } )

/*   smart copying for STRS, STRL ????????                                 */
#define STRSCPY(DEST,SRC)      ( ((SRC)==NULL) ? (strcpy((DEST),"")) :     \
  (strncpy((DEST),(SRC),SIZE_LEN3-1)) )
#define STRLCPY(DEST,SRC)      ( ((SRC)==NULL) ? (strcpy((DEST),"")) :     \
  (strncpy((DEST),(SRC),SIZE_LEN2-1)) )

/*   binary representation in string -> to a data                          */
#define STR2(ST)              strtol(ST,NULL,2)


/*   to remove LEFT spaces                                                 */
#define LTRIM(ST)               {                                          \
  char *P=(ST);                                                            \
  while (*P==' ') P++;                                                     \
  memmove((ST),P,strlen(P)+1); }

/*   to remove RIGHT spaces                                                */
#define RTRIM(ST)               {                                          \
  char *P=(ST)+strlen(ST);                                                 \
  while (*(--P)==' ' || *P=='\n') *P=0; }

/*   to remove BOTH spaces (and from the middle)                           */
#define TRIM(ST)                { LTRIM(ST); RTRIM(ST); strtr(' ',ST); }

#define ADDSLASH(ST)            { int i=strlen(ST); ST[i]=SLASH; ST[i+1]=0; }

/*   indexes = [128..255](unsigned char) = [-128..-1](char), char ST[128] */
#define KOI8(ST) { \
  memset(ST, 0, 128); \
  ST[35] = '£'; \
  ST[64] = 'À'; \
  ST[65] = 'Á'; \
  ST[66] = 'Â'; \
  ST[67] = 'Ã'; \
  ST[68] = 'Ä'; \
  ST[69] = 'Å'; \
  ST[70] = 'Æ'; \
  ST[71] = 'Ç'; \
  ST[72] = 'È'; \
  ST[73] = 'É'; \
  ST[74] = 'Ê'; \
  ST[75] = 'Ë'; \
  ST[76] = 'Ì'; \
  ST[77] = 'Í'; \
  ST[78] = 'Î'; \
  ST[79] = 'Ï'; \
  ST[80] = 'Ð'; \
  ST[81] = 'Ñ'; \
  ST[82] = 'Ò'; \
  ST[83] = 'Ó'; \
  ST[84] = 'Ô'; \
  ST[85] = 'Õ'; \
  ST[86] = 'Ö'; \
  ST[87] = '×'; \
  ST[88] = 'Ø'; \
  ST[89] = 'Ù'; \
  ST[90] = 'Ú'; \
  ST[91] = 'Û'; \
  ST[92] = 'Ü'; \
  ST[93] = 'Ý'; \
  ST[94] = 'Þ'; \
  ST[95] = 'ß'; }

/****************************************************************************
*                                                                           *
*   BIT MACROS                                                              *
*                                                                           *
****************************************************************************/
/*   If threre is N-bit in X                                               */
#define IFBIT(X,N)              ( ((X)  & (1UL << (N))) != 0 )

/*   If X1 has the same bits set, as X2 has                                */
#define IFBIT1(X1,X2)           ( ((X1) & (X2)) != 0 )

/*   To set N-bit in X                                                     */
#define SETBIT(X,N)             ( (X)  |= (1UL << (N)) )

/*   To set to X1 the same bits, as X2 has                                 */
#define SETBIT1(X1,X2)          ( (X1) |= (X2) )

/*   To remove N-bit in X                                                  */
#define UNSETBIT(X,N)           ( (X) &= ~(1UL << (N)) )

/*   To remove in X1 bits, which are in X2                                 */
#define UNSETBIT1(X1,X2)        ( (X1) &= ~(X2) )

/*   To toggle N-bit in X                                                  */
#define TOGGLEBIT(X,N)          ( (X) ^=  (1UL << (N)) )

/*   To toggle in X1 bits, which are in X2                                 */
#define TOGGLEBIT1(X1,X2)       ( (X1)^=  X2 )

/*   To unset bits to left from N inclusive (unsigned)                     */
#define CLEARLBIT(X,N)          ( { (X)<<=N; (X)>>=N; } )

/*   To unset bits to right from N inclusive (any)                         */
#define CLEARRBIT(X,N)          ( { (X)>>=N; (X)<<=N; } )

/**/
#define CLEARBIT(X,N1,N2)       ( { CLEARLBIT(X,N1); CLEARRBIT(X,N2); } )

/*   If N1-bit in X1, then to set N2-bit in X2, and vise versa             */
#define SUBIT(X1,N1,X2,N2)      ( IFBIT(X1,N1) ? SETBIT(X2,N2) :           \
  UNSETBIT(X2,N2) )

/*   If N1-bit in X1, then to unset N2-bit in X2, and vise versa           */
#define SUBIT1(X1,N1,X2,N2)     ( IFBIT(X1,N1) ? UNSETBIT(X2,N2) :         \
  SETBIT(X2,N2) )

/*   If X1, then to set N2-bit in X2, and vise versa                       */
#define SUBIT2(X1,X2,N2)        ( (X1) ? SETBIT(X2,N2) : UNSETBIT(X2,N2) )

/*   If X1, then to set in X2 bits, which are in X3                        */
#define SUBIT3(X1,X2,X3)        ( (X1) ? SETBIT1(X2,X3) : UNSETBIT1(X2,X3) )

/*   For 1-bit color: to get color, if having coords, image width size and
     bit string itself,
     unsigned char *data (*.xbm)                                           */
#define GETBIT(w,data)          IFBIT( *((data) + i*((w)/8+1) + j/8), j%8 )

/****************************************************************************
*                                                                           *
*   EQUALITY MACROS                                                         *
*                                                                           *
****************************************************************************/
/****************************************************************************
*   Equality exact and with the gap                                         *
****************************************************************************/
/*   If X exactly equal to Y                                               */
#define EQ(X,Y)                ( (X)==(Y) )

/*   If X almost equal to Y                                                */
#define EQZ(X,Y)               ( fabs((X)-(Y))<NOL )

/*   If X,Y,Z are equal                                                    */
#define EQ3(X,Y,Z)             ( EQ(X,Y) && EQ(X,Z) /* && EQ(Y,Z) */ )

/*   If X,Y,Z are almost equal                                             */
#define EQ3Z(X,Y,Z)            ( EQZ(X,Y) && EQZ(X,Z) /* && EQZ(Y,Z) */ )

/****************************************************************************
*   Equality exact to 0                                                     *
****************************************************************************/
#define X0(X)                  EQ(X,0)
#define X20(X1,X2)             ( X0(X1) && X0(X2) )
#define X30(X1,X2,X3)          ( X0(X1) && X20(X2,X3) )
#define X40(X1,X2,X3,X4)       ( X0(X1) && X30(X2,X3,X4) )
#define X60(X1,X2,X3,X4,X5,x6) ( X30(X1,X2,X3) && X30(X4,X5,x6) )

/****************************************************************************
*   Equality with the gap to 0, i.e. X=(-NOL..NOL)                        *
****************************************************************************/
#define XZ(X)                  EQZ(X,0)
#define X2Z(X1,X2)             ( XZ(X1) && XZ(X2) )
#define X2Z_(X1,X2)            ( XZ(X1) || XZ(X2) )
#define X3Z(X1,X2,X3)          ( XZ(X1) && X2Z(X2,X3) )
#define X3Z_(X1,X2,X3)         ( XZ(X1) || X2Z_(X2,X3) )
#define X4Z(X1,X2,X3,X4)       ( XZ(X1) && X3Z(X2,X3,X4) )
#define X4Z_(X1,X2,X3,X4)      ( XZ(X1) || X3Z_(X2,X3,X4) )

/****************************************************************************
*   Minimums                                                                *
****************************************************************************/
/*   Minimum !=0                                                           */
#define MINNZ(X,Y)             (((X)==0) ? (Y) : ((Y)==0) ? (X) : AMIN(X,Y))

/*   Minimum !=0 with the gap                                              */
#define MINANZ(X,Y)            ( ((X)<NOL && (Y)<NOL) ? 0 :              \
  ((X)<NOL) ? (Y) : ((Y)<NOL) ? (X) : AMIN(X,Y) )

/*   Minimum of 3 magnitudes                                               */
#define MIN3(X,Y,Z)            AMIN(X,AMIN(Y,Z))

/*   Minimum of 3 magnitudes with the gap                                  */
#define MIN3ANZ(X,Y,Z)         MINANZ(X,MINANZ(Y,Z))

/*   Minimum of 4 magnitudes                                               */
#define MIN4(X1,X2,X3,X4)      AMIN(AMIN(X1,X2),AMIN(X3,X4))

/*   Minimum of 4 magnitudes not 0 with the gap                            */
#define MIN4ANZ(X1,X2,X3,X4)   MINANZ(MINANZ(X1,X2),MINANZ(X3,X4))

/*   Minimum of 5 magnitudes not 0 with the gap                            */
#define MIN5ANZ(X1,X2,X3,X4,X5) MINANZ(MIN3ANZ(X1,X2,X3),MINANZ(X4,X5))

/****************************************************************************
*   Maximums                                                                *
****************************************************************************/
/*   Maximum not 0 with the gap                                            */
#define MAXANZ(X,Y)            ( ((X)<NOL && (Y)<NOL) ? 0 :              \
  ((X)<NOL) ? (Y) : ((Y)<NOL) ? (X) : AMAX(X,Y) )

/*   Maximum of 3 magnitudes                                               */
#define MAX3(X,Y,Z)            AMAX(X,AMAX(Y,Z))

/*   Maximum of 3 magnitudes not 0 with the gap                            */
#define MAX3ANZ(X,Y,Z)         MAXANZ(X,MAXANZ(Y,Z))

/*   Maximum of 4 magnitudes not 0 with the gap                            */
#define MAX4(X1,X2,X3,X4)      AMAX(AMAX(X1,X2),AMAX(X3,X4))

/****************************************************************************
*   Restrict: to make X inside [X1..X2]                                     *
****************************************************************************/
//#define RESTRICT(X,X1,X2)    ( ((X)<(X1)) ? (X1) : ((X)>(X2)) ? (X2) : (X) )
#define RESTRICT(X,X1,X2) ( ((X)<AMIN(X1,X2)) ? AMIN(X1,X2) : ( \
  ((X)>AMAX(X1,X2)) ? AMAX(X1,X2) : (X) ) )

/****************************************************************************
*                                                                           *
*   PRINTF MACROS                                                           *
*                                                                           *
****************************************************************************/
/*   to print a byte binary (in bits)                                      */
#define FPCHAR(X) fprintf(stdout,"%3d %#4x \"%c\" {%d%d%d%d%d%d%d%d}",     \
  (UC)(X),(UC)(X),(UC)(X),                                                 \
  IFBIT(X,7),IFBIT(X,6),IFBIT(X,5),IFBIT(X,4),                             \
  IFBIT(X,3),IFBIT(X,2),IFBIT(X,1),IFBIT(X,0))

/*   to make a string from a byte binary                                   */
#define SBYTE(X,ST) sprintf((ST),"%d={%d%d%d%d%d%d%d%d} ",                 \
  (unsigned char)(X),                                                      \
  IFBIT(X,7),IFBIT(X,6),IFBIT(X,5),IFBIT(X,4),                             \
  IFBIT(X,3),IFBIT(X,2),IFBIT(X,1),IFBIT(X,0))

/*   to make a string from a byte binary (to take 3 bits)                  */
#define SBYTE3(X,ST) sprintf(ST,"%d={%d%d%d} ",(unsigned char)(X),         \
  IFBIT(X,2),IFBIT(X,1),IFBIT(X,0))

/*   to print a Short Int binary (in bits)                                 */
#define FPUSI(X) fprintf(stdout,"%3d %#10x "                               \
  "{%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d}",                                    \
  (USI)(X),(USI)(X),                                                       \
  IFBIT(X,15),IFBIT(X,14),IFBIT(X,13),IFBIT(X,12),                         \
  IFBIT(X,11),IFBIT(X,10),IFBIT(X,9), IFBIT(X,8),                          \
  IFBIT(X,7), IFBIT(X,6), IFBIT(X,5), IFBIT(X,4),                          \
  IFBIT(X,3), IFBIT(X,2), IFBIT(X,1), IFBIT(X,0))
#define FPUSI1(ST,X) { \
  fprintf(stdout,"%10s = ",ST); \
  FPUSI(X); \
  fprintf(stdout,"\n"); }

/*   to print a Long Double binary (in bits)                               */
#define FPLD(X) {fprintf(stdout,"%3d %#10x "                               \
  "{%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d}",                                    \
  (USI)(X),(USI)(X),                                                       \
  IFBIT(X,15),IFBIT(X,14),IFBIT(X,13),IFBIT(X,12),                         \
  IFBIT(X,11),IFBIT(X,10),IFBIT(X,9), IFBIT(X,8),                          \
  IFBIT(X,7), IFBIT(X,6), IFBIT(X,5), IFBIT(X,4),                          \
  IFBIT(X,3), IFBIT(X,2), IFBIT(X,1), IFBIT(X,0))

/**/
#define FPMASSIVCHAR(IMAX,P) { int I;                                      \
  for (I=0; I<(IMAX); I++) fprintf(stdout,"%d ",(char)(*(P+I)));           \
  fprintf(stdout,"\n"); }
#define FPMASSIVUC(IMAX,P) { int I;                                        \
  for (I=0; I<(IMAX); I++) fprintf(stdout,"%d ",(UC)(*(P+I)));             \
  fprintf(stdout,"\n"); }
#define FPMASSIVINT(IMAX,P) { int I;                                       \
  for (I=0; I<(IMAX); I++) fprintf(stdout,"%d ",(int)(*(P+I)));            \
  fprintf(stdout,"\n"); }
#define FPMASSIVULI(IMAX,P) { int I;                                       \
  for (I=0; I<(IMAX); I++) fprintf(stdout,"%lu ",(ULI)(*(P+I)));           \
  fprintf(stdout,"\n"); }
#define FPMASSIVLD(IMAX,P) { int I;                                        \
  for (I=0; I<(IMAX); I++) fprintf(stdout,"%29.28Lg\n ",(LD)(*(P+I)));     \
  fprintf(stdout,"\n"); }

/****************************************************************************
*                                                                           *
*   ERROR MACROS: NOT TO WRITE ';' AFTER GLUK                               *
*                                                                           *
****************************************************************************/
#define GLUA1(L/*length*/,C/*char*/) {   int I; \
  for (I=0; I<(L); I++) fprintf(stderr,"%c",C); }
#define GLUA2       fprintf(stderr,"\n")
#define GLUA3       fprintf(stderr,"*")
#define GLUA4(L)    { GLUA1(L,'*'); GLUA2; }                  // **********\n
#define GLUA5(L)    { GLUA3; GLUA1((L)-2,' '); GLUA3; GLUA2; }// *        *\n
#define GLUA6(L,ST) { fprintf(stderr,"*   %s",ST); \
  GLUA1(L-strlen(ST)-5,' '); GLUA3; GLUA2; }               // *   qqqqq   *\n
#define GLU(X,ST) {\
  int L;\
  STRL ST1,ST2; \
  sprintf(ST1,"Gluk in file \"%s\", line %d, function \"%s\": [%d]", \
    __FILE__,__LINE__,__FUNCTION__,(X));          \
  sprintf(ST2,"Code of exit: %s",strerror(errno)); \
  L=AMAX(strlen(ST1),strlen(ST2))+8; \
  GLUA2;\
  GLUA4(L); \
  GLUA5(L); \
  GLUA6(L,ST1); \
  GLUA6(L,ST2); \
  GLUA5(L);\
  GLUA6(L,ST); \
  GLUA5(L);\
  GLUA4(L); \
  GLUA2; }

#ifdef qwer
#define GLU(X,ST) {                                                        \
  fprintf(stderr,"\n**********************************************\n");    \
  fprintf(stderr,"*\n");                                                   \
  fprintf(stderr,"* Gluk in file %s, line %d",__FILE__,__LINE__);          \
  fprintf(stderr,", function \"%s\"",__FUNCTION__);                        \
  fprintf(stderr,": [%d]\n",(X));                                          \
  fprintf(stderr,"* "); perror("Code of exit");                            \
  fprintf(stderr,"*\n");                                                   \
  fprintf(stderr,"* %s\n",ST);                                             \
  fprintf(stderr,"*\n");                                                   \
  fprintf(stderr,"**********************************************\n\n");    \
  /*exit(BAD);*/ }
#endif

#define GLUR(X) { GLU(X,"return");      return; }
#define GLUB(X) { GLU(X,"return BAD");  return BAD; }
#define GLUN(X) { GLU(X,"return NULL"); return NULL; }
#define GLUE(X) { GLU(X,"exit(BAD)");   exit(BAD); }
#define GLUK(X) ( GLUE(X) ) // old style

#define coreleft()    0L
#define farcoreleft() 0L

#define CORELEFT printf("%12s [%3d]: left=%6lu, farleft=%6lu\n", \
  __FILE__,__LINE__,(ULI)coreleft(),(ULI)farcoreleft())

#define CALLOC(SIZE,STRU) { \
  CORELEFT; \
  printf("need %lu bytes of memory\n",(ULI)(SIZE)*sizeof(STRU)); \
  printf("need  memory for %lu STRU\n",(ULI)SIZE); \
  printf("exist memory for %lu STRU (far)\n",farcoreleft()/sizeof(STRU));\
  printf("exist memory for %lu STRU\n",coreleft()/sizeof(STRU)); \
  printf("recommend: decrease SIZE1 on %lu\n", \
    1+((ULI)(SIZE)*sizeof(STRU)-coreleft())/sizeof(uni)); \
  GLUR(666); }

/****************************************************************************
*                                                                           *
*   MACROS FOR bit string BITSTR                                            *
*                                                                           *
****************************************************************************/
#define FPBITSTR(X) { int I; \
  fprintf(stdout,"              76543210\n"); \
  for (I=0; I<SIZE_LEN0; I++) { \
    FPCHAR((X)[I]); fprintf(stdout," %d\n",I*8); } }

#define IFBITSTR(X,N)    ( ((N)>=SIZE_LEN0*8) ? beep() :                   \
  IFBIT((X)[(N)/8],(N)%8) )

#define SETBITSTR(X,N)    ( ((N)>=SIZE_LEN0*8) ? beep() :                  \
  SETBIT((X)[(N)/8],(N)%8) )

#define UNSETBITSTR(X,N)  ( ((N)>=SIZE_LEN0*8) ? beep() :                  \
  UNSETBIT((X)[(N)/8],(N)%8) )

#define TOGGLEBITSTR(X,N) ( ((N)>=SIZE_LEN0*8) ? beep() :                  \
  TOGGLEBIT((X)[(N)/8],(N)%8) )

/****************************************************************************
*                                                                           *
*   MACROS FOR COLORS                                                       *
*                                                                           *
****************************************************************************/
/*   To get 16-bit color from 8-bit R,G,B                                  */
#define RGB16(R,G,B) (                                                     \
  ((int)(31.0*((int)(R) & 0xff)/255) << 11) | \
  ((int)(63.0*((int)(G) & 0xff)/255) << 5 ) | \
   (int)(31.0*((int)(B) & 0xff)/255) )
/*   To get 16-bit color from 0xRRGGBB                                     */
#define RGB_16(X) RGB16( \
  ((X) & 0xFF0000) >> 16, \
  ((X) & 0x00FF00) >> 8, \
  (X) & 0xFF )

/*   To get 8-bit red from 16-bit color                                    */
#define GET_RED(X)   ( (((int)(X) & 0xf800) >> 11)*255/31 )

/*   To get 8-bit green from 16-bit color                                  */
#define GET_GREEN(X) ( (((int)(X) & 0x7e0 ) >> 5 )*255/63 )

/*   To get 8-bit blue from 16-bit color                                   */
#define GET_BLUE(X)  (  ((int)(X) & 0x1f  )       *255/31 )

/*   Color converter: to shift to definite color                           */
#define COLCON(C1,C2,A) { \
  int RGB[3]={ GET_RED(C1),GET_GREEN(C1),GET_BLUE(C1) }, \
      HSB[3]; \
  colorconvert(RGB2HSB,RGB,HSB); \
  A; \
  colorconvert(HSB2RGB,HSB,RGB); \
  (C2)=RGB16(RGB[0],RGB[1],RGB[2]); }
#define COLCONBLUE(C1,C2) COLCON(C1,C2,HSB[0]=0.5*(240+HSB[0])) /* blue */
#define COLCONRED(C1,C2)  COLCON(C1,C2,HSB[0]=0.5*(0  +HSB[0])) /* blue */

/****************************************************************************
*                                                                           *
*   MACROS FOR PPV                                                          *
*                                                                           *
****************************************************************************/
#ifdef OC2K1x
  #define OC2K_THREAD ( { \
    if (tuneXEnvironment(NULL,NULL,NULL)) { \
      fprintf(stderr,"Error:tuneXEnvironment().\n"); \
      return 0; \
    } \
    if (oc2kOClibsAccessInit(X11_MASK,0)) { \
      fprintf(stderr,"Error:oc2kOClibsAccessInit(X11_MASK,0),failed.\n"); \
      return NULL; \
    } \
  } )
#else
   #define OC2k_THREAD ;
#endif

/*   Regim checking                                                        */
#ifndef ALEX
  #define CRREGIM  ( (UCHAR)(*workPtr->ourReg) )
  /*   profilactics */
  #define CRPROF   ( checReg == chBit(workPtr->ourReg,checReg,1) )
#else
  /*   autonomic profilactics */
  #define CRREGIM   12
  #define CRPROF    TRUE
#endif

/****************************************************************************
*                                                                           *
*   MACROS FOR WORK                                                         *
*                                                                           *
****************************************************************************/
#define E2EV(E)       ( (E)/EE )  /* energy in electronvolts eV            */
#define M2AEM(M)      ( (M)/AEM ) /* mass in AEM                           */
#define IONSPEED(E,M) sqrt(2*(E)/(M))

/*   Debay function: if X>4000*M_LN10=9210 -> GLUK                         */
#define DEBAY(X) ( ((X)>4000*M_LN10) ? -1 : ( ((X)<NOL) ? 1 :             \
  (X)/(exp(X)-1) ))

/*   DT = debay temperature                                                */
#define SIGMA0(M,DT)         sqrt( 3*SQR(HH) / (4*(M)*KK*(DT)) )
#define SIGMA(M,DT,T)        ( (T<NOL) ? SIGMA0(M,DT) :                   \
  2*SIGMA0(M,DT)*sqrt(sqr((T)/(DT))*DebayIntegral(DT,T)+0.25) )

/*   Consider cfg *cq always, and Q - vector to change                     */
#define SKP2SKV(Q) mulvec3mat3(Q,cq->skp2skv)
#define SKV2SKP(Q) mulvec3mat3(Q,cq->skv2skp)
#define SKF2SKP(Q) mulvec3mat3(Q,cq->skf2skp)
#define SKV2SKC(Q) mulvec3mat3(Q,cq->skv2skc)
#define SKC2SKV(Q) mulvec3mat3(Q,cq->skc2skv)

/*   Find litera coords in SKC: cfg *cq, L=litera, C=cage                  */
#define CG0(L,C)  sumvec3(cq->amas[(L)].skc,C)
/*   FindUGlobal: cq=cfg*                                                  */
#define UG0(L,C)  SKC2SKV(CG0(L,C))
/*   UG0 of current uni *u)                                                */
#define UGU0      UG0(u->litera,u->cage)
/*   UG0 of cfg *cq                                                        */
#define UGQ0      UG0(cq->litera,cq->cage)
/*   UG0 of collis *c                                                      */
#define UGC0      UG0(c->litera,c->cage)

/*   All these with check                                                  */
#define CG(L,C)   ( (cq->amas[(L)].n==NULL) ? bad_vec3 : CG0(L,C) )
#define UG(L,C)   SKC2SKV(CG(L,C))
#define UGU       UG(u->litera,u->cage)
#define UGQ       UG(cq->litera,cq->cage)
#define UGC       UG(c->litera,c->cage)

/*   For shortness: STRL ST == char ST[SIZE_LEN2]                          */
#define FGETS fgets(st,SIZE_LEN2,f)

/*   Check, if coords (in SKV) are inside of sample                        */
#define RINSAMPLE(Q)  qinpa(SKV2SKP(Q),cq->sample)
/*   Check, if coords (in SKV) are inside of sample with pmax in edges     */
#define RINSAMPLEP(Q) qinpa(SKV2SKP(Q),cq->samplep)
/***************************************************************************/
#endif /* MACRO_H                                                          */

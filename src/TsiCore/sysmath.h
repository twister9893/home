#ifndef _SYSMATH_H_
#define _SYSMATH_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!\defgroup SysMath Математические процедуры
  \{
*/

#define EQ3(a,b) (fabs(a-b)<0.001)
#define ZERO3(a) (fabs(a)<0.001)
#define MIN(a,b) ((a<=b)?a:b)
#define MAX(a,b) ((a>=b)?a:b)

//! Перевод из градусов в радианы
/*!
	\param[in] x Угол, градусы
	\returns Угол, радианы
*/
inline double rad(double x) {return x*M_PI/180.0;}

//! Перевод из радианов в градусы
/*!
	\param[in] x Угол, радианы
	\returns Угол, градусы
*/
inline double grad(double x) {return x*180.0/M_PI;}

//! Перевод из т.д. в градусы
/*!
	\param[in] x Угол, т.д.
	\returns Угол, градусы
*/
inline double td2grad(double x) {return x*360.0/6000.0;}

//! Перевод из градусов в т.д.
/*!
	\param[in] x Угол, градусы
	\returns Угол, т.д.
*/
inline double grad2td(double x) {return x*6000.0/360.0;}


//! Перевод скорости из м/с в узлы
/*!
	\param[in] mc Скорость, м/с
	\returns Скорость, узлы
*/
inline double mc2uz (double mc) {return mc*1.943855;}

//! Перевод скорости из узлов в м/с
/*!
	\param[in] uz Скорость, узлы
	\returns Скорость, м/с
*/
inline double uz2mc (double uz) {return uz/1.943855;}

//! Перевод дальности из километров в мили
/*!
	\param[in] km Дальность, километры
	\returns Дальность, мили
*/
inline double km2ml (double km) {return km*0.539957;}

//! Перевод дальности из миль в километры
/*!
	\param[in] ml Дальность, мили
	\returns Дальность, километры
*/
inline double ml2km (double ml) {return ml/0.539957;}

inline double m2foot (double m) {return(m/0.3048);}
inline double m2yard (double m) {return(m/0.9144);}
inline double foot2m (double foot) {return(foot*0.3048);}
inline double yard2m (double yard) {return(yard*0.9144);}

int CFLXY(double f0, double l0, double f, double l, double *x, double *y,int mercator=0);
int CXYFL(double f0, double l0, double x, double y, double *f, double *l,int mercator=0);

//! Перевод пеленга и дальности в координаты X и Y
/*!
	\param[in] p Пеленг, градусы
	\param[in] d Дальность, километры
	\param[out] x Координата X, километры
	\param[out] y Координата Y, километры

	Можно указатель на часть выходных данных передать равным нулю, тогда эта составляющая считаться не будет.
*/
inline void pdinxy(double p,double  d, double *x,double *y ) {if(x) *x=d*sin(rad(p));if(y) *y=d*cos(rad(p));}

//! Перевод координат X и Y в пеленг и дальность
/*!
	\param[in] x Координата X, километры
	\param[in] y Координата Y, километры
	\param[out] p Пеленг, градусы
	\param[out] d Дальность, километры

	Можно указатель на часть выходных данных передать равным нулю, тогда эта составляющая считаться не будет.
*/
inline void xyinpd(double x, double y, double *p, double *d) {if(d) *d = sqrt(x*x+y*y);if(p) {*p=(x||y)?grad(atan2(x,y)):0;if(*p<0) *p+=360;};}

#define sign(a) (((a)>=0)?1:-1)

//! Процедура расчета параметров кратчайшего сближения цели и своего корабля
/*!
	\param[in] Xc Координата X цели, километры
	\param[in] Yc Координата Y цели, километры
	\param[in] Vxc Составляющая по X вектора скорости цели, м/с
	\param[in] Vyc Составляющая по Y вектора скорости цели, м/с
	\param[in] Vxsk Составляющая по X вектора скорости своего корабля, м/с
	\param[in] Vysk Составляющая по Y вектора скорости своего корабля, м/с
	\param[out] Dkr Дистанция кратчайшего сближения, километры
	\param[out] Tkr Относительное время кратчайшего сближения, секунды

	Можно указатель на часть выходных данных передать равным нулю, тогда эта составляющая считаться не будет.
*/
void DkrTkr(double Xc, double Yc, double Vxc, double Vyc,double Vxsk, double Vysk,double* Dkr,double* Tkr);

//! Процедура дистанции и времени пересечения целью линии курса своего корабля
/*!
	\param[in] Xc Координата X цели, километры
	\param[in] Yc Координата Y цели, километры
	\param[in] Vxc Составляющая по X вектора скорости цели, м/с
	\param[in] Vyc Составляющая по Y вектора скорости цели, м/с
	\param[in] Vxsk Составляющая по X вектора скорости своего корабля, м/с
	\param[in] Vysk Составляющая по Y вектора скорости своего корабля, м/с
	\param[out] Dper Дистанция пересечения, километры
	\param[out] Tper Относительное время пересечения, секунды

	\return Наличие пересечения (0 - нет пересечения, 1 - есть пересечение)

	Можно указатель на часть выходных данных передать равным нулю, тогда эта составляющая считаться не будет.
*/
int DperTper(double Xc, double Yc, double Vxc, double Vyc,double Vxsk, double Vysk,double* Dper,double* Tper);


//! Процедура расчета координат точек пересечения окружности и луча
int KTPOL(double X0,double Y0,double P,double Xc,double Yc,double R,double* pX1,double* pY1,double* pX2,double* pY2);


//! Процедура формирования области запрещенных маневров (курсов)
/*!
	\param[in] Rb Радиус безопасности, километры
	\param[in] Vm Скорость маневра, м/с
	\param[in] Pc Пеленг цели, градусы
	\param[in] Dc Дальность цели, километры
	\param[in] Vxc Составляющая по X скорости цели, м/с
	\param[in] Vyc Составляющая по Y скорости цели, м/с
	\param[out] ZParr Указатель на массив из 360 элементов типа char.

	Результатом выполнения процедуры является заполненный массив ZParr.
	Каждый элемент массива представляет собой курс от 0 до 359 градусов.
	При этом
	- Значение 1 говорит о недопустимости движения данным курсом при заданных радиусе безопасности и скорости.
	- Значение 0 говорит возможности движения данным курсом.
*/
void FDZM(double Rb,double Vm,double Pc,double Dc,double Vxc,double Vyc,char* ZParr);

//! Процедура расчета времени уклонения
/*!
	\param[in] Rb Радиус безопасности, километры
	\param[in] Vxsk Составляющая по X вектора скорости возврата, м/с
	\param[in] Vysk Составляющая по Y вектора скорости возврата, м/с
	\param[in] Vxm Составляющая по X вектора скорости маневра, м/с
	\param[in] Vym Составляющая по Y вектора скорости маневра, м/с
	\param[in] Xc Координата X цели, километры
	\param[in] Yc Координата Y цели, километры
	\param[in] Vxc Составляющая по X скорости цели, м/с
	\param[in] Vyc Составляющая по Y скорости цели, м/с

	\return Время уклонения (нахождения на курсе маневра), секунды
*/
double Tukl(double Rb,double Vxsk,double Vysk,double Vxm,double Vym,double Xc, double Yc, double Vxc, double Vyc);

//! Процедура расчета экстраполированных параметров местоположения цели
/*!
	\param[in] Xc Координата X цели, километры
	\param[in] Yc Координата Y цели, километры
	\param[in] Vxc Составляющая по X вектора скорости цели, м/с
	\param[in] Vyc Составляющая по Y вектора скорости цели, м/с
	\param[in] Vxsk Составляющая по X вектора скорости своего корабля, м/с
	\param[in] Vysk Составляющая по Y вектора скорости своего корабля, м/с
	\param[in] Textr Относительное время экстраполяции, секунды
	\param[out] Xextr Экстраполированная координата X цели, километры
	\param[out] Yextr Экстраполированная координата Y цели, километры

	Можно указатель на часть выходных данных передать равным нулю, тогда эта составляющая считаться не будет.
*/
void Extr(double Xc,double Yc,double Vxc,double Vyc,double Vxsk,double Vysk,double Textr,double* Xextr,double* Yextr);


//! Процедура расчета функции потерь при маневре
/*!
	\param[in] Ksk Курс своего корабля, градусы
	\param[in] Vsk Скорость своего корабля, м/с
	\param[in] Km Курс маневра, градусы
	\param[in] Vm Скорость маневра, м/с
	\param[in] Tm Относительное время маневра, секунды

	\return Значение функции потерь, метры
*/
inline double Fpot(double Ksk,double Vsk,double Km,double Vm,double Tm) {return Tm*(Vsk-Vm*cos(rad(Ksk-Km)));}

//! Процедура расчета параметров маневра для сближения с подвижной целью на заданную дистанцию с заданной скоростью
/*!
	\param[in] Xc Координата X цели, километры
	\param[in] Yc Координата Y цели, километры
	\param[in] Vxc Составляющая по X вектора скорости цели, м/с
	\param[in] Vyc Составляющая по Y вектора скорости цели, м/с
	\param[in] Dz Заданная дистанция, километры
	\param[in] Vz Заданная скорость маневра, м/с
	\param[out] T Время маневра, секунды
	\param[out] K Курс маневра, градусы

	\return Возможность сближения. Возвращает 0, если сближение на заданную дистанцию с заданной скоростью невозможно.

	- Для сближения вплотную задайте Dz=0
	- Dz не должна быть больше текущего расстояния до цели. В этом случае надо осознанно использовать процедуру удаления на Dz
*/
int sblDzVz(double Xc,double Yc,double Vxc,double Vyc,double Dz,double Vz,double* T,double* K);

//! Процедура перевода пеленга в курсовой угол
/*!
	\param[in] Ksk Курс своего корабля, градусы
	\param[in] P Пеленг, градусы

	\return Курсовой угол, градусы
*/
inline double P2Kugol(double Ksk,double P) {return -grad( acos(cos(rad(Ksk-P))) * sign(sin(rad(Ksk-P))) );}

//! Процедура перевода курсового угла в пеленг
/*!
	\param[in] Ksk Курс своего корабля, градусы
	\param[in] Kugol Курсовой угол, градусы

	\return Пеленг, градусы
*/
inline double Kugol2P(double Ksk,double Kugol) {double res=Ksk+Kugol;if(res<0) return 360+res;if(res>=360) return res-360;return res;}

//! Процедура проверки вхождения пеленга/курсового угла в сектор
/*!
	\param[in] p1 Пеленг/курсовой угол левой границы сектора, градусы
	\param[in] p2 Пеленг/курсовой угол правой границы сектора, градусы
	\param[in] pc Проверяемый пеленг/курсовой угол, градусы

	\return Возвращает 1 если проверяемый пеленг/курсовой угол входит в сектор

	\attention
	- Процедура работает как с пеленгами, так и с курсовыми углами, но все входные параметры должны
	быть одинаковыми - все параметры как пеленг или все параметры как курсовые углы.
	- Сектор должен задаваться <b>по часовой</b> стрелке
*/
inline int isInSector(double p1,double p2,double pc) {double s1c=sin(rad(p1-pc)),s12=sin(rad(p1-p2)),s2c=sin(rad(p2-pc));return (s1c<=0 && (s12>0 || s2c>=0)) || (s12>=0 && s2c>=0);}

//! Процедура проверки вхождения пеленга/курсового угла в сектор (более быстрый вариант)
/*!
	\param[in] p1 Пеленг/курсовой угол левой границы сектора, градусы
	\param[in] p2 Пеленг/курсовой угол правой границы сектора, градусы
	\param[in] pc Проверяемый пеленг/курсовой угол, градусы

	\return Возвращает 1 если проверяемый пеленг/курсовой угол входит в сектор

	\attention
	- Процедура работает как с пеленгами, так и с курсовыми углами, но все входные параметры должны
	быть одинаковыми - все параметры как пеленг или все параметры как курсовые углы.
	- Сектор должен задаваться <b>по часовой</b> стрелке
	- Вариант имеет следующее ограничение: если границы сектора заданы как 0-360, то проверяемый пеленг нельзя
	давать отрицательным
*/
inline int isInSectorFast(double p1,double p2,double pc) {if(p1<p2) return (pc<p2)&&(pc>p1); else return (pc>p1)||(pc<p2);}

inline unsigned int val2mas(double val,int countR,double CSR,double CMR=0)
{
	if(CMR) return val/CMR;
	double cmr=CSR/(unsigned int)(1<<(countR-1));
	return (int)(val/cmr);
}

inline double mas2val(unsigned int val,int countR,double CSR,double CMR=0)
{
	if(CMR) return val*CMR;
	double cmr=CSR/(unsigned int)(1<<(countR-1));
	return val*cmr;
}

inline double mas2valSigned(int val,int countR,double CSR,double CMR=0)
{
	double cmr=CMR?CMR:CSR/(unsigned int)(1<<(countR-1));
	unsigned int mask=(countR<32)?~((1<<countR)-1):0;
	if((val & (1<<(countR-1))))
		val=mask | val;
	return val*cmr;
}

inline double m2km(double m) {return m/1000.0;}
inline double km2m(double km) {return km*1000.0;}

//! Процедура чтения данных из NMEA формуляр
/*!
	\param[in] str строка по протоколу NMEA
	\param[in] needComma номер запятой, после которой необходимо записать данные
	\param[in] rval буфер
	\param[in] symbolNumber номер символа относительно запятой <b>needComma</b> (начиная с 0), начиная с которого необходимо считать данные
	\param[in] symbolCount размер читаемых данных (в символах)

	\attention
	Если поле в NMEA обрамлено запятыми, то параметры <b>symbolCount</b> и <b>symbolNumber</b> не имеют смысла и их следует оставить нулевыми,
	тогда данные будут считаны строго между запятыми.
*/
char* getNmeaValue(char* str,int needComma,char* rval, int symbolNumber = 0, int symbolCount = 0);

//! Процедура записи данных в NMEA формуляр
/*!
	\param[in] str строка по протоколу NMEA
	\param[in] needComma номер запятой, после которой необходимо записать данные
	\param[in] val записываемые данные
	\param[in] symbolNumber номер символа относительно запятой <b>needComma</b> (начиная с 0), начиная с которого необходимо записать данные
	\param[in] symbolCount размер записываемых данных (в символах)

	\attention
	Если поле в NMEA обрамлено запятыми, то параметры <b>symbolCount</b> и <b>symbolNumber</b> не имеют смысла и их следует оставить нулевыми,
	тогда данные будут записываться строго между запятыми.
*/
void setNmeaValue(char* str,int needComma,char* val, int symbolNumber = 0, int symbolCount = 0);

inline double getNmeaFloat(char* str,int needComma, int symbolNumber = 0, int symbolCount = 0)
{
	char valueStr[256];
	return atof(getNmeaValue(str,needComma,valueStr,symbolNumber,symbolCount));
}

inline int getNmeaInt(char* str,int needComma, int symbolNumber = 0, int symbolCount = 0)
{
	char valueStr[256];
	return atoi(getNmeaValue(str,needComma,valueStr,symbolNumber,symbolCount));
}

inline int getNmeaOrdinal(char* str,int needComma,const char* values)
{
	char valueStr[256];
	getNmeaValue(str,needComma,valueStr);
	for(int i=0;values[i];i++)
		if(values[i]==valueStr[0])
			return i;
	return -1;
}

inline void setNmeaFloat(char* str,int needComma,double val, int symbolNumber = 0, int symbolCount = 0)
{
	char valueStr[256];
	sprintf(valueStr,"%.2f",val);
	setNmeaValue(str,needComma,valueStr);
}

inline void setNmeaFloat4(char* str,int needComma,double val, int symbolNumber = 0, int symbolCount = 0)
{
	char valueStr[256];
	sprintf(valueStr,"%.4f",val);
	setNmeaValue(str,needComma,valueStr);
}

inline void setNmeaInt(char* str,int needComma,int val, int symbolNumber = 0, int symbolCount = 0)
{
	char valueStr[256];
	sprintf(valueStr,"%d",val);
	setNmeaValue(str,needComma,valueStr);
}

inline void setNmeaOrdinal(char* str,int needComma,const char* values,int val)
{
	char valueStr[256];
	if(val>=0 && val<(int)strlen(values))
	{
		valueStr[0]=values[val];
		valueStr[1]=0;
		setNmeaValue(str,needComma,valueStr);
	}
}

//! Процедура расчета параметров маневра для сближения с подвижной целью с заданного пеленга на заданную дистанцию с заданной скоростью
/*!
	\param[in] Xc Координата X цели, километры
	\param[in] Yc Координата Y цели, километры
	\param[in] Vxc Составляющая по X вектора скорости цели, м/с
	\param[in] Vyc Составляющая по Y вектора скорости цели, м/с
	\param[in] Dz Заданная дистанция, километры
	\param[in] Vz Заданная скорость маневра, м/с
	\param[in] Pz Заданный пеленг, градусы
	\param[out] T Время маневра, секунды
	\param[out] K Курс маневра, градусы

	\return Возможность сближения. Возвращает 0, если сближение на заданную дистанцию с заданной скоростью невозможно.

	- Для сближения вплотную задайте Dz=0
	- Dz не должна быть больше текущего расстояния до цели. В этом случае надо осознанно использовать процедуру удаления на Dz
*/
int sblDzVzPz(double Xc,double Yc,double Vxc,double Vyc,double Dz,double Vz,double Pz,double* T,double* K);


//! Процедура расчета параметров маневра для сближения с подвижной целью на заданную дистанцию за заданное время
/*!
	\param[in] Xc Координата X цели, километры
	\param[in] Yc Координата Y цели, километры
	\param[in] Vxc Составляющая по X вектора скорости цели, м/с
	\param[in] Vyc Составляющая по Y вектора скорости цели, м/с
	\param[in] Dz Заданная дистанция, километры
	\param[in] Vmax Предельная скорость маневра, секунды
	\param[in] Tz Заданное время маневра, секунды
	\param[out] K Курс маневра, градусы
	\param[out] V Скорость маневра, м/с

	\return Возможность сближения. Возвращает 0, если сближение на заданную дистанцию за заданное время невозможно.

	- Для сближения вплотную задайте Dz=0
	- Dz не должна быть больше текущего расстояния до цели. В этом случае надо осознанно использовать процедуру удаления на Dz
*/
int sblDzTz(double Xc, double Yc, double Vxc, double Vyc, double Dz, double Vmax, double Tz, double* K, double* V);

//! Процедура расчета параметров маневра для сближения с подвижной целью с заданного пеленга на заданную дистанцию за заданное время
/*!
	\param[in] Xc Координата X цели, километры
	\param[in] Yc Координата Y цели, километры
	\param[in] Vxc Составляющая по X вектора скорости цели, м/с
	\param[in] Vyc Составляющая по Y вектора скорости цели, м/с
	\param[in] Dz Заданная дистанция, километры
	\param[in] Vmax Предельная скорость маневра, м/с
	\param[in] Tz Заданное время маневра, секунды
	\param[in] Pz Заданный пеленг, градусы
	\param[out] K Курс маневра, градусы
	\param[out] V Скорость маневра, м/с

	\return Возможность сближения. Возвращает 0, если сближение с заданного пеленга на заданную дистанцию за заданное время невозможно.

	- Для сближения вплотную задайте Dz=0
	- Dz не должна быть больше текущего расстояния до цели. В этом случае надо осознанно использовать процедуру удаления на Dz
*/
int sblDzTzPz(double Xc, double Yc, double Vxc, double Vyc, double Dz, double Vmax, double Tz, double Pz, double* K, double* V);

//! Процедура выработки признака стороны расхождения
/*!
	\param[in] Xc Координата X цели, километры
	\param[in] Yc Координата Y цели, километры
	\param[in] Vxc Составляющая по X вектора скорости цели, м/с
	\param[in] Vyc Составляющая по Y вектора скорости цели, м/с
	\param[in] Vxsk Составляющая по X вектора скорости СК, м/с
	\param[in] Vysk Составляющая по Y вектора скорости СК, м/с
	\param[in] aa Граница сектора выработки признака "Нос" (по умолчанию 11.25), градусы
	\param[in] bb Правая граница сектора выработки признака "Праваый борт" (по умолчанию 157.5), градусы

	\return Признак стороны расхождения. Возвращает: 0 - "Нос"; 1 - "Правый борт"; 2 - "Левый борт"; 3 - "Корма"
*/
int boardMove(double Xc, double Yc, double Vxc, double Vyc,double Vxsk, double Vysk, double aa = 11.25, double bb = 157.5);

//! Процедура расчета параметров сближения с объектом маневра при заданной скорости с учетом динамических характеристик управляемого объекта
/*!
	\param[in] F Широта начальной точки (местоположение своего корабля), град
	\param[in] L Долгота начальной точки (местоположение своего корабля), град
	\param[in] Xn Координата X начала маневра, километры
	\param[in] Yn Координата Y начала маневра, километры
	\param[in] Kn Текущий курс движения цели, градусы
	\param[in] Vn Начальная скорость маневра, м/с
	\param[in] Vk Заданная скорость маневра, м/с
	\param[in] a Ускорение разгона/торможения, м/с2
	\param[in] Km1 Курс маневра без учета циркуляции, градусы
	\param[in] Rc Радиус циркуляции, м
	\param[in] tm1 Расчитанное время маневра без учета циркуляции, сек
	\param[in] Xc Координата X цели, километры
	\param[in] Yc Координата Y цели, километры
	\param[in] Kc Курс цели, градусы
	\param[in] Vc Скорость цели, м/с
	
	\param[out] Kk Курс маневра сближения с учетом циркуляции, град
	\param[out] tm Время маневра сближения с учетом циркуляции, сек
	\param[out] Fn Географические координаты точки начала циркуляции, град
	\param[out] Ln Географические координаты точки начала циркуляции, град
	\param[out] Fk Географические координаты точки окончания циркуляции, град
	\param[out] Lk Географические координаты точки окончания циркуляции, град
	\param[out] Fv Географические координаты точки окончания маневра, град
	\param[out] Lv Географические координаты точки окончания маневра, град
	\param[out] Fc Географические координаты центра циркуляции, град
	\param[out] Lc Географические координаты центра циркуляции, град
	\param[out] tc Время циркуляции, сек
	\param[out] tpt Время разгона/торможения, сек
	
	\return Возможность сближения. Возвращает 0, если сближение невозможно.
*/
int dynamicVz(double F, double L, double Xn, double Yn, double Kn, double Vn, double Vk, double a, double Km1, double Rc, double tm1, double Xc, double Yc, double Kc, double Vc,
			  double* Kk, double* tm, double* Fn, double* Ln, double* Fk, double* Lk, double* Fv, double* Lv, double* Fc, double* Lc, double* tc, double* tpt);


//! Процедура расчета параметров сближения с объектом маневра на заданную дистанцию с учетом динамических характеристик управляемого объекта
/*!
	\param[in] F Широта начальной точки (местоположение своего корабля), град
	\param[in] L Долгота начальной точки (местоположение своего корабля), град
	\param[in] Xn Координата X начала маневра, километры
	\param[in] Yn Координата Y начала маневра, километры
	\param[in] Kn Текущий курс движения цели, градусы
	\param[in] Vn Начальная скорость маневра, м/с
	\param[in] Vk Заданная скорость маневра, м/с
	\param[in] a Ускорение разгона/торможения, м/с2
	\param[in] Dz Заданная дистанция сближения, километры
	\param[in] Rc Радиус циркуляции, м
	\param[in] Xc Координата X цели, километры
	\param[in] Yc Координата Y цели, километры
	\param[in] Kc Курс цели, градусы
	\param[in] Vc Скорость цели, м/с
	
	\param[out] Kk Курс маневра сближения с учетом циркуляции, град
	\param[out] tm Время маневра сближения с учетом циркуляции, сек
	\param[out] Fn Географические координаты точки начала циркуляции, град
	\param[out] Ln Географические координаты точки начала циркуляции, град
	\param[out] Fk Географические координаты точки окончания циркуляции, град
	\param[out] Lk Географические координаты точки окончания циркуляции, град
	\param[out] Fv Географические координаты точки окончания маневра, град
	\param[out] Lv Географические координаты точки окончания маневра, град
	\param[out] Fc Географические координаты центра циркуляции, град
	\param[out] Lc Географические координаты центра циркуляции, град
	\param[out] tc Время циркуляции, сек
	\param[out] tpt Время разгона/торможения, сек
	
	\return Возможность сближения. Возвращает 0, если сближение невозможно.
*/
int dynamicDz(double F, double L, double Xn, double Yn, double Kn, double Vn, double Vk, double a, double Dz, double Rc, double Xc, double Yc, double Kc, double Vc,
			  double* Kk, double* tm, double* Fn, double* Ln, double* Fk, double* Lk, double* Fv, double* Lv, double* Fc, double* Lc, double* tc, double* tpt);


//! Процедура расчета параметров сближения с объектом маневра за заданное время с учетом динамических характеристик управляемого объекта
/*!
	\param[in] F Широта начальной точки (местоположение своего корабля), град
	\param[in] L Долгота начальной точки (местоположение своего корабля), град
	\param[in] Xn Координата X начала маневра, километры
	\param[in] Yn Координата Y начала маневра, километры
	\param[in] Kn Текущий курс движения цели, градусы
	\param[in] Vn Начальная скорость маневра, м/с
	\param[in] Vk Заданная скорость маневра, м/с
	\param[in] a Ускорение разгона/торможения, м/с2
	\param[in] Tz Заданное время сближения, сек
	\param[in] Dz Заданная дистанция сближения, километры
	\param[in] Rc Радиус циркуляции, м
	\param[in] Xc Координата X цели, километры
	\param[in] Yc Координата Y цели, километры
	\param[in] Kc Курс цели, градусы
	\param[in] Vc Скорость цели, м/с
	
	\param[out] Kk Курс маневра сближения с учетом циркуляции, град
	\param[out] tm Время маневра сближения с учетом циркуляции, сек
	\param[out] Fn Географические координаты точки начала циркуляции, град
	\param[out] Ln Географические координаты точки начала циркуляции, град
	\param[out] Fk Географические координаты точки окончания циркуляции, град
	\param[out] Lk Географические координаты точки окончания циркуляции, град
	\param[out] Fv Географические координаты точки окончания маневра, град
	\param[out] Lv Географические координаты точки окончания маневра, град
	\param[out] Fc Географические координаты центра циркуляции, град
	\param[out] Lc Географические координаты центра циркуляции, град
	\param[out] tc Время циркуляции, сек
	\param[out] tpt Время разгона/торможения, сек
	
	\return Возможность сближения. Возвращает 0, если сближение невозможно.
*/
int dynamicDzTz(double F, double L, double Xn, double Yn, double Kn, double Vn, double Vmax, double a, float Tz, double Dz, double Rc, double Xc, double Yc, double Kc, double Vc,
		  double* Fn, double* Ln, double* Fk, double* Lk, double* Fv, double* Lv, double* Fc, double* Lc, double* Kk, double* Vk, double* tm, double* tc, double* tpt);


int dynamicDzTz2(double F, double L, double Xn, double Yn, double Kn, double Vn, double Vmax, double a, float Tz, double Dz, double Rc, double Xc, double Yc, double Kc, double Vc,
		  double* Fn, double* Ln, double* Fk, double* Lk, double* Fv, double* Lv, double* Fc, double* Lc, double* Kk, double* Vk, double* tm, double* tc, double* tpt);







// Венгерский алгоритм.
// Даниил Швед, 2008. danshved [no-spam] gmail.com
// Реализация навеяна псевдокодом А.С.Лопатина из книги
// "Оптимизация на графах (алгоритмы и реализация)".
#include <vector>
#include <limits>
//using namespace std;

typedef std::pair<int, int> PInt;
typedef std::vector<int> VInt;
typedef std::vector<VInt> VVInt;
typedef std::vector<PInt> VPInt;

const int hungarianMax = std::numeric_limits<int>::max();

//! Процедура решения задачи о назначениях Венгерским методом.
/*!
	\param[in] matrix Прямоугольная матрица из целых чисел (не обязательно положительных).

	\return Список пар назначений

	\attention Высота матрицы не должна быть больше ширины. Алгоритм работает только с целыми числами.
*/
VPInt hungarian(const VVInt &matrix);

//! Процедура расчета точки прямолинейного галса
/*!
    \param[in] Fs Широта начальной точки, градусы
    \param[in] Ls Долгота начальной точки, градусы
    \param[in] K0 Курс в начальной точке, градусы
    \param[in] V0 Скорость в начальной точке, м/с
    \param[in] V1 Скорость в конечной точке, м/с
    \param[in] T Время движения, с
    \param[in] t Врямя в искомой точке, с
    \param[in] a Значение ускорения на галсе. Задается без знака, м/с^2
    \param[out] Fm Широта искомой точки, градусы
    \param[out] Lm Долгота искомой точки, градусы
    \param[out] Vm Скорость в искомой точке, м/с
    
    \return Код ошибки: 1 - успех
                        -1 - Некорректное время галса
                        -2 - Некорректное текущее время
*/
int galsPoint(double Fs, double Ls, double K0, double V0, double V1, float T, float t, float a, double *Fm, double *Lm, double *Vm);

//! Процедура расчета точки криволинейного галса
/*!
    \param[in] Fs Широта начальной точки, градусы
    \param[in] Ls Долгота начальной точки, градусы
    \param[in] K0 Курс в начальной точке, градусы
    \param[in] V0 Скорость в начальной точке, м/с
    \param[in] V1 Скорость в конечной точке, м/с
    \param[in] T Время движения, с
    \param[in] t Врямя в искомой точке, с
    \param[in] a Значение ускорения на галсе. Задается без знака, м/с^2
    \param[in] rotate Направление поворота, -1 левый, 1 правый
    \param[in] R Радиус поворота, километры
    \param[out] Fc Широта центра поворота, градусы
    \param[out] Lc Долгота центра поворота, градусы
    \param[out] Fm Широта искомой точки, градусы
    \param[out] Lm Долгота искомой точки, градусы
    \param[out] Km Курс в искомой точке, градусы
    \param[out] Vm Скорость в искомой точке, м/с
        
    \return Код ошибки: 1 - успех
                        -1 - Некорректное время галса
                        -2 - Некорректное текущее время
*/
int galsPoint(double Fs, double Ls, double K0, double V0, double V1, float T, float t, float a, int rotate, double R, double *Fc, double *Lc, double *Fm, double *Lm, double *Km, double *Vm);

//! Решение квадратного уравнения
/*!
	\param[in] A старший коэффициент
	\param[in] B средний коэффициент
	\param[in] C свободный член
	\param[out] X1 первый корень 
	\param[out] X2 второй корень
	\return Количество вещественных корней [0-2]
*/
int squareSolution(double A, double B, double C, double* X1, double* X2);


//! Процедура выработки параметров дуги циркуляции
/*!
	\param[in] Kn Начальный курс, град
	\param[in] Kk Конечный курс, град
	\param[in] Xpt Координата X смены курса, км
	\param[in] Ypt Координата Y смены курса, км
	\param[in] Rc Радиус циркуляции, км
	
	\param[out] Xc Координата X центра окружности, км
	\param[out] Yc Координата Y центра окружности, км
	\param[out] Xn Координата X начала циркуляции, км
	\param[out] Yn Координата Y начала циркуляции, км
	\param[out] Xn Координата X окончания циркуляции, км
	\param[out] Yn Координата Y окончания циркуляции, км
*/
int pdcmr(double Kn, double Kk, double Xpt, double Ypt, double Rc, double *Xc, double *Yc, double *Xn, double *Yn, double *Xk, double *Yk);


/* \} */
#endif


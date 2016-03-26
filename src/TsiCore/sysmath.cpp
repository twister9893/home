#include "sysmath.h"
#include <string.h>
#include <stdio.h>

#include "libCoord.h"

#define NOL 0.000001

//   If X almost equal to Y
#define EQZ(X,Y) ( fabs((X)-(Y))<NOL )

#define XZ(X)                  EQZ(X,0)

//! Модуль числа
#define ABS(X) ( ((X)<0)?-(X):(X) )

#define WGS

int CFLXY(double f0, double l0, double f, double l, double *x, double *y,int mercator)
{
	double P,D,X,Y;
	int res;

	if (!x || !y) return 0;

	(*x)=(*y)=0;
	if (EQZ(f0,f) && EQZ(l0,l)) return 1;

	if(mercator)
	{
#ifdef WGS
    res=WFLtoMXYr(f, l, f0, l0, &X, &Y);
#else
    res=KFLtoMXYr(f, l, f0, l0, &X, &Y);
#endif
	*x=Y/1000.0;
	*y=X/1000.0;
	}
	else
	{
#ifdef WGS
		res=WFLtoEllipseSA(f,l,f0,l0,&D,&P);
#else
		res=KFLtoEllipseSA(f,l,f0,l0,&D,&P);
#endif
		pdinxy(P,D/1000.0,x,y);
	}

	return res;
}

int CXYFL(double f0, double l0, double x, double y, double *f, double *l,int mercator)
{
	double P,D;
	int res;

	if (!f || !l) return 0;
	if (XZ(x) && XZ(y)) {
		*f=f0;
		*l=l0;
		return 1;
	}

	*f=*l=0;
	xyinpd(x,y,&P,&D);
#ifdef WGS
	res=EllipseSAtoWFL(D*1000.0,P,f0,l0,f,l);
#else
	res=EllipseSAtoKFL(D*1000.0,P,f0,l0,f,l);
#endif
	return res;
}

void DkrTkr(double Xc, double Yc, double Vxc, double Vyc,double Vxsk, double Vysk,double* Dkr,double* Tkr)
{
	double Wx=Vxsk-Vxc;
	double Wy=Vysk-Vyc;
	double W;
	xyinpd(Wx,Wy,0,&W);
	double A=Xc*1000*Wy-Yc*1000*Wx;
	double B=Xc*1000*Wx+Yc*1000*Wy;
	if(fabs(W)<0.001)
	{
		if(Dkr) xyinpd(Xc,Yc,0,Dkr);
		if(Tkr) *Tkr=0;
	}
	else
	{
		if(Dkr) *Dkr=fabs(A/W/1000);
		if(Tkr) *Tkr=B/(W*W);
	}
}

int DperTper(double Xc, double Yc, double Vxc, double Vyc,double Vxsk, double Vysk,double* Dper,double* Tper)
{
	double D=Vxc*Vysk-Vyc*Vxsk;
	if(fabs(D)<0.001) return 0;

	double t2=(Yc*1000*Vxsk-Xc*1000*Vysk)/D;
	if(t2<0.001) return 0;

	double t1=(Yc*1000*Vxc-Xc*1000*Vyc)/D;
	double Xsk=Vxsk*t2;
	double Ysk=Vysk*t2;
	double Xcv=Xc*1000+Vxc*t2;
	double Ycv=Yc*1000+Vyc*t2;

	if(Dper) *Dper=sign(t1)*sqrt((Xcv-Xsk)*(Xcv-Xsk)+(Ycv-Ysk)*(Ycv-Ysk))/1000.0;
	if(Tper) *Tper=t2;
	return 1;
}

int KTPOL(double X0,double Y0,double P,double Xc,double Yc,double R,double* pX1,double* pY1,double* pX2,double* pY2)
{
	double radP=rad(P);
	double Xn=X0-Xc;
	double Yn=Y0-Yc;
	double A=Xn*sin(radP)+Yn*cos(radP);
	double B=R*R-Xn*Xn-Yn*Yn;
	double C=A*A+B;
	double t1,t2;
	if(fabs(C)<0.000001) C=0;
	if(C<0)
		return 0;
	t1=-A-sqrt(C);
	t2=-A+sqrt(C);
	*pX1=X0+t1*sin(radP);
	*pY1=Y0+t1*cos(radP);
	*pX2=X0+t2*sin(radP);
	*pY2=Y0+t2*cos(radP);
	if(t2<0) return 0;
	if(t1<0 || C==0)
	{
		*pX1=*pX2;
		*pY1=*pY2;
		return 1;
	}
	return 2;
}

void FDZM(double Rb,double Vm,double Pc,double Dc,double Vxc,double Vyc,char* ZParr)
{
	double y;
	if(!ZParr) return;
	if(Rb<Dc)
		y=grad(asin(Rb/Dc));
	else //занято полностью
	{
		memset(ZParr,1,360);
		return;
	}

	int KR1,KR2;
	double X11,Y11,X12,Y12;
	double X21,Y21,X22,Y22;
	double f11,f12,f21,f22;

	KR1=KTPOL(Vxc,Vyc,Pc-y,0,0,Vm,&X11,&Y11,&X12,&Y12);
	KR2=KTPOL(Vxc,Vyc,Pc+y,0,0,Vm,&X21,&Y21,&X22,&Y22);

	// рис. 4
	if(KR1==2 && KR2==2)
	{
		xyinpd(X11,Y11,&f11,0);
		xyinpd(X21,Y21,&f21,0);
		xyinpd(X12,Y12,&f12,0);
		xyinpd(X22,Y22,&f22,0);
		if(f11<f21) f11+=360;
		for(int i=round(f21);i<=round(f11);i++)
			ZParr[i%360]=1;
		if(f22<f12) f22+=360;
		for(int i=round(f12);i<=round(f22);i++)
			ZParr[i%360]=1;
//		printf("%f - %f\n",f21,f11);
//		printf("%f - %f\n",f12,f22);
		return;
	}
	// рис. 2
	if(KR1==2)
	{
		xyinpd(X11,Y11,&f11,0);
		xyinpd(X12,Y12,&f12,0);
		if(f11<f12) f11+=360;
		for(int i=round(f12);i<=round(f11);i++)
			ZParr[i%360]=1;
		return;
	}
	// рис. 3
	if(KR2==2)
	{
		xyinpd(X21,Y21,&f21,0);
		xyinpd(X22,Y22,&f22,0);
		if(f22<f21) f22+=360;
		for(int i=round(f21);i<=round(f22);i++)
			ZParr[i%360]=1;
		return;
	}
	double Kc,Vc;
	xyinpd(Vxc,Vyc,&Kc,&Vc);
	// рис. 5
	if(KR1==1 && KR2==1 && Vc<=Vm)
	{
		xyinpd(X12,Y12,&f12,0);
		xyinpd(X22,Y22,&f22,0);
		if(f22<f12) f22+=360;
		for(int i=round(f12);i<=round(f22);i++)
			ZParr[i%360]=1;
//		printf("%f - %f\n",f12,f22);
		return;
	}
	// занято полностью
	if(sin(rad(Kc-Pc-y))*sin(rad(Kc-Pc+y))<0)
		memset(ZParr,1,360);
}

double Tukl(double Rb,double Vxsk,double Vysk,double Vxm,double Vym,double Xc, double Yc, double Vxc, double Vyc)
{
	const double Tmax=120*60;
	double ret;

	double W0x=Vxsk-Vxc;
	double W0y=Vysk-Vyc;
	double Wx=Vxm-Vxc;
	double Wy=Vym-Vyc;

	double W0;
	xyinpd(W0x,W0y,0,&W0);

	double L=Wy*W0x-Wx*W0y;
	double M=Yc*1000*W0x-Xc*1000*W0y;
	double N=M+W0*Rb*1000*sign(L);
	double P=L*Tmax;
	if(fabs(N)<=fabs(P))
		ret=N/L;
	else
		ret=Tmax;
	return ret;
}

void Extr(double Xc,double Yc,double Vxc,double Vyc,double Vxsk,double Vysk,double Textr,double* Xextr,double* Yextr)
{
	double Xe,Ye;
	Xe=Xc+(Vxc-Vxsk)*Textr/1000.0;
	Ye=Yc+(Vyc-Vysk)*Textr/1000.0;
	if(Xextr) *Xextr=Xe;
	if(Yextr) *Yextr=Ye;
}

int sblDzVz(double Xc,double Yc,double Vxc,double Vyc,double Dz,double Vz,double* T,double* K)
{
	double a,b,c,d,t=1000000,k;
	if(Vz==0 || Dz>sqrt(Xc*Xc+Yc*Yc)) return 0;
	a=Vxc*Vxc+Vyc*Vyc-Vz*Vz;
	b=-2*(Dz*Vz-Vxc*Xc-Vyc*Yc);
	c=Xc*Xc+Yc*Yc-Dz*Dz;
	
	if(fabs(a)<0.001)
	{
		if(fabs(b)<0.001) return 0;
		t=-c/b;
		if (t<=0.001) return 0;
	}
	else
	{
		double solt[2];
		d=b*b-4*a*c;
		if(d<0) return 0;
		solt[0]=-(b+sqrt(d))/(2*a);
		solt[1]=-(b-sqrt(d))/(2*a);
		if(solt[0]<0 && solt[1]<0) return 0;
		if(solt[0]>=0) t=solt[0];
		if(solt[1]>0 && (solt[0]<0 || solt[1]<t)) t=solt[1];
	}
	xyinpd(Vz*(t*Vxc+Xc)/(Dz+t*Vz),Vz*(t*Vyc+Yc)/(Dz+t*Vz),&k,0);
	if(K) *K=k;
	if(T) *T=t*1000;
	return 1;
}

char* getNmeaValue(char* str,int needComma,char* rval, int symbolNumber, int symbolCount)
{
	int curComma = 0, curSymbolOnComma = 0, fnd = 0, w = 0;
	for(int i = 0; str[i]; i++)
	{
		if(str[i] == ',')
		{
			curSymbolOnComma = i;
			curComma++;
			if(curComma == needComma)
				fnd = 1;
			else
				if(fnd)
					break;
		}
		else if(fnd)
				if((symbolCount && i > curSymbolOnComma + symbolNumber && i <= curSymbolOnComma + symbolNumber + symbolCount) || !symbolCount)
					rval[w++] = str[i];
	}
	if(!fnd)
		puts("ERROR: bad comma pos");
	rval[w] = 0;
	return rval;
}

void setNmeaValue(char* str,int needComma,char* val, int symbolNumber, int symbolCount)
{
	int curComma=0, fnd=0;
	char str2[strlen(str)+1];
	if (symbolCount != 0 && strlen(val) > symbolCount)
	{
		puts("ERROR: bad value, size out of range");
		return;
	}
	strcpy(str2, str);
	for(int i=0; str2[i]; i++)
	{
		if(str2[i]==',')
		{
			curComma++;
			if(curComma==needComma)
			{
				if (symbolNumber >= 0)
				{
					str[i+symbolNumber+1]=0;
					strcat(str,val);
				}
				else
				{
					str[i+1]=0;
					strcat(str,val);
				}
				fnd=1;
			}
			else if(fnd && symbolNumber < 0)
			{
				strcat(str, &str2[i]);
				break;
			}
		}
		if(fnd && symbolNumber >= 0)
		{
			strcat(str, &str2[i+symbolCount+symbolNumber+1]);
			break;
		}
	}
	if(!fnd) puts("ERROR: bad comma pos");
}


int sblDzVzPz(double Xc,double Yc,double Vxc,double Vyc,double Dz,double Vz,double Pz,double* T,double* K)
{
	double x,y;

	pdinxy(Pz, Dz, &x, &y);

	Xc += x;
	Yc += y;
	Dz = 0;

	return sblDzVz(Xc, Yc, Vxc, Vyc, Dz, Vz, T, K);
}

int sblDzTz(double Xc, double Yc, double Vxc, double Vyc, double Dz, double Vmax, double Tz, double* K, double* V)
{
	double Xv, Yv;
	double Dv, D;
	if (Tz<=0 || Dz>sqrt(Xc*Xc+Yc*Yc)) return 0;
	Xv = Xc*1000 + Vxc*Tz;
	Yv = Yc*1000 + Vyc*Tz;

	xyinpd(Xv/1000.0, Yv/1000.0, K, &Dv);

	D = Dv - Dz;
	if (D < 0) return 0;
	*V = (D*1000.0)/Tz;
	if (*V > Vmax) return 0;
	return 1;
}

int sblDzTzPz(double Xc, double Yc, double Vxc, double Vyc, double Dz, double Vmax, double Tz, double Pz, double* K, double* V)
{
	double x,y;

	pdinxy(Pz, Dz, &x, &y);

	Xc += x;
	Yc += y;
	Dz = 0;

	return sblDzTz(Xc, Yc, Vxc, Vyc, Dz, Vmax, Tz, K, V);
}


int boardMove(double Xc, double Yc, double Vxc, double Vyc,double Vxsk, double Vysk, double aa, double bb)
{
	double Wx = Vxc - Vxsk;
	double Wy = Vyc - Vysk;
	double X, Y;
	double Dk, Tk, Pk;
	double Q, K;

	DkrTkr(Xc, Yc, Vxc, Vyc, Vxsk, Vysk, &Dk, &Tk);

	X = Xc + Wx*Tk/1000.0;
	Y = Yc + Wy*Tk/1000.0;

	xyinpd(X, Y, &Pk, &Dk);

	xyinpd(Vxsk, Vysk, &K, &Dk);
	Q = P2Kugol(K, Pk);

	if (isInSector(-aa, aa, Q)) return 0;
	if (isInSector(aa, bb, Q)) return 1;
	if (isInSector(-bb, -aa, Q)) return 2;
	return 3;
}

int dynamicVz(double F, double L, double Xn, double Yn, double Kn, double Vn, double Vk, double a,  double Km1, double Rc, double tm1, double Xc, double Yc, double Kc, double Vc,
			  double* Kk, double* tm, double* Fn, double* Ln, double* Fk, double* Lk, double* Fv, double* Lv, double* Fc, double* Lc, double* tc, double* tpt)
{
	double dT = 1;
	double Km, Spt, tpr, Dm;
	double Vcx, Vcy, ga, da, dK; 
	double Xv, Yv, Xo, Yo, Xk_, Yk_, Xk, Yk;
	int ttt = 24*60*60;
	int side = 1;
	*tm = tm1;
	Km = Km1;

	a = a*sign(Vk - Vn);
	if (a != 0) *tpt = fabs(Vk - Vn)/fabs(a); else *tpt = 0;
	//Spt = Vn*(*tpt) + (fabs(a)*(*tpt)*(*tpt))/2;
	Spt = Vn*(*tpt) + (a*(*tpt)*(*tpt))/2;
//	printf("Spt = %0.2f tpt = %0.2f\n", Spt, *tpt);		
	
	pdinxy(Kc, Vc, &Vcx, &Vcy);
	int i = 0;
	side = sign(sin(rad(Km - Kn)));
	
	do
	{
		ttt = (int)fabs(*tm-tm1);
		tm1 = *tm;
//	printf("Km1 = %0.2f; tm1 = %0.2f a = %0.2f\n", Km1, tm1, a);
		
//		printf(" Xn = %0.2f Yn = %0.2f\n", Xn*1000.0, Yn*1000.0);
	
		Xv = Xc*1000 + Vcx*(*tm);
		Yv = Yc*1000 + Vcy*(*tm);
		Xo = Xn*1000 + side*Rc*cos(rad(Kn));
		Yo = Yn*1000 - side*Rc*sin(rad(Kn));
//		printf(" Xv = %0.2f Yv = %0.2f\n", Xv, Yv);
//		printf(" Xn = %0.2f Yn = %0.2f\n", Xn, Yn);
//		printf(" Xo = %0.2f Yo = %0.2f\n", Xo, Yo);
		
		xyinpd((Xo - Xv),(Yo - Yv), &ga, &da);
		/*
		Xk_ = side*((Rc*sqrt(da*da - Rc*Rc))/da);
		Yk_ = da - (Rc*Rc)/da;
		
		Xk = Xv + Xk_*cos(rad(ga))+Yk_*sin(rad(ga));
		Yk = Yv + Yk_*sin(rad(ga))+Yk_*cos(rad(ga));
		*/
//		printf("p = %0.2f; d = %0.2f\n", ga, da);
		if (da<=Rc)
		{
			return 0;
		}
		
		
//		printf("alfa = %0.2f\n", grad(asin(Rc/da)));

		pdinxy(ga+side*grad(asin(Rc/da)), sqrt(da*da-Rc*Rc), &Xk_, &Yk_);
		Xk = Xv+Xk_;
		Yk = Yv+Yk_;
		
//		printf(" Xk = %0.2f Yk = %0.2f\n", Xk, Yk);
		xyinpd((Xv - Xk), (Yv - Yk), &Km, &Dm);
	
		double _Cross = (Xn*1000.0-Xo)*(Yk-Yo)-(Yn*1000.0-Yo)*(Xk-Xo);
		double _Dot = (Xn*1000.0-Xo)*(Xk-Xo)+(Yn*1000.0-Yo)*(Yk-Yo);
		dK = (_Cross*side>0 )?(360.0-acos(_Dot/pow(Rc, 2))*180.0/M_PI):(acos(_Dot/pow(Rc, 2))*180.0/M_PI);	
//		dK = 180-grad(acos(-cos(rad(Km - Kn))));
		
//		printf("dK = %0.2f\n", dK);
		
		*Lc = (M_PI*Rc*fabs(dK))/180.0;
		
//		printf("Lc = %0.2f; Spt = %0.2f\n", *Lc, Spt);
//		printf(" Km = %0.2f Dm = %0.2f\n", Km, Dm);
		
		
		if (Spt < *Lc)
		{
			*tc = *tpt + (*Lc - Spt)/Vk;
			tpr = Dm/Vk;
			
			//tpr = (*tpt - *tc) + (Dm - (Spt - *Lc))/Vk;
		} else
		{
			if ((pow(Vn, 2) + 2*a*(*Lc)) < 0) return 0;
			
			*tc = (-Vn+sqrt(pow(Vn, 2)+2*a*(*Lc)))/a;//-Vn/a + sqrt((Vn*Vn)/(a*a)+2*(*Lc)/a);
			tpr = (Spt - (*Lc))/Vk + (Dm-(Spt-(*Lc)))/Vk;
			//*tc = Vn/fabs(a) + sqrt((Vn*Vn)/(fabs(a)*fabs(a)) + (2.0*(*Lc))/fabs(a));
			//tpr = Dm/Vk;
		}
		*tm = *tc + tpr;
//		printf("tm = %0.2f\n", *tm);
//		printf(" tc = %0.2f tpr = %0.2f\n", *tc, tpr);
//		printf(">>>>> %d - %0.2f < %0.2f; %d\n", i, dT, fabs(*tm-tm1), ttt);

		if (i && ttt < (int)fabs(*tm-tm1)) return 0;
		i++;
	} while (dT<=fabs(*tm-tm1) && i<5000/*Максимальное количество итераций*/);

//	printf("tm = %0.2f\n", *tm);
//	printf(" tc = %0.2f tpr = %0.2f\n", *tc, tpr);
//	printf(" Xv = %0.2f Yv = %0.2f\n", Xv, Yv);
//	printf(" Xn = %0.2f Yn = %0.2f\n", Xn*1000, Yn*1000);
//	printf(" Xo = %0.2f Yo = %0.2f\n", Xo, Yo);
//	printf(" Xk = %0.2f Yk = %0.2f\n", Xk, Yk);	

	*Kk = Km;
	CXYFL(F, L, Xn, Yn, Fn, Ln);
	CXYFL(F, L, Xk/1000.0, Yk/1000.0, Fk, Lk);
	CXYFL(F, L, Xv/1000.0, Yv/1000.0, Fv, Lv);
	CXYFL(F, L, Xo/1000.0, Yo/1000.0, Fc, Lc);
	return 1;
}


int dynamicDz(double F, double L, double Xn, double Yn, double Kn, double Vn, double Vk, double a, double Dz, double Rc, double Xc, double Yc, double Kc, double Vc,
			  double* Kk, double* tm, double* Fn, double* Ln, double* Fk, double* Lk, double* Fv, double* Lv, double* Fc, double* Lc, double* tc, double* tpt)
{

	double t = (Dz*1000.0)/Vk;
	double Vcx, Vcy, Spcx, Spcy;
	double T, K, Xk, Yk;
	double Dkr, Tkr;
	int result;
	
	
//	printf("Dz: %0.2f; Vk: %0.2f; t: %d\n", (int)t, Dz, Vk);
	
	
	pdinxy(Kc, Vc, &Vcx, &Vcy);
	
//	printf("1. Xc: %0.2f; Yc: %0.2f\n", Xc, Yc);
	
	Xc = Xc - Vcx*t/1000.0;
	Yc = Yc - Vcy*t/1000.0;
	
//	printf("2. Xc: %0.2f; Yc: %0.2f\n", Xc, Yc);
	
	result = sblDzVz(Xc, Yc, Vcx, Vcy, 0, Vk, &T, &K);
	
//	printf("1. res=%d\n", result);
	
	if (result == 0) return 0;
	
	result = dynamicVz(F, L, Xn, Yn, Kn, Vn, Vk, a, K, Rc, T, Xc, Yc, Kc, Vc,
						Kk, tm, Fn, Ln, Fk, Lk, Fv, Lv, Fc, Lc, tc, tpt);
	
//	printf("2. res=%d\n", result);
	if (result == 0) return 0;
//	pdinxy(Kn, Vk, &Spcx, &Spcy);
//	DkrTkr(Xc, Yc, Vcx, Vcy, Spcx, Spcy, &Dkr, &Tkr);

//	printf("Tm: %d; Tc: %d; t:%d\n", (int)*tm, (int)*tc, (int)t);
	
	*tm = *tm - t;
	CFLXY(F, L, *Fk, *Lk, &Xk, &Yk);
//	printf(" _Xk = %0.2f _Yk = %0.2f\n", Xk, Yk);		
	
	
	pdinxy(*Kk, Vk, &Vcx, &Vcy);
	Xk = Xk + Vcx*((*tm)-(*tc))/1000.0;
	Yk = Yk + Vcy*((*tm)-(*tc))/1000.0;
//	printf(" _Xv = %0.2f _Yv = %0.2f\n", Xk, Yk);			
	
	CXYFL(F,L, Xk, Yk, Fv, Lv);
	
	return 1;
}


int dynamicDzTz(double F, double L, double Xn, double Yn, double Kn, double Vn, double Vmax, double a, float Tz, double Dz, double Rc, double Xc, double Yc, double Kc, double Vc,
		  double* Fn, double* Ln, double* Fk, double* Lk, double* Fv, double* Lv, double* Fc, double* Lc, double* Kk, double* Vk, double* tm, double* tc, double* tpt)
{
	//Посчитаем параметры выхода без циркуляции
	int result = 0;
	double Vcx, Vcy;	//Составляющие сскорости цели
	double Km, Vm;		//Курс и скорость маневра без циркуляции
	pdinxy(Kc, Vc, &Vcx, &Vcy);
	result = sblDzTz(Xc, Yc, Vcx, Vcy, Dz, Vmax, Tz, &Km, &Vm);
//	printf("____ res1 = %d\n", result);
	if (result == 0) return 0;
	
	double dV = 0.1;	// Начальное значение дельта скорости
	double Tr = Tz;	// Промежуточное время сближения
	int i = 0;
	double _Vm;
	do
	{
		printf("____ Vm = %0.3f\n", Vm);
		result = dynamicDz(F, L, Xn, Yn, Kn, Vn, Vm, a, Dz, Rc, Xc, Yc, Kc, Vc,
			  Kk, tm, Fn, Ln, Fk, Lk, Fv, Lv, Fc, Lc, tc, tpt);
//		printf("____ res2 = %d\n", result);
		//if (result == 0) return 0;
		Tr = *tm;
		if (Tz>Tr && result == 1) 
		{
			if (dV>0) dV /=2;
			dV = -1*ABS(dV);
			Vm += dV;
			
			
		} else 
		{
			if (dV<0) dV /=2;			
			dV = ABS(dV);
			Vm +=dV;
		} 
		printf("___ %d ____ Tz = %.1f; Tr = %.1f; dT = %.1f\n", i, Tz, Tr, ABS(Tz-Tr));
		i++;
	} while (ABS(Tz-Tr)>1.0 && i<1000);
	if (result == 0) return 0;
	if (i == 1000) return 0;
	*Vk = Vm;
	return 1;
}


int dynamicDzTz2(double F, double L, double Xn, double Yn, double Kn, double Vn, double Vmax, double a, float Tz, double Dz, double Rc, double Xc, double Yc, double Kc, double Vc,
		  double* Fn, double* Ln, double* Fk, double* Lk, double* Fv, double* Lv, double* Fc, double* Lc, double* Kk, double* Vk, double* tm, double* tc, double* tpt)
{
	
	double Xt, Yt, Vcx, Vcy, T, K;
	int result = 0, dynRes = 0;
	pdinxy(Kc, Vc, &Vcx, &Vcy);
	Xt = Xc + Vcx*Tz/1000.0;
	Yt = Yc + Vcy*Tz/1000.0;

	result = sblDzVz(Xt, Yt , 0, 0, 0, Vmax, &T, &K);
	if (result == 0) return 0;

	
	dynRes = dynamicDz(F, L, Xn, Yn, Kn, Vn, Vmax, a, 0, Rc, Xt, Yt, 0, 0,
			Kk, tm, Fn, Ln, Fk, Lk, Fv, Lv, Fc, Lc, tc, tpt);
	if (dynRes == 0) return 0;
	
	double S, S1, S2;
	a = sign(Vmax-Vn)*a;
	S1 = Vn*(*tpt) + a*pow(*tpt, 2)/2;
	S2 = Vmax*((*tm) - (*tpt));
	S = S1 + S2;
	double x,y;
	int res = squareSolution(1, -2*(a*Tz+Vn), 2*a*S+pow(Vn, 2), &x, &y);
	if (res == 0) return 0;
	if (res == 1)
	{
		*Vk = x;
	}
	if (res == 2)
	{
		if (x*y<0 && x<0) *Vk = y;
		if (x*y<0 && y<0) *Vk = x;
		if (x*y>0 && x<y) *Vk = x;
		if (x*y>0 && x>y) *Vk = y;
	}
	printf("____ Vk = %.2f\n", *Vk);
	if (*Vk > Vmax) return 0;
	//-----------------------------
	double Xk, Yk, Xo, Yo, Xv, Yv;
	double Dm;
	CFLXY(F, L, *Fk, *Lk, &Xk, &Yk);
	CFLXY(F, L, *Fc, *Lc, &Xo, &Yo);
	CFLXY(F, L, *Fv, *Lv, &Xv, &Yv);
	
	double side = sign(sin(rad(K - Kn)));
	double _Cross = (Xn-Xo)*(Yk-Yo)-(Yn-Yo)*(Xk-Xo);
	double _Dot = (Xn-Xo)*(Xk-Xo)+(Yn-Yo)*(Yk-Yo);
	double dK = (_Cross*side>0 )?(360.0-acos(_Dot/pow(Rc/1000.0, 2))*180.0/M_PI):(acos(_Dot/pow(Rc/1000.0, 2))*180.0/M_PI);		
	double Lcc = (M_PI*Rc*fabs(dK))/180.0;

	*tpt = (*Vk - Vn)/a;
	xyinpd(Xv-Xk, Yv-Yk, 0, &Dm);
	double tpr;
	S1 = Vn*(*tpt) + a*pow(*tpt, 2)/2;
	if (S1 < Lcc)
		{
			*tc = *tpt + (Lcc - S1)/(*Vk);
			tpr = Dm*1000.0/(*Vk);
		} else
		{
			if ((pow(Vn, 2) + 2*a*Lcc) < 0) return 0;
			
			*tc = (-Vn+sqrt(pow(Vn, 2)+2*a*Lcc))/a;
			tpr = (S1 - Lcc)/(*Vk) + (Dm-(S1-Lcc))/(*Vk);
		}
		*tm = *tc + tpr;
	printf("____ tm = %.1f\n", *tm);	
	printf("____ tc = %.1f\n", *tc);	
	printf("____ tpt = %.1f\n", *tpt);	
		
	return 1;
}



VPInt hungarian(const VVInt &matrix) {

   // Размеры матрицы
   int height = matrix.size(), width = matrix[0].size();

   // Значения, вычитаемые из строк (u) и столбцов (v)
   VInt u(height, 0), v(width, 0);

   // Индекс помеченной клетки в каждом столбце
   VInt markIndices(width, -1);

   // Будем добавлять строки матрицы одну за другой
   for(int i = 0; i < height; i++) {
      VInt links(width, -1);
      VInt mins(width, hungarianMax);
      VInt visited(width, 0);

      // Разрешение коллизий (создание "чередующейся цепочки" из нулевых элементов)
      int markedI = i, markedJ = -1, j;
      while(markedI != -1) {
         // Обновим информацию о минимумах в посещенных строках непосещенных столбцов
         // Заодно поместим в j индекс непосещенного столбца с самым маленьким из них
         j = -1;
         for(int j1 = 0; j1 < width; j1++)
            if(!visited[j1]) {
               if(matrix[markedI][j1] - u[markedI] - v[j1] < mins[j1]) {
                  mins[j1] = matrix[markedI][j1] - u[markedI] - v[j1];
                  links[j1] = markedJ;
               }
               if(j==-1 || mins[j1] < mins[j])
                  j = j1;
            }

         // Теперь нас интересует элемент с индексами (markIndices[links[j]], j)
         // Произведем манипуляции со строками и столбцами так, чтобы он обнулился
         int delta = mins[j];
         for(int j1 = 0; j1 < width; j1++)
            if(visited[j1]) {
               u[markIndices[j1]] += delta;
               v[j1] -= delta;
            } else {
               mins[j1] -= delta;
            }
         u[i] += delta;

         // Если коллизия не разрешена - перейдем к следующей итерации
         visited[j] = 1;
         markedJ = j;
         markedI = markIndices[j];
      }

      // Пройдем по найденной чередующейся цепочке клеток, снимем отметки с
      // отмеченных клеток и поставим отметки на неотмеченные
      for(; links[j] != -1; j = links[j])
         markIndices[j] = markIndices[links[j]];
      markIndices[j] = i;
   }

   // Вернем результат в естественной форме
   VPInt result;
   for(int j = 0; j < width; j++)
      if(markIndices[j] != -1)
         result.push_back(PInt(markIndices[j], j));
   return result;
}

int galsPoint(double Fs, double Ls, double K0, double V0, double V1, float T, float t, float a, double *Fm, double *Lm, double *Vm)
{   
    if(T <= 0)
    {
        puts("sysmath.h galsPoint function ERROR: Negative or null gals time");
        return -1;
    }
//     if(t > T)
//     {
//         puts("Sysmath galsPoint function ERROR: Current time more than gals time");
//         return -2;
//     }
	if (t>T) t = T;
    
	if (ABS(V1-V0) < NOL)
    	{
		double lm = (V0*t) / 1000.0;
		double Xm = lm * sin(rad(K0));
		double Ym = lm * cos(rad(K0));
		CXYFL(Fs,Ls,Xm,Ym,Fm,Lm);
    
		if(Vm) *Vm = V0;
    
		return 1;
	} else
	{
		a = sign(V1-V0)*a;
		double _t = (V1-V0)/a;
		if (_t>t)
		{
			double lm = (V0*t + a*t*t/2) / 1000.0;
			double Xm = lm * sin(rad(K0));
			double Ym = lm * cos(rad(K0));
			CXYFL(Fs,Ls,Xm,Ym,Fm,Lm);
    
			if(Vm) *Vm = V0+a*t;
    
			return 1;
		}
		
		double S = V0*_t+a*_t*_t/2;
		double tr = t-_t;
		
		double lm = (V1*tr + S)/1000.0;
		double Xm = lm * sin(rad(K0));
		double Ym = lm * cos(rad(K0));
		CXYFL(Fs,Ls,Xm,Ym,Fm,Lm);
    
		if(Vm) *Vm = V1;
    
		return 1;		
	}
}

int galsPoint(double Fs, double Ls, double K0, double V0, double V1, float T, float t, float a, int rotate, double R, double *Fc, double *Lc, double *Fm, double *Lm, double *Km, double *Vm)
{
    if(T <= 0)
    {
        puts("Sysmath galsPoint function ERROR: Negative or null gals time");
        return -1;
    }
//     if(t > T)
//     {
//         puts("Sysmath galsPoint function ERROR: Current time more than gals time");
//         return -2;
//     }
	if (t>T) t = T;
    
    rotate=(rotate < 0)?-1:1;
    double Xc = rotate * R*cos(rad(K0));
    double Yc = -rotate * R*sin(rad(K0));
    CXYFL(Fs,Ls,Xc,Yc,Fc,Lc);
    
	if (ABS(V1-V0)<NOL)
	{
		double lm = (V0*t) / 1000;
		double fi = lm/R;
		double Xm = (-Xc)*cos(fi) + rotate*(-Yc)*sin(fi) + Xc;
		double Ym = -rotate*(-Xc)*sin(fi) + (-Yc)*cos(fi) + Yc;
		CXYFL(Fs,Ls,Xm,Ym,Fm,Lm);
    
		if(Km)
        {
            *Km = K0 + rotate*grad(fi);
            *Km += (*Km > 360)?-360:(*Km < 0)?360:0;
        }
		if(Vm) *Vm = V0;
//		printf("___1___fi=%.2f\n", grad(fi));
		return 1;	
	} else
	{
		a = sign(V1-V0)*a;
		double _t = (V1-V0)/a;	
		
//		printf("---- Tr = %.1f; t = %.1f; Tgals = %.1f\n", _t, t, T);
		
		if (_t>t)
		{
			double lm = (V0*t + a*t*t/2) / 1000;
			double fi = lm/R;
			double Xm = (-Xc)*cos(fi) + rotate*(-Yc)*sin(fi) + Xc;
			double Ym = -rotate*(-Xc)*sin(fi) + (-Yc)*cos(fi) + Yc;
			CXYFL(Fs,Ls,Xm,Ym,Fm,Lm);
    
			if(Km)
            {
                *Km = K0 + rotate*grad(fi);
                *Km += (*Km > 360)?-360:(*Km < 0)?360:0;
            }
			if(Vm) *Vm = a*t + V0;
//			printf("___2___fi=%.2f\n", grad(fi));
			return 1;
		}		

		double S = V0*_t+a*_t*_t/2;
		double tr = t-_t;
		double lm = (V1*tr + S)/1000.0;		

		double fi = lm/R;
		double Xm = (-Xc)*cos(fi) + rotate*(-Yc)*sin(fi) + Xc;
		double Ym = -rotate*(-Xc)*sin(fi) + (-Yc)*cos(fi) + Yc;
		CXYFL(Fs,Ls,Xm,Ym,Fm,Lm);
    
		if(Km)
        {
            *Km = K0 + rotate*grad(fi);
            *Km += (*Km > 360)?-360:(*Km < 0)?360:0;
        }
		if(Vm) *Vm = V1;
//		printf("___3___fi=%.2f\n", grad(fi));
		return 1;		
	}
}


int squareSolution(double A, double B, double C, double* X1, double* X2)
{
	if (A == 0)
	{
		*X1 = -C/B;
		return 1;
	} 
	
	double D = pow(B, 2) - 4*A*C;
	
	if (D<0) return 0;
	
	if (ABS(D)<NOL)
	{
		*X1 = -B/(2*A);
		return 1;
	}
	
	*X1 = (-B-sqrt(D))/(2*A);
	*X2 = (-B+sqrt(D))/(2*A);
	return 2;
}


int pdcmr(double Kn, double Kk, double Xpt, double Ypt, double Rc,
			double *Xc, double *Yc, double *Xn, double *Yn, double *Xk, double *Yk)
{
	*Xc = *Yc = *Xn = *Yn = *Xk = *Yk = 0.0;
	Kn = rad(Kn); Kk = rad(Kk);
	
	double signn = sign(sin(Kk-Kn));
	double dFi = 0.5*acos(-cos(Kk-Kn));
	double a = Kk + dFi*signn;
	double Y_c = Rc / sin(dFi);
	*Xc = Xpt + Y_c*sin(a); // X центр окружности
	*Yc = Ypt + Y_c*cos(a); // Y центр окружности
	
	double X_n = signn*(Rc*(cos(dFi)));
	double Y_n = Y_c - Rc*sin(dFi);
	*Xn = Xpt + X_n*cos(a) + Y_n*sin(a); // Х точка начала циркуляции
	*Yn = Ypt - X_n*sin(a) + Y_n*cos(a); // Y точка начала циркуляции
	
	double X_k = -X_n;
	double Y_k = Y_n;
	*Xk = Xpt + X_k*cos(a) + Y_k*sin(a); // X точка конца циркуляции
	*Yk = Ypt - X_k*sin(a) + Y_k*cos(a); // Y точка конца циркуляции
	
	return 1;
}

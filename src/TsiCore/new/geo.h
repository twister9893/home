#ifndef GEO
#define GEO

class Geo {
public:
    enum Projection {
        Gauss=0,
        Mercator
    };

    static bool FLtoXY(double f0, double l0, double f, double l, double *x, double *y, Projection projection=Gauss);
    static bool XYtoFL(double f0, double l0, double x, double y, double *f, double *l, Projection projection=Gauss);
    static bool XYtoPD(double x, double y, double *p, double *d);
    static bool PDtoXY(double p, double d, double *x, double *y);

private:
    Geo() {}
};

#endif // GEO


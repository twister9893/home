#include <QApplication>
#include <QPointer>

#include "tsicore.h"

#include "glgeoprimitive.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    TsiCore *core = new TsiCore();
    core->show();

    GeoPointArray points;
    points << GeoPoint(-20.0,-20.0,0.0, 54.0,19.0) << GeoPoint(0.0,20.0,0.0, 54.0,19.0) << GeoPoint(20.0,-20.0,0.0, 54.0,19.0);
    GlGeoPrimitive *gelem = new GlGeoPrimitive();
    gelem->setType(GL_TRIANGLES);
    gelem->setBrush(QBrush(Qt::red));
    gelem->setPoints(points);
    core->graphicsManager()->addGraphics(0,gelem);

    return a.exec();
}

//#include <QDebug>
#include <QCoreApplication>
#include <QMap>
#include <QDebug>
#include <thread>
//#include <QThread>
#include "glgraphicsengine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMap<int,TsiGraphics> graphics;
    TsiGraphics g;
    QVector<TsiPrimitive> primitives;
    QVector<QPointF> points;
    points << QPointF(0.0,0.0) << QPointF(0.5,0.5);
    TsiPrimitive line;
    line.setPoints(points);
    line.setColor(QColor(Qt::red));
    line.setWidth(3);

    primitives.append(line);

    g.setPrimitives(primitives);
    graphics.insert(1,g);
    //QThread *mainLoopThread = new QThread();
    //lGraphicsEngine::instance()->moveToThread(mainLoopThread);
    GlGraphicsEngine::instance()->setGraphicsSource(&graphics);
    GlGraphicsEngine *instance = GlGraphicsEngine::instance();
    //instance->run();
    std::thread thread(&GlGraphicsEngine::run, instance);
    //thread.detach();
    //QObject::connect(mainLoopThread, SIGNAL(started()), GlGraphicsEngine::instance(), SLOT(slot_run()));
    //QObject::connect(GlGraphicsEngine::instance(), SIGNAL(terminate()), mainLoopThread, SLOT(quit()));
    //QObject::connect(mainLoopThread, SIGNAL(terminated()), mainLoopThread, SLOT(deleteLater()));
    //mainLoopThread->start();
    qDebug() << "Stand by";
    return a.exec();
}

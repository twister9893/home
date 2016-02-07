#include <QCoreApplication>
#include <iostream>

#include "glgraphicsengine.h"
#include "glwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GlGraphicsEngine *engine = new GlGraphicsEngine();
    GlWindow *glWindow = new GlWindow(argc, argv);

    engine->painter()->begin(glWindow);
    engine->painter()->drawLine(0.0,0.0,100.0,100.0);
    engine->painter()->end();

    cout << "Hello" << endl;
    return a.exec();
}


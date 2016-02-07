#ifndef GLGRAPHICSENGINE_H
#define GLGRAPHICSENGINE_H

#include <QObject>
#include <singleton.h>
#include "../TsiCore/Interfaces/tsigraphicsengineinterface.h"
#include "../TsiCore/tsigraphics.h"

class GlGraphicsEngine : public QObject, public Singleton<GlGraphicsEngine>, public TsiGraphicsEngineInterface {
    //Q_OBJECT
public:
    void setGraphicsSource(QMap<int,TsiGraphics> *graphics) {m_graphics = graphics;}
    //void setObjectSource(QVector<TsiObject> *objects);

    void run() {}
    void kill() {}
    const char* getName() {return "";}
    TsiPluginInterface::Type getType() {return TsiPluginInterface::GraphicsEngine;}
    int getId() {return 0;}

protected:
    GlGraphicsEngine();

private:
    void initialize();
    void startMainLoop();

    static void drawGraphics(TsiGraphics graphics);
    //static void drawObject(TsiObject object);

    static void render();
    static void timerEvent(int value);
    static void keyboardEvent(unsigned char key, int x, int y);

    static GlGraphicsEngine *m_instance;
    static int m_fps;
    static int m_window;

    static QMap<int,TsiGraphics> *m_graphics;
   // static QVector<TsiObject> *m_objects;
};

#endif // GLGRAPHICSENGINE_H

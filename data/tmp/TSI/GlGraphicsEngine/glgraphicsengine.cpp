#include <QDebug>
#include <QThread>
#include <GL/glut.h>

#include "glgraphicsengine.h"

GlGraphicsEngine::GlGraphicsEngine() {
}

QMap<int,TsiGraphics> *GlGraphicsEngine::m_graphics = 0;
int GlGraphicsEngine::m_fps = 0;
int GlGraphicsEngine::m_window = 0;

void GlGraphicsEngine::run() {
    initialize();
    startMainLoop();
}

void GlGraphicsEngine::kill() {
    glutDestroyWindow(m_window);
    emit instance()->terminated();
    deleteLater();
}

void GlGraphicsEngine::initialize() {
    qDebug() << "[GlGraphicsEngine] Initialize...";
    int argc = 0;
    glutInit(&argc, 0);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(512, 512);
    m_window = glutCreateWindow("Hello");

    glClearColor(0.2,0.2,0.2,1.0);

    glutDisplayFunc(m_instance->render);
    glutIdleFunc(m_instance->render);

    glutTimerFunc(1000, m_instance->timerEvent, 0);
    glutKeyboardFunc(m_instance->keyboardEvent);
}

void GlGraphicsEngine::startMainLoop() {
    glutMainLoop();
}

void GlGraphicsEngine::timerEvent(int value) {
    qDebug() << "FPS:" << m_fps;
    m_fps = 0;
    glutTimerFunc(1000, m_instance->timerEvent, 0);
}

void GlGraphicsEngine::keyboardEvent(unsigned char key, int x, int y) {
    qDebug() << "KEY:" << key;
    switch(key) {
        case 27: {
            instance()->kill();
            break;
        }
        default: {
            break;
        }
    }
}

void GlGraphicsEngine::drawGraphics(TsiGraphics graphics) {
    for(int i=0; i < graphics.getPrimitives().size(); i++) {
        TsiPrimitive primitive = graphics.getPrimitives().at(i);
        glColor3d(primitive.getColor().red(), primitive.getColor().green(), primitive.getColor().blue());
        glLineWidth(primitive.getWidth());
        glPointSize(primitive.getWidth());

        glBegin(GL_LINE_STRIP);
        for(int i = 0; i < primitive.getPoints().size(); i++) {
            glVertex2f(primitive.getPoints().at(i).x(), primitive.getPoints().at(i).y());
        }
        glEnd();
    }
}

/*void GlGraphicsEngine::drawObject(TsiObject object) {

}*/

void GlGraphicsEngine::render() {
    //qDebug() << "Render...";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(QMap<int,TsiGraphics>::iterator i = m_graphics->begin(); i != m_graphics->end(); i++) {
        drawGraphics(i.value());
    }

    glutSwapBuffers();

    m_fps++;
}

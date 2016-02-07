#include <iostream>

#include "glengine.h"

using namespace std;

GLuint GlEngine::layers[1] = {0};

GlEngine::GlEngine(int argc, char *argv[]) {
    cout << "Engine init start" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(512, 512);
    //glutInitContextVersion(4, 3);
    //glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow(0);
    if (glewInit()) {
        cerr << "Unable to initialize GLEW ... exiting" << endl;
        exit(EXIT_FAILURE);
    }

    glutDisplayFunc(render);

    glutMainLoop();

    cout << "Engine init finish" << endl;
}

bool GlEngine::begin(QPaintDevice * pdev) {
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GlEngine::drawLines(const QLineF * lines, int lineCount) {
    glColor3f(0.5,0.0,0.0);

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, layers[0]);

    glBegin(GL_LINES);
        for(int i = 0; i < lineCount; i++) {
            glVertex2f(lines[i].x1(), lines[i].y1());
            glVertex2f(lines[i].x2(), lines[i].y2());
        }
    glEnd();

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void GlEngine::drawPixmap(const QRectF & r, const QPixmap & pm, const QRectF & sr) {

}

bool GlEngine::end() {

}

QPaintEngine::Type GlEngine::type() const {

}

void GlEngine::updateState(const QPaintEngineState & state) {

}

void GlEngine::createBuffers() {
    glGenFramebuffersEXT(1, layers);
}

void GlEngine::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, layers[0]);
    glDrawBuffer(GL_NONE);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

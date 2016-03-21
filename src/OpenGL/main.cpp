#include <QApplication>
#include <QDebug>

#include "glwindow.h"
//#include <GL/gl.h>
//#include <GL/glut.h>
//#include <GL/glew.h>
//#include <GL/glu.h>



/*void createBuffers() {

}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(-0.5,-0.5);

    glColor3f(0.0,1.0,0.0);
    glVertex2f(0.5,-0.5);

    glColor3f(0.0,0.0,1.0);
    glVertex2f(0.0,0.5);
    glEnd();

    glutSwapBuffers();
}
*/
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    GlWindow *window = new GlWindow();
    window->show();

    return a.exec();
}

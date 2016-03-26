//#include <QSvgRenderer>
#include <QWheelEvent>
#include <QDebug>
#include <qmath.h>
//#include <QGLShaderProgram>

#include "glwindow.h"

GlWindow::GlWindow (UpdateBehavior updateBehavior, QWindow *parent)
    : QOpenGLWindow(updateBehavior, parent) {
    scale=16.0;
    angle=0.0;
    mangle=0.0;
    posX=0.0;
    posY=0.0;
    m_mapFbo=0;

    setWidth(512);
    setHeight(512);
}

void GlWindow::resizeGL(int w, int h) {
//    qDebug() << "resize";
    m_screen.setWidth(w);
    m_screen.setHeight(h);
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2, w/2, -h/2, h/2, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GlWindow::paintGL() {
//    qDebug() << "render";

    if(!m_mapFbo)
    {
        m_mapFbo = new QOpenGLFramebufferObject(m_screen, QOpenGLFramebufferObject::NoAttachment, GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-m_windowSize.width()/2, m_windowSize.width()/2, -m_windowSize.height()/2, m_windowSize.height()/2, 1, -1);
//    glMatrixMode(GL_MODELVIEW);
//    glBegin(GL_TRIANGLES);
//    glColor3f(1.0,0.0,0.0);
//    glVertex2f((GLfloat)(-m_windowSize.width()/4),(GLfloat)(-m_windowSize.height()/4));

//    glColor3f(0.0,1.0,0.0);
//    glVertex2f((GLfloat)(m_windowSize.width()/4),(GLfloat)(-m_windowSize.height()/4));

//    glColor3f(0.0,0.0,1.0);
//    glVertex2f(0.0,(GLfloat)(m_windowSize.height()/4));
//    glEnd();

    m_mapFbo->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    glColor4d(0.0,0.0,1.0,0.5);
    glBegin(GL_TRIANGLES);
    glVertex2f((GLfloat)(-m_screen.width()/4),(GLfloat)(-m_screen.height()/4));

//    glColor4b(0,200,0,255);
    glVertex2f((GLfloat)(m_screen.width()/4),(GLfloat)(-m_screen.height()/4));

//    glColor4b(0,0,200,255);
    glVertex2f(0.0,(GLfloat)(m_screen.height()/4));
    glEnd();
    m_mapFbo->release();


    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,m_mapFbo->texture());

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(-m_screen.width()/4,-m_screen.height()/4,0);

    glTexCoord2f(1,0);
    glVertex3f(m_screen.width()/4,-m_screen.height()/4,0);

    glTexCoord2f(1,1);
    glVertex3f(m_screen.width()/4,m_screen.height()/4,0);

    glTexCoord2f(0,1);
    glVertex3f(-m_screen.width()/4,m_screen.height()/4,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void GlWindow::initializeGL() {
    glClearColor(0.2,0.2,0.2,1.0);
//    loadMap();
}

/*void GlWindow::paintEvent(QPaintEvent *event) {
    qDebug() << "paintEvent";

    QPainter painter;
    painter.begin(this);

    //painter.setBrush(QBrush(Qt::red));
    //painter.setPen(QPen(QColor(0,200,0)));
    //painter.drawEllipse(QPointF(50,50), 50, 50);
    painter.setTransform(m_globalTransform);
    QSvgRenderer svg;
    svg.load(QString("someIcon.svg"));
    svg.render(&painter);
    //QImage icon("someIcon.svg");
    //painter.drawImage(0,0,icon);

    painter.end();
}
*/
void GlWindow::mouseMoveEvent(QMouseEvent *event) {
    qDebug() << "mouseMoveEvent" << event->x() << event->y();
//    m_globalTransform.translate(event->x() - m_lastClick.x(), event->y() - m_lastClick.y());
//    m_lastClick.setX(event->x());
//    m_lastClick.setY(event->y());
//    repaint();
//    event->accept();
}

void GlWindow::mousePressEvent(QMouseEvent *event) {
//    m_lastClick.setX(event->x());
//    m_lastClick.setY(event->y());
//    event->accept();
    qDebug() << "x" << event->x() << "y" << event->y();
}

void GlWindow::wheelEvent(QWheelEvent * event) {
    qDebug() << "wheelEvent";
//    qreal factor = qPow(1.2, event->delta() / 240.0);
//    m_globalTransform.scale(factor, factor);
//    repaint();
    //    event->accept();
}

void GlWindow::timerEvent(QTimerEvent *e)
{

}

void GlWindow::loadMap()
{
    m_mapFbo = new QOpenGLFramebufferObject(m_screen, QOpenGLFramebufferObject::NoAttachment);
    qDebug() << "Fbo loaded";


//    GLubyte* pData=(GLubyte*)calloc(0,m_screen.width()*m_screen.height()*4);

//    glGenTextures(1,&m_mapTex);
//    glGenFramebuffers(1,&m_mapFbo);

//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D,m_mapTex);
//    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,m_screen.width(),m_screen.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,pData);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

//    glBindFramebuffer(GL_FRAMEBUFFER_EXT,m_mapFbo);
//    glFramebufferTexture2D(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_TEXTURE_2D, m_mapTex,0);

//    glBindFramebuffer(GL_FRAMEBUFFER_EXT,0);
//    glActiveTexture(GL_TEXTURE0);

//    free(pData);
}


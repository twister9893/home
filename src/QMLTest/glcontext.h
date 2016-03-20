#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include <QQuickItem>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QMenu>
#include <QDebug>

class SquircleRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    SquircleRenderer() : m_t(0), m_program(0) {}
    ~SquircleRenderer();

    void setT(qreal t) { m_t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }

public slots:
    void paint();

private:
    QSize m_viewportSize;
    qreal m_t;
    QOpenGLShaderProgram *m_program;
};

class Squircle : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)

public:
    Squircle();

    qreal t() const { return m_t; }
    void setT(qreal t);

signals:
    void tChanged();

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    qreal m_t;
    SquircleRenderer *m_renderer;
};

#endif // GLCONTEXT_H

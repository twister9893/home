#include "glwindow.h"

GlWindow::GlWindow(int argc, char *argv[]) {
    m_glEngine = new GlEngine(argc, argv);
}

QPaintEngine* GlWindow::paintEngine() const {
    return m_glEngine;
}

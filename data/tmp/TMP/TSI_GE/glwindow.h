#ifndef PAINTDEVICEOPENGL_H
#define PAINTDEVICEOPENGL_H

#include <QPaintDevice>

#include "glengine.h"

class GlWindow : public QPaintDevice {
public:
    GlWindow(int argc, char *argv[]);

    QPaintEngine* paintEngine() const;

private:
    GlEngine *m_glEngine;
};

#endif // PAINTDEVICEOPENGL_H

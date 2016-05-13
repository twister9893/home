#include "glwindow.h"

GlWindow::GlWindow()
    : core(new Core(this))
{
    core->addEllipse(0.0,0.0,100.0,100.0);
}


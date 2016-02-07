#ifndef TSIGRAPHICSENGINEOPENGL_H
#define TSIGRAPHICSENGINEOPENGL_H

//#include "../TSI/Interfaces/tsigraphicsengineinterface.h"
#include <QPainter>

class GlGraphicsEngine/* : public TsiGraphicsEngineInterface */{
public:
    GlGraphicsEngine();
    ~GlGraphicsEngine();

    QPainter* painter();

private:
    QPainter *m_painter;
};

#endif // TSIGRAPHICSENGINEOPENGL_H

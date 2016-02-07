#ifndef TSIGRAPHICSENGINEINTERFACE_H
#define TSIGRAPHICSENGINEINTERFACE_H

#include <QtGui/QPainter>

class TsiGraphicsEngineInterface/*: public TsiPluginBasicInterface*/ {
public:
    TsiGraphicsEngineInterface() {;}
    virtual ~TsiGraphicsEngineInterface() {;}

    virtual QPainter* painter();
};

Q_DECLARE_INTERFACE(TsiGraphicsEngineInterface, "ru.lan.TSI.TsiGraphicsEngineInterface/1.0")

#endif // TSIGRAPHICSENGINEINTERFACE_H

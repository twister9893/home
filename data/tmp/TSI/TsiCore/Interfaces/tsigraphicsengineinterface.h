#ifndef TSIGRAPHICSENGINEINTERFACE_H
#define TSIGRAPHICSENGINEINTERFACE_H

#include <QVector>
#include "tsiplugininterface.h"
#include "../tsigraphics.h"

class TsiGraphicsEngineInterface : public TsiPluginInterface {
public:
    virtual void setGraphicsSource(QMap<int,TsiGraphics> *graphics) = 0;
    //virtual void setObjectSource(QVector<TsiObject> *objects) = 0;

protected:
    TsiGraphicsEngineInterface();
    virtual ~TsiGraphicsEngineInterface();
};

//Q_DECLARE_INTERFACE(TsiGraphicsEngineInterface, "ru.lan.TSI.TsiGraphicsEngineInterface/1.0")

#endif // TSIGRAPHICSENGINEINTERFACE_H

#ifndef TSIPLUGININTERFACE_H
#define TSIPLUGININTERFACE_H

class TsiPluginInterface {
public:
    enum Type {
        DataBase=0,
        MapLoader,
        GraphicsEngine,
        Common
    };

    virtual void run() = 0;
    virtual void kill() = 0;
    virtual const char * getName() = 0;
    virtual Type getType() = 0;
    virtual int getId() = 0;

protected:
    TsiPluginInterface();
    virtual ~TsiPluginInterface();
};

#endif // TSIPLUGININTERFACE_H

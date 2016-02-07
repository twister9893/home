#ifndef TSIPLUGINLOADER_H
#define TSIPLUGINLOADER_H

#include <QString>

#include "Interfaces/tsiplugininterface.h"

class TsiPluginLoader {
public:
    TsiPluginLoader(QString fileName);
    TsiPluginInterface* getInstance() {return m_instance;}

private:
    void load(QString fileName);

    TsiPluginInterface *m_instance;
};

#endif // TSIPLUGINLOADER_H

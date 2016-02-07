#include <QDir>
#include <QPluginLoader>

#include "tsicore.h"

TsiCore::TsiCore() {
}

bool TsiCore::loadPlugins() {
    QDir pluginsDir = directoryOf("Plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        if (TsiDataBaseInterface *interface = qobject_cast<TsiDataBaseInterface*>(loader.instance()))
            m_dbPlugins.append(interface);
        if (TsiMapLoaderInterface *interface = qobject_cast<TsiMapLoaderInterface*>(loader.instance()))
            m_mlPlugins.append(interface);
        if (TsiGraphicsEngineInterface *interface = qobject_cast<TsiGraphicsEngineInterface*>(loader.instance()))
            m_gePlugins.append(interface);
    }
}

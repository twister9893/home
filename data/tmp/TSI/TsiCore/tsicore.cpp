#include <QDir>
//#include <QPluginLoader>
//#include <QThread>
#include <QDebug>
#include "tsipluginloader.h"
#include "tsicore.h"

TsiCore::TsiCore() {
    m_activeDataBasePlugin = -1;
    m_activeMapLoaderPlugin = -1;
    m_activeGraphicsEnginePlugin = -1;
    loadPlugins();
}

bool TsiCore::setActiveGraphicsEnginePlugin(int id) {
    if(m_plugins.contains(id)) {
        if(m_activeGraphicsEnginePlugin != -1) {
            m_plugins.value(m_activeGraphicsEnginePlugin)->kill();
            m_graphicsThread->join();
            delete m_graphicsThread;
        }
        m_activeGraphicsEnginePlugin = id;
        static_cast<TsiGraphicsEngineInterface*>(m_plugins.value(id))->setGraphicsSource(&graphics);
        m_graphicsThread = new std::thread(&TsiPluginInterface::run, m_plugins.value(id));
    }
}

bool TsiCore::loadPlugins() {
    QDir pluginsDir;
    pluginsDir.setPath("./Plugins");
    qDebug() << "[TsiCore] Load plugins...";
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        TsiPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        qDebug() << "\ttry" << fileName;
        int id = findFreePluginId();
        m_plugins.insert(id,loader.getInstance());
    }
}

int TsiCore::findFreePluginId() {
    int id = 0;
    while(m_plugins.contains(id)) {
        id++;
    }
    return id;
}

int TsiCore::findFreeGraphicsId() {
    int id = 0;
    while(m_graphics.contains(id)) {
        id++;
    }
    return id;
}

int TsiCore::addGraphics(TsiGraphics graphics) {
    int id = findFreeGraphicsId();
    m_graphics.insert(id, graphics);
}

#ifndef TSICORE_H
#define TSICORE_H

#include <QObject>

#include "Interfaces/tsidatabaseinterface.h"
#include "Interfaces/tsimaploaderinterface.h"
#include "Interfaces/tsigraphicsengineinterface.h"

class TsiCore : public QObject {
    Q_OBJECT
public:

//        class TsiObject {
//        public:
//            TsiObject();
//            virtual ~TsiObject() {}

//            void setId(int id) {m_id = id;}
//            void setName(QString name) {m_name = name;}
//            void setDescription(QString description) {m_description = description;}
//            void setType(Type type) {m_type = type;}

//            int id() {return m_id;}
//            QString name() {return m_name;}
//            QString description() {return m_description;}
//            Type type() {return m_type;}

//        private:
//            int m_id;
//            QString m_name;
//            QString m_description;
//            Type m_type;
//        };

    TsiCore();
    virtual ~TsiCore() {}

    bool runPlugin(int id);
    bool stopPlugin(int id);

    bool setActiveDataBasePlugin(int id);
    bool setActiveMapLoaderPlugin(int id);
    bool setActiveGraphicsEnginePlugin(int id);

    int activeDataBasePlugin();
    int activeMapLoaderPlugin();
    int activeGraphicsEnginePlugin();

    QMap<int,QString> dataBasePlugins();
    QMap<int,QString> mapLoaderPlugins();
    QMap<int,QString> graphicsEnginePlugins();
    QMap<int,QString> commonPlugins();

    int addObject(TsiObject object);
    int addGraphics(TsiGraphics graphics);

    bool removeObject(int id);
    bool removeGraphics(int id);

    bool editObject(int id, TsiObject object);
    bool editGraphics(int id, TsiGraphics graphics);

    TsiObject getObject(int id, bool *isOk);
    TsiGraphics getGraphics(int id, bool *isOk);

    QMap<int,TsiObject> getObjects();
    QMap<int,TsiGraphics> getGraphics();

protected:
    bool loadPlugins();

    QMap<int,TsiBasicInterface*> m_plugins;

    QList<int> m_dataBasePlugins;
    QList<int> m_mapLoaderPlugins;
    QList<int> m_graphicsEnginePlugins;
    QList<int> m_commonPlugins;

    int m_activeDataBasePlugin;
    int m_activeMapLoaderPlugin;
    int m_activeGraphicsEnginePlugin;

    QMap<int,TsiMap*> m_maps;
    QMap<int,TsiObject*> m_objects;
    QMap<int,TsiGraphics*> m_graphics;
};

#endif // TSICORE_H

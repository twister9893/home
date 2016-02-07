#include <stdio.h>
#ifndef WIN32
#include <dlfcn.h>
#else
#include <windows.h>
#endif

#include <QObject>

#include "tsipluginloader.h"

TsiPluginLoader::TsiPluginLoader(QString fileName) {
    load(fileName);
}

void TsiPluginLoader::load(QString fileName) {
    void * plugin;
    TsiPluginInterface* (*getInstanceFunction)(void);
 #ifndef WIN32
    plugin = dlopen(fileName.toStdString().c_str(), RTLD_LAZY);
 #else
    plugin = LoadLibrary(fileName.toStdString().c_str());
 #endif
    if (!plugin) {
      printf("[TsiPluginLoader] Can't open plugin '%s'\n", fileName.toStdString().c_str());
      return;
    }
 #ifndef WIN32
    getInstanceFunction = (TsiPluginInterface* (*)(void))dlsym(plugin, "getInstance");
 #else
    getInstanceFunction = (void (*)(void))GetProcAddress((HINSTANCE)plugin, "getInstance");
 #endif
    if (getInstanceFunction == NULL) {
      printf("[TsiPluginLoader] Can't load function 'getInstance'\n");
    } else {
      m_instance = getInstanceFunction();
    }
 /*#ifndef WIN32
    dlclose(plugin);
 #else
    FreeLibrary((HINSTANCE)plugin);
 #endif*/
}

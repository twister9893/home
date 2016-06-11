#include <QApplication>
#include "network_configurator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    NetworkConfigurator window;
    window.show();

    return app.exec();
}


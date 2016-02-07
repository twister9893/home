#include <QCoreApplication>
#include "tsicore.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TsiCore *core = new TsiCore();

    core->setActiveGraphicsEnginePlugin(0);

    return a.exec();
}

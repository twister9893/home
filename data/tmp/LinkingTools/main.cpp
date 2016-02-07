#include "linkingtools.h"
#include <QApplication>

QStringList g_fieldTypes;
QStringList g_fieldDimensions;
QStringList g_capacities;
QStringList g_formularHeaderSections;
QStringList g_enumerationHeaderSections;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LinkingTools w;
    w.show();

    return a.exec();
}

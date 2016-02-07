#include "formulareditor.h"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    FormularEditor w;
    w.show();

    return a.exec();
}

#include "formulareditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FormularEditor w;
    w.show();

    return a.exec();
}

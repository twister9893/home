#include <QApplication>
//#include <QDebug>

#include "glwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    GlWindow *window = new GlWindow();
    window->show();

    return a.exec();
}

#include <QApplication>
#include <QDebug>

#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Connection akva;
    akva.open("../data/mr-231.xml");

    akva.write(0,0);

//    qDebug() << "opened";

    return app.exec();
}


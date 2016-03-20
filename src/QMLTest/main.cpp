#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "glcontext.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Squircle>("OpenGLUnderQML", 1, 0, "Squircle");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

//int main(int argc, char **argv)
//{
//    QGuiApplication app(argc, argv);

//    qmlRegisterType<Squircle>("OpenGLUnderQML", 1, 0, "Squircle");

//    QQuickView view;
//    view.setResizeMode(QQuickView::SizeRootObjectToView);
//    view.setSource(QUrl("qrc:/main.qml"));
//    view.show();

//    return app.exec();
//}

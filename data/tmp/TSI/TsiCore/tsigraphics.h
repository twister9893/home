#ifndef TSIGRAPHICS_H
#define TSIGRAPHICS_H

#include <QVector>
#include "tsiprimitive.h"

class TsiGraphics {
public:
    TsiGraphics() {}

    void setName(QString name) {m_name = name;}
    void setPrimitives(QVector<TsiPrimitive> primitives) {m_primitives = primitives;}

    QString getName() {return m_name;}
    QVector<TsiPrimitive> & getPrimitives() {return m_primitives;}

private:
    QString m_name;
    QVector<TsiPrimitive> m_primitives;
};

#endif // TSIGRAPHICS_H

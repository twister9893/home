#include <QCoreApplication>
#include <QDebug>
#include "formular.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Formular *formular = new Formular();
    QMap<QString,FieldData*> fields;
    fields.insert("int1",new FieldData("int1","int11",FieldData::Integer,FieldData::Meters,4));
    fields.insert("int2",new FieldData("int2","int22",FieldData::Integer,FieldData::kMeters,4));
    fields.insert("int3",new FieldData("int3","int33",FieldData::Integer,FieldData::Degrees,8));
    formular->setFields(fields);

    char data[2] = {49,9};
    formular->setData(data);

    //qDebug() << "int1" << formular->

    return a.exec();
}


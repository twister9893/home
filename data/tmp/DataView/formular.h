#ifndef FORMULAR_H
#define FORMULAR_H

#include <QMap>
#include <QVariant>

#include "fielddata.h"

class Formular {
public:
    Formular();
    Formular(Formular &formular);

    void setName(QString name) {m_name = name;}
    void setFields(QMap<QString,FieldData*> fields);
    void setData(char *data);
    void setValue(QString fieldName, QVariant value);

    QString getName() {return m_name;}
    QMap<QString,FieldData*> & getFields();
    char * getData();
    int getSize() {return m_size;}
    QVariant getValue(QString fieldName);

private:
    int getFieldPosition(QString name);

    QString m_name;
    QMap<QString,FieldData*> m_fields;
    char *m_data;
    int m_size;
};

#endif // FORMULAR_H

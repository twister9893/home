#ifndef FORMULAR_H
#define FORMULAR_H

#include <QList>

#include "fielddata.h"

class Formular {
public:
    Formular();
    Formular(Formular &formular);

    QList<FieldData> & getFields();
    char * getData(int *size);
    QVariant getValue(QString fieldName);

    void setFields(QList<FieldData> fields);
    void setData(char *data, int size);
    void setValue(QString fieldName, QVariant value);

private:
    FieldData getFieldNamed(QString name);
    int getFieldPosition(FieldData field);

    QList<FieldData> m_fields;
    char *m_data;
    int m_size;
};

#endif // FORMULAR_H

#include "formular.h"

Formular::Formular()
    : m_data(0), m_size(0) {
}

Formular::Formular(Formular &formular) {
    m_data = formular.getData();
}

void Formular::setFields(QMap<QString, FieldData*> fields) {
    m_fields = fields;
    m_size = 0;
    for(QMap<QString,FieldData*>::iterator i = m_fields.begin(); i != m_fields.end(); i++) {
        m_size += i.value()->getSize();
    }
    m_size /= 8;
}

void Formular::setData(char *data) {
    if(m_data != 0) {
        free(m_data);
    }
    m_data = (char*)malloc(m_size);
    memcpy(data, m_data, m_size);
}

void Formular::setValue(QString fieldName, QVariant value) {

}

QMap<QString,FieldData*> & Formular::getFields() {
    return m_fields;
}

int Formular::getFieldPosition(QString name) {
    int position = 0;
    for(QMap<QString,FieldData*>::iterator i = m_fields.begin(); i != m_fields.find(name); i++) {
        position += i.value()->getSize();
    }
    return position;
}

char * Formular::getData() {
    char *data = (char*)malloc(m_size);
    memcpy(m_data, data, m_size);
    return data;
}

QVariant Formular::getValue(QString fieldName) {

    return QVariant();
}

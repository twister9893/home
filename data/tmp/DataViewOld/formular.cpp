#include "formular.h"

Formular::Formular()
    : m_data(0), m_size(0) {
}

QList<FieldData> & Formular::getFields() {
    return m_fields;
}

char * Formular::getData(int *size) {
    *size = m_size;
    char *data = (char*)malloc(m_size);
    memcpy(m_data, data, m_size);
    return data;
}

QVariant Formular::getValue(QString fieldName) {
    return QVariant();
}

void Formular::setFields(QList<FieldData> fields) {
    m_fields = fields;
    m_size = 0;
    for(int i = 0; i < m_fields.size(); i++) {
        m_size += m_fields.at(i).getSize();
    }
}

void Formular::setData(char *data, int size) {
    m_size = size;
    if(m_data != 0) {
        free(m_data);
    }
    m_data = (char*)malloc(m_size);
    memcpy(data, m_data, m_size);
}

void Formular::setValue(QString fieldName, QVariant value) {

}

FieldData Formular::getFieldNamed(QString name) {
    for(int i = 0; i < m_fields.size(); i++) {
        FieldData field = m_fields.at(i);
        if(field.getName() == name) {
            return field;
        }
    }
    return FieldData();
}

int Formular::getFieldPosition(FieldData field) {
    int position = 0;
    for(int i = 0; i < m_fields.indexOf(field); i++) {
        position += field.getSize();
    }
    return position;
}

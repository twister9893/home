#include <QVariant>
#include "dynamicformular.h"

DynamicFormular::DynamicFormular() {

}

DynamicFormular::DynamicFormular(DynamicFormular & dynamicFormular) {
    m_data = dynamicFormular.getData(&m_size);
}

void DynamicFormular::addFormular(Formular *formular, FormularLink *link) {
    m_formulars.insert(formular->getName(), formular);
    if(!link->getFormularName().isEmpty() && !link->getFieldName().isEmpty()) {
        m_links.insert(formular->getName(), link);
    }
}

void DynamicFormular::setData(char *data, int size) {
    m_size = size;
    if(m_data != 0) {
        free(m_data);
    }
    m_data = (char*)malloc(m_size);
    memcpy(data, m_data, m_size);
}

Formular * DynamicFormular::getFormular(QString name, uint number) {
    if(number < getFormularCount(name)) {
        char *data = (char*)malloc(m_formulars[name]->getSize());
        int shift = 0;
        for(QMap<QString,Formular*>::iterator i = m_formulars.begin(); i != m_formulars.end(); i++) {
            if(i.key() != name) {
                shift += i.value()->getSize();
            } else {
                shift += i.value()->getSize() * number;
                break;
            }
        }
        memcpy(data, m_data+shift, m_formulars[name]->getSize());
        m_formulars[name]->setData(data);
        return m_formulars[name];
    } else {
        return 0;
    }
}

char* DynamicFormular::getData(int *size) {
    *size = m_size;
    char *data = (char*)malloc(m_size);
    memcpy(m_data, data, m_size);
    return data;
}

int DynamicFormular::getFormularCount(QString name) {
    if(m_links.contains(name)) {
        Formular *linkedFormular = getFormular(m_links[name]->getFormularName(), 0);
        return linkedFormular->getValue(m_links[name]->getFieldName()).toInt();
    } else {
        return 1;
    }
}

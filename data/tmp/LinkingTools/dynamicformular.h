#ifndef DYNAMICFORMULAR_H
#define DYNAMICFORMULAR_H

#include <QMap>
#include "formular.h"

class DynamicFormular {
public:
    class FormularLink {
    public:
        FormularLink() {}
        FormularLink(QString formularName, QString fieldName)
            : m_formularName(formularName), m_fieldName(fieldName) {}

        void setFormularName(QString formularName) {m_formularName = formularName;}
        void setFieldName(QString fieldName) {m_fieldName = fieldName;}

        QString getFormularName() {return m_formularName;}
        QString getFieldName() {return m_fieldName;}

    private:
        QString m_formularName;
        QString m_fieldName;
    };

    DynamicFormular();
    DynamicFormular(DynamicFormular & dynamicFormular);
    void addFormular(Formular *formular, FormularLink *link = 0);
    void setData(char *data, int size);

    Formular * getFormular(QString name, uint number);
    char * getData(int *size);

private:
    int getFormularCount(QString name);

    QMap<QString,Formular*> m_formulars;
    QMap<QString,FormularLink*> m_links;
    char *m_data;
    int m_size;
};

#endif // DYNAMICFORMULAR_H

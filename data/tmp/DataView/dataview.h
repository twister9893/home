#ifndef DATAVIEW_H
#define DATAVIEW_H

#include "ui_dataview.h"
#include "formular.h"
#include "dynamicformular.h"

class DataView : public QMainWindow, private Ui::DataView {
    Q_OBJECT
public:
    explicit DataView(QWidget *parent = 0);

    int addFormular(Formular *formular);
    int addFormular(DynamicFormular *dynamicFormular);
    //void addFormular(Nmea *nmea);

private:
    void updateView();
    //void updateData();

    int m_freeId;
    QMap<int,Formular*> m_formulars;
    QMap<int,DynamicFormular*> m_dynamicFormulars;
};

#endif // DATAVIEW_H

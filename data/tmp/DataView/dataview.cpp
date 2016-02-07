#include "dataview.h"

DataView::DataView(QWidget *parent) :
    QMainWindow(parent), m_freeId(0) {
    setupUi(this);
}

int DataView::addFormular(Formular *formular) {
    m_formulars.insert(m_freeId, formular);
    return m_freeId++;
}

int DataView::addFormular(DynamicFormular *dynamicFormular) {
    m_dynamicFormulars.insert(m_freeId, dynamicFormular);
    return m_freeId++;
}

void updateView() {

}

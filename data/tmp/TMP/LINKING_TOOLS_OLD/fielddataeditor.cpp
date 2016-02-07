#include "fielddataeditor.h"

FieldDataEditor::FieldDataEditor(QWidget *parent)
    : QWidget(parent) {
    setupUi(this);
    extern QStringList g_fieldTypes;
    extern QStringList g_fieldDimensions;
    typeBox->insertItems(0, g_fieldTypes);
    dimensionBox->insertItems(0, g_fieldDimensions);
    typeBox->setDisabled(true);

    connect(okButton, SIGNAL(released()), this, SLOT(slot_requestAccept()));
    connect(cancelButton, SIGNAL(released()), this, SLOT(slot_requestReject()));
}

void FieldDataEditor::slot_requestAccept() {
    emit accept();
}

void FieldDataEditor::slot_requestReject() {
    emit reject();
}

void FieldDataEditor::closeEvent(QCloseEvent *event) {
    slot_requestReject();
    event->ignore();
}

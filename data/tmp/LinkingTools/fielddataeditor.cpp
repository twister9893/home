#include "fielddata.h"
#include "scalablewidget.h"
#include "enumerationwidget.h"
#include "constantwidget.h"

#include "fielddataeditor.h"

FieldDataEditor::FieldDataEditor(QWidget *parent)
    : QWidget(parent) {
    setupUi(this);
    typeBox->insertItems(0, FieldData::fieldTypes);
    dimensionBox->insertItems(0, FieldData::fieldDimensions);
    typeBox->setDisabled(true);

    connect(okButton, SIGNAL(released()), this, SIGNAL(accept()));
    connect(cancelButton, SIGNAL(released()), this, SIGNAL(reject()));
}

void FieldDataEditor::slot_constructEditor(int type) {
    switch(type) {
        case FieldData::Integer:
        case FieldData::Real:
        case FieldData::Boolean:
        case FieldData::String:
        case FieldData::Unused: {
            break;
        }
        case FieldData::Scalable: {
            fieldDataEditor->additionalLayout->addWidget(new ScalableWidget(fieldDataEditor));
            break;
        }
        case FieldData::Enumeration: {
            FieldEnumeration *fieldEnumeration = static_cast<FieldEnumeration*>(field);
            EnumerationWidget *enumerationEditor = new EnumerationWidget(fieldDataEditor);
            fieldDataEditor->additionalLayout->addWidget(enumerationEditor);
            connect(enumerationEditor->addButton, SIGNAL(released()), fieldEnumeration, SLOT(slot_addElement()));
            connect(enumerationEditor->removeButton, SIGNAL(released()), fieldEnumeration, SLOT(slot_removeLastElement()));
            break;
        }
        case FieldData::Constant: {
            fieldDataEditor->additionalLayout->addWidget(new ConstantWidget(fieldDataEditor));
            break;
        }
        default:
            break;
    }
}

void FieldDataEditor::closeEvent(QCloseEvent *event) {
    emit reject();
    event->ignore();
}

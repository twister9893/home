#include "formulardelegate.h"

FormularDelegate::FormularDelegate(QObject *parent) :
    QAbstractItemDelegate(parent) {
}

void FormularDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if(index.isValid()) {
        FieldData *field = (FieldData*)index.data(Qt::EditRole).toInt();
        switch(field->getType()) {
            case Integer: {
                painter->setPen(option.palette.text().color());
                break;
            }
            case Real: {
                painter->setPen(option.palette.text().color());
                break;
            }
            case Boolean: {
                painter->setPen(option.palette.text().color());
                break;
            }
            case String: {
                painter->setPen(option.palette.text().color());
                break;
            }
            case Unused: {
                painter->setPen(Qt::gray);
                break;
            }
            case Scalable: {
                painter->setPen(option.palette.text().color());
                break;
            }
            case Enumeration: {
                painter->setPen(option.palette.text().color());
                break;
            }
            case Constant: {
                painter->setPen(option.palette.text().color());
                break;
            }
        }

        if(option.state & QStyle::State_Selected) {
            painter->fillRect(option.rect, option.palette.highlight());
            painter->setPen(option.palette.highlightedText().color());
        }
        painter->drawText(option.rect.x() + 4, option.rect.y(), option.rect.width() - 4, option.rect.height(), Qt::AlignTop, index.data(Qt::DisplayRole).toString());
    }
}

QSize FormularDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const {
    return QSize(option.rect.size());
}

QWidget* FormularDelegate::createEditor(QWidget */*parent*/, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const {
    FieldDataEditor *fieldDataEditor = NULL;
    FieldData *field = (FieldData*)index.data(Qt::EditRole).toInt();
    if(field != NULL) {
        qDebug() << "[Formular delegate] Create editor: Get data from model\t[OK]";
    } else {
        qCritical() << "[Formular delegate] Create editor: Get data from model\t[ERROR]";
        qCritical() << "[Formular delegate] Create editor: Unknown field type. Terminate with NULL return statement";
        return NULL;
    }
    if(field != NULL) {
        fieldDataEditor = new FieldDataEditor(/*parent*/);
        fieldDataEditor->setWindowModality(Qt::ApplicationModal);
        connect(fieldDataEditor, SIGNAL(accept()), this, SLOT(slot_accept()));
        connect(fieldDataEditor, SIGNAL(reject()), this, SLOT(slot_reject()));
        switch(field->getType()) {
            case Integer:
            case Real:
            case Boolean:
            case String:
            case Unused: {
                break;
            }
            case Scalable: {
                fieldDataEditor->additionalLayout->addWidget(new ScalableWidget(fieldDataEditor));
                break;
            }
            case Enumeration: {
                FieldEnumeration *fieldEnumeration = static_cast<FieldEnumeration*>(field);
                EnumerationWidget *enumerationEditor = new EnumerationWidget(fieldDataEditor);
                fieldDataEditor->additionalLayout->addWidget(enumerationEditor);
                connect(enumerationEditor->addButton, SIGNAL(released()), fieldEnumeration, SLOT(slot_addElement()));
                connect(enumerationEditor->removeButton, SIGNAL(released()), fieldEnumeration, SLOT(slot_removeLastElement()));
                break;
            }
            case Constant: {
                fieldDataEditor->additionalLayout->addWidget(new ConstantWidget(fieldDataEditor));
                break;
            }
        }
    }
    extern QStringList g_fieldTypes;
    if(fieldDataEditor != NULL) {
        qDebug() << "[Formular delegate] Create editor: For type" << g_fieldTypes.at(field->getType()) << "\t[OK]";
    } else {
        qCritical() << "[Formular delegate] Create editor: For type" << g_fieldTypes.at(field->getType()) << "\t[ERROR]";
    }
    return fieldDataEditor;
}

void FormularDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    FieldDataEditor *fieldDataEditor = static_cast<FieldDataEditor*>(editor);
    if(fieldDataEditor != NULL) {
        qDebug() << "[Formular delegate] Set editor data: Widget static cast    [OK]";
    } else {
        qCritical() << "[Formular delegate] Set editor data: Widget static cast    [ERROR]";
    }
    FieldData *field = (FieldData*)index.data(Qt::EditRole).toInt();
    if(field != NULL) {
        qDebug() << "[Formular delegate] Set editor data: Get data from model   [OK]";
    } else {
        qCritical() << "[Formular delegate] Set editor data: Get data from model   [ERROR]";
    }
    if(field != NULL && fieldDataEditor != NULL) {
        fieldDataEditor->nameEdit->setText(field->getName());
        fieldDataEditor->setWindowTitle(QString::fromUtf8("Поле ") + field->getName());
        fieldDataEditor->descriptionEdit->setText(field->getDescription());
        fieldDataEditor->typeBox->setCurrentIndex(field->getType());
        fieldDataEditor->dimensionBox->setCurrentIndex(field->getDimension());
        fieldDataEditor->sizeBox->setValue(field->getSize());
        extern QStringList g_fieldTypes;
        qDebug() << "[Formular delegate] Set editor data: Field type" << g_fieldTypes.at(field->getType());
        switch(field->getType()) {
            case Integer:
            case Real:
            case Boolean:
            case String: {
                break;
            }
            case Unused: {
                fieldDataEditor->nameEdit->setDisabled(true);
                fieldDataEditor->descriptionEdit->setDisabled(true);
                fieldDataEditor->dimensionBox->setDisabled(true);
                break;
            }
            case Scalable: {
                FieldScalable *fieldScalable = static_cast<FieldScalable*>(field);
                ScalableWidget *scalableEditor = static_cast<ScalableWidget*>(fieldDataEditor->additionalLayout->itemAt(0)->widget());
                if(fieldScalable->getHighOrderBit() != 0.0) {
                    scalableEditor->highBitRadio->setChecked(true);
                    scalableEditor->bitOrderBox->setValue(fieldScalable->getHighOrderBit());
                } else if (fieldScalable->getLowerOrderBit() != 0.0) {
                    scalableEditor->lowerBitRadio->setChecked(true);
                    scalableEditor->bitOrderBox->setValue(fieldScalable->getLowerOrderBit());
                }
                scalableEditor->additionalCodeCheck->setChecked(fieldScalable->hasAdditionalCode());
                scalableEditor->highBitSignCheck->setChecked(fieldScalable->hasHighBitSign());
                break;
            }
            case Enumeration: {
                FieldEnumeration *fieldEnumeration = static_cast<FieldEnumeration*>(field);
                EnumerationWidget *enumerationEditor = static_cast<EnumerationWidget*>(fieldDataEditor->additionalLayout->itemAt(0)->widget());
                enumerationEditor->tableView->setModel(fieldEnumeration->getModel());
                enumerationEditor->tableView->setItemDelegate(fieldEnumeration->getDelegate());
                updateEditorGeometry(fieldDataEditor, QStyleOptionViewItem(), index);
                break;
            }
            case Constant: {
                FieldConstant *fieldConstant = static_cast<FieldConstant*>(field);
                ConstantWidget *constantEditor = static_cast<ConstantWidget*>(fieldDataEditor->additionalLayout->itemAt(0)->widget());
                constantEditor->constantValue->setText(fieldConstant->getValue());
                break;
            }
        }
    }
}

void FormularDelegate::setModelData(QWidget *editor, QAbstractItemModel */*model*/, const QModelIndex &index) const {
    FieldDataEditor *fieldDataEditor = static_cast<FieldDataEditor*>(editor);
    if(fieldDataEditor != NULL) {
        qDebug() << "[Formular delegate] Set model data: Widget static cast    [OK]";
    } else {
        qCritical() << "[Formular delegate] Set model data: Widget static cast    [ERROR]";
    }
    FieldData *field = (FieldData*)index.data(Qt::EditRole).toInt();
    if(field != NULL) {
        qDebug() << "[Formular delegate] Set model data: Get data from model   [OK]";
    } else {
        qCritical() << "[Formular delegate] Set model data: Get data from model   [ERROR]";
    }
    if(field != NULL && fieldDataEditor != NULL) {
        field->setName(fieldDataEditor->nameEdit->text());
        field->setDescription(fieldDataEditor->descriptionEdit->toPlainText());
        field->setDimension((FieldDimension)fieldDataEditor->dimensionBox->currentIndex());
        field->setSize(fieldDataEditor->sizeBox->value());
        switch(field->getType()) {
            case Integer:
            case Real:
            case Boolean:
            case String:
            case Unused: {
                break;
            }
            case Scalable: {
                FieldScalable *fieldScalable = static_cast<FieldScalable*>(field);
                ScalableWidget *scalableEditor = static_cast<ScalableWidget*>(fieldDataEditor->additionalLayout->itemAt(0)->widget());
                if(scalableEditor->highBitRadio->isChecked()) {
                    fieldScalable->setHighOrderBit(scalableEditor->bitOrderBox->value());
                } else {
                    fieldScalable->setLowerOrderBit(scalableEditor->bitOrderBox->value());
                }
                fieldScalable->setHighBitSign(scalableEditor->highBitSignCheck->isChecked());
                fieldScalable->setAdditionalCode(scalableEditor->additionalCodeCheck->isChecked());
                break;
            }
            case Enumeration: {
                /*
                FieldEnumeration *fieldEnumeration = static_cast<FieldEnumeration*>(field);
                EnumerationWidget *enumerationEditor = static_cast<EnumerationWidget*>(fieldDataEditor->additionalLayout->itemAt(0)->widget());
                */
                break;
            }
            case Constant: {
                FieldConstant *fieldConstant = static_cast<FieldConstant*>(field);
                ConstantWidget *constantEditor = static_cast<ConstantWidget*>(fieldDataEditor->additionalLayout->itemAt(0)->widget());
                fieldConstant->setValue(constantEditor->constantValue->text());
                break;
            }
        }
    }
}

void FormularDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if(editor != NULL && index.isValid()) {
        QWidget *parentWidget = static_cast<QWidget*>(parent());
        int x = parentWidget->x() + 100;
        int y = parentWidget->y() + 200;
        editor->setGeometry(x, y, option.rect.width(), option.rect.height());

        FieldDataEditor *fieldDataEditor = static_cast<FieldDataEditor*>(editor);
        if(fieldDataEditor != NULL) {
            qDebug() << "[Formular delegate] Update editor geometry: Widget static cast    [OK]";
        } else {
            qCritical() << "[Formular delegate] Update editor geometry: Widget static cast    [ERROR]";
        }
        FieldData *field = (FieldData*)index.data(Qt::EditRole).toInt();
        if(field != NULL) {
            qDebug() << "[Formular delegate] Update editor geometry: Get data from model   [OK]";
        } else {
            qCritical() << "[Formular delegate] Update editor geometry: Get data from model   [ERROR]";
        }
        if(field != NULL && fieldDataEditor != NULL) {
            switch(field->getType()) {
                case Integer:
                case Real:
                case Boolean:
                case String:
                case Unused: {
                    break;
                }
                case Scalable: {
                    break;
                }
                case Enumeration: {
                    EnumerationWidget *enumerationEditor = static_cast<EnumerationWidget*>(fieldDataEditor->additionalLayout->itemAt(0)->widget());
                    enumerationEditor->tableView->setColumnWidth(Code, 40);
                    enumerationEditor->tableView->setColumnWidth(Acronym, 95);
                    enumerationEditor->tableView->horizontalHeader()->setStretchLastSection(true);
                    break;
                }
                case Constant: {
                    break;
                }
            }
        }
        editor->adjustSize();
    }
}

bool FormularDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    switch(event->KeyPress) {
    case Qt::Key_Escape: {

    }
    }

    return QAbstractItemDelegate::editorEvent(event, model, option, index);
}

void FormularDelegate::slot_reject() {
    emit closeEditor(static_cast<QWidget*>(sender()));
}

void FormularDelegate::slot_accept() {
    emit commitData(static_cast<QWidget*>(sender()));
    emit closeEditor(static_cast<QWidget*>(sender()));
}

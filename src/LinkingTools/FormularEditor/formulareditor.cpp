#include "formulareditor.h"
#include "ui_formulareditor.h"

#include <QDomDocument>

#include "../formular.h"

FormularEditor::FormularEditor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FormularEditor) {
    ui->setupUi(this);
}

bool FormularEditor::readFromFile(QString fileName) {
    QString errorString;
    int errorLine;
    int errorColumn;
    QFile file(fileName);
    QDomDocument domDocument;

    if(!file.open(QIODevice::ReadOnly))
        return false;

    if(!domDocument.setContent(&file, true, &errorString, &errorLine, &errorColumn)) {
        qWarning() << "Line " << errorLine << "colunm " << errorColumn << " message ";
        return false;
    }

    QDomElement domRoot = domDocument.documentElement();
    qDebug() << "[Formular editor] Read from file: Root tag name" << domRoot.tagName();

    if(domRoot.tagName() != "formular") {
        qCritical() << "[Formular editor] Read from file: Bad file, incorrect root tag name";
        return false;
    }

    QString inputCheck;
    QString defaultCapacity = Formular::capacities.first();
    inputCheck = domRoot.attribute("capacity", "_err_");
    if(inputCheck == "_err_") {
        qWarning() << "[Formular editor] Read from file: No \"capacity\" attribute. Set default" << defaultCapacity;
        inputCheck = QString::number(defaultCapacity);
    }
    if(Formular::capacities.indexOf(inputCheck) == -1) {
        qWarning() << "[Formular editor] Read from file: Bad \"capacity\" attribute. Set default" << defaultCapacity;
        inputCheck = QString::number(defaultCapacity);
    }
    capacityBox->setCurrentIndex(Formular::capacities.indexOf(inputCheck));

    inputCheck = domRoot.attribute("description", "_err_");
    if(inputCheck == "_err_")
    {
        qWarning() << "[Formular editor] Read from file: No \"description\" attribute. Set empty string";
        inputCheck = "";
    }
    descriptionEdit->setText(inputCheck);

    QDomElement domField = domRoot.firstChildElement();
    while(!domField.isNull()) {
        inputCheck = domField.attribute("name", "_err_");
        if(inputCheck == "_err_") {
            qWarning() << "[Formular editor] Read from file: No \"name\" attribute. Set empty string";
            inputCheck = "";
        }
        QString name = inputCheck;

        inputCheck = domField.attribute("description", "_err_");
        if(inputCheck == "_err_") {
            qWarning() << "[Formular editor] Read from file: No \"description\" attribute. Set empty string";
            inputCheck = "";
        }
        QString description = inputCheck;

        const QString defaultFieldSize = "1";
        inputCheck = domField.attribute("size", "_err_");
        if(inputCheck == "_err_") {
            qWarning() << "[Formular editor] Read from file: No \"size\" attribute. Set default" << defaultFieldSize;
            inputCheck = QString::number(defaultFieldSize);
        }
        if(inputCheck.toInt() <= 0) {
            qWarning() << "[Formular editor] Read from file: Bad \"size\" attribute. Set default" << defaultFieldSize;
            inputCheck = QString::number(defaultFieldSize);
        }
        int size = inputCheck.toInt();

        const FieldData::Dimension defaultFieldDimension = FieldData::No;
        inputCheck = domField.attribute("dimension", "_err_");
        if(inputCheck == "_err_") {
            qWarning() << "[Formular editor] Read from file: No \"dimension\" attribute. Set default" << FieldData::dimensions.at(defaultFieldDimension);
            inputCheck = FieldData::dimensions.at(defaultFieldDimension);
        }
        if(FieldData::dimensions.indexOf(inputCheck) == -1) {
            qWarning() << "[Formular editor] Read from file: Bad \"dimension\" attribute. Set default" << FieldData::dimensions.at(defaultFieldDimension);
            inputCheck = FieldData::dimensions.at(defaultFieldDimension);
        }
        FieldData::Dimension dimension = (FieldDimension)FieldData::dimensions.indexOf(inputCheck);

        const FieldData::Type defaultFieldType = FieldData::Integer;
        inputCheck = domField.attribute("type", "_err_");
        if(inputCheck == "_err_") {
            qWarning() << "[Formular editor] Read from file: No \"type\" attribute. Set default" << FieldData::types.at(defaultFieldType);
            inputCheck = FieldData::types.at(defaultFieldType);
        }
        if(FieldData::types.indexOf(inputCheck) == -1) {
            qWarning() << "[Formular editor] Read from file: Bad \"type\" attribute. Set default" << FieldData::types.at(defaultFieldType);
            inputCheck = FieldData::types.at(defaultFieldType);
        }
        FieldData::Type type = (FieldType)FieldData::types.indexOf(inputCheck);

        switch(type) {
            case Integer:
            case Real:
            case Boolean:
            case String:
            case Unused: {
                FieldData *field = new FieldData(name, description, type, dimension, size);
                m_formularModel->insertRow(m_formularModel->rowCount());
                m_formularModel->setData(m_formularModel->index(m_formularModel->rowCount() - 1), QVariant((int)field), Qt::EditRole);
                break;
            }
            case Scalable: {
                FieldScalable *field = new FieldScalable(name, description, type, dimension, size);
                const double defaultHighOrderBit = 0.0;
                inputCheck = domField.attribute("highOrderBit", "_err_");
                if(inputCheck == "_err_") {
                    qWarning() << "[Formular editor] Read from file: No \"highOrderBit\" attribute. Set default" << defaultHighOrderBit;
                    inputCheck = QString::number(defaultHighOrderBit);
                }
                field->setHighOrderBit(inputCheck.toDouble());
                const double defaultLowerOrderBit = 0.0;
                inputCheck = domField.attribute("lowerOrderBit", "_err_");
                if(inputCheck == "_err_") {
                    qWarning() << "[Formular editor] Read from file: No \"lowerOrderBit\" attribute. Set default" << defaultLowerOrderBit;
                    inputCheck = QString::number(defaultLowerOrderBit);
                }
                field->setLowerOrderBit(inputCheck.toDouble());
                const bool defaultAdditionalCodeState = false;
                inputCheck = domField.attribute("additionalCode", "_err_");
                if(inputCheck == "_err_") {
                    qWarning() << "[Formular editor] Read from file: No \"additionalCode\" attribute. Set default" << defaultAdditionalCodeState;
                    inputCheck = QString::number(defaultAdditionalCodeState);
                }
                field->setAdditionalCode(inputCheck.toInt());
                const bool defaultHighBitSignState = false;
                inputCheck = domField.attribute("highBitSign", "_err_");
                if(inputCheck == "_err_") {
                    qWarning() << "[Formular editor] Read from file: No \"highBitSign\" attribute. Set default" << defaultHighBitSignState;
                    inputCheck = QString::number(defaultHighBitSignState);
                }
                field->setHighBitSign(inputCheck.toInt());
                m_formularModel->insertRow(m_formularModel->rowCount());
                m_formularModel->setData(m_formularModel->index(m_formularModel->rowCount() - 1), QVariant((int)field), Qt::EditRole);
                break;
            }
            case Enumeration: {
                FieldEnumeration *field = new FieldEnumeration(name, description, type, dimension, size);
                QDomElement domEnumerationElement = domField.firstChildElement();
                uint code = 0;
                while(!domEnumerationElement.isNull()) {
                    field->getModel()->insertRow(field->getModel()->rowCount());
                    inputCheck = domEnumerationElement.attribute("code", "_err_");
                    if(inputCheck == "_err_") {
                        qWarning() << "[Formular editor] Read from file: No \"code\" attribute. Set default" << code;
                        inputCheck = QString::number(code);
                    }
                    ++code;
                    field->getModel()->setData(field->getModel()->index(field->getModel()->rowCount() - 1, Code), QVariant(inputCheck.toInt()), Qt::EditRole);
                    inputCheck = domEnumerationElement.attribute("acronym", "_err_");
                    if(inputCheck == "_err_") {
                        qWarning() << "[Formular editor] Read from file: No \"acronym\" attribute. Set empty string";
                        inputCheck = "";
                    }
                    field->getModel()->setData(field->getModel()->index(field->getModel()->rowCount() - 1, Acronym), QVariant(inputCheck), Qt::EditRole);
                    inputCheck = domEnumerationElement.attribute("transcript", "_err_");
                    if(inputCheck == "_err_") {
                        qWarning() << "[Formular editor] Read from file: No \"transcript\" attribute. Set empty string";
                        inputCheck = "";
                    }
                    field->getModel()->setData(field->getModel()->index(field->getModel()->rowCount() - 1, Transcript), QVariant(inputCheck), Qt::EditRole);
                    domEnumerationElement = domEnumerationElement.nextSiblingElement();
                }
                m_formularModel->insertRow(m_formularModel->rowCount());
                m_formularModel->setData(m_formularModel->index(m_formularModel->rowCount() - 1), QVariant((int)field), Qt::EditRole);
                break;
            }
            case Constant: {
                FieldConstant *field = new FieldConstant(name, description, type, dimension, size);
                inputCheck = domField.attribute("value", "_err_");
                if(inputCheck == "_err_") {
                    qWarning() << "[Formular editor] Read from file: No \"value\" attribute. Set empty string";
                    inputCheck = "";
                }
                field->setValue(inputCheck);
                m_formularModel->insertRow(m_formularModel->rowCount());
                m_formularModel->setData(m_formularModel->index(m_formularModel->rowCount() - 1), QVariant((int)field), Qt::EditRole);
                break;
            }
        }
        domField = domField.nextSiblingElement();
    }
    return true;
}

bool FormularEditor::writeToFile(QString fileName) {
    QDomDocument domDocument("formular");
    QDomNode xmlNode = domDocument.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    domDocument.insertBefore(xmlNode, domDocument.firstChildElement());
    QDomElement domRoot;
    domRoot = domDocument.createElement("formular");
    domRoot.setAttribute("capacity", Formular::capacities.at(capacityBox->currentIndex()));
    domRoot.setAttribute("description", descriptionEdit->toPlainText());
    domDocument.appendChild(domRoot);
    for(int i = 0; i < m_formularModel->rowCount(); i++) {
        QDomElement domField = domDocument.createElement("field");
        domRoot.appendChild(domField);
        FieldData *field = (FieldData*)m_formularModel->data(m_formularModel->index(i), Qt::EditRole).toInt();
        domField.setAttribute("name", field->getName());
        domField.setAttribute("description", field->getDescription());
        domField.setAttribute("type", FieldData::types.at(field->getType()));
        domField.setAttribute("dimension", FieldData::dimensions.at(field->getDimension()));
        domField.setAttribute("size", field->getSize());
        switch(field->getType()) {
            case Integer:
            case Real:
            case Boolean:
            case String:
            case Unused: {
                break;
            }
            case Scalable: {
                FieldScalable *fieldScalable = static_cast<FieldScalable*>((FieldData*)m_formularModel->data(m_formularModel->index(i), Qt::EditRole).toInt());
                domField.setAttribute("highOrderBit", fieldScalable->getHighOrderBit());
                domField.setAttribute("lowerOrderBit", fieldScalable->getLowerOrderBit());
                domField.setAttribute("additionalCode", fieldScalable->hasAdditionalCode());
                domField.setAttribute("highBitSign", fieldScalable->hasHighBitSign());
                break;
            }
            case Enumeration: {
                FieldEnumeration *fieldEnumeration = static_cast<FieldEnumeration*>((FieldData*)m_formularModel->data(m_formularModel->index(i), Qt::EditRole).toInt());
                for (int j = 0; j < fieldEnumeration->getModel()->rowCount(); j++) {
                    QDomElement domEnumerationElement = domDocument.createElement("element");
                    domField.appendChild(domEnumerationElement);
                    domEnumerationElement.setAttribute("code", fieldEnumeration->getModel()->index(j, Code).data(Qt::EditRole).toString());
                    domEnumerationElement.setAttribute("acronym", fieldEnumeration->getModel()->index(j, Acronym).data(Qt::EditRole).toString());
                    domEnumerationElement.setAttribute("transcript", fieldEnumeration->getModel()->index(j, Transcript).data(Qt::EditRole).toString());
                }
                break;
            }
            case Constant: {
                FieldConstant *fieldConstant = static_cast<FieldConstant*>((FieldData*)m_formularModel->data(m_formularModel->index(i), Qt::EditRole).toInt());
                domField.setAttribute("value", fieldConstant->getValue());
                break;
            }
        }
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
            return false;
    QTextStream st(&file);
    domDocument.save(st, 4);
    file.close();
    return true;
}

FormularEditor::~FormularEditor() {
    delete ui;
}

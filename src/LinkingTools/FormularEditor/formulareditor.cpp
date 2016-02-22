#include "formulareditor.h"
#include "ui_formulareditor.h"

#include <QDomDocument>
#include <QDebug>

#include "formular.h"

FormularEditor::FormularEditor(QWidget *parent)
    : FileEditor(parent), ui(new Ui::FormularEditor) {
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
    const uint defaultCapacity = 8;
    inputCheck = domRoot.attribute("capacity", "_err_");
    if(inputCheck == "_err_") {
        qWarning() << "[Formular editor] Read from file: No \"capacity\" attribute. Set default" << defaultCapacity;
        inputCheck = QString::number(defaultCapacity);
    }
    if(inputCheck.toInt()%8) {
        qWarning() << "[Formular editor] Read from file: Bad \"capacity\" attribute. Set default" << defaultCapacity;
        inputCheck = QString::number(defaultCapacity);
    }
    ui->capacityBox->setCurrentIndex(Formular::capacities.indexOf(inputCheck));

    inputCheck = domRoot.attribute("description", "_err_");
    if(inputCheck == "_err_")
    {
        qWarning() << "[Formular editor] Read from file: No \"description\" attribute. Set empty string";
        inputCheck = "";
    }
    ui->descriptionEdit->setText(inputCheck);

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

        const uint defaultFieldSize = 1;
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
        FieldData::Dimension dimension = (FieldData::Dimension)FieldData::dimensions.indexOf(inputCheck);

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
        FieldData::Type type = (FieldData::Type)FieldData::types.indexOf(inputCheck);

        switch(type) {
            case FieldData::Integer:
            case FieldData::Real:
            case FieldData::Boolean:
            case FieldData::String:
            case FieldData::Unused: {
                FieldData *field = new FieldData(name, description, type, dimension, size);
                m_formularModel->insertRow(m_formularModel->rowCount());
                m_formularModel->setData(m_formularModel->index(m_formularModel->rowCount() - 1), QVariant((long long int)field), Qt::EditRole);
                break;
            }
            case FieldData::Scalable: {
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
                m_formularModel->setData(m_formularModel->index(m_formularModel->rowCount() - 1), QVariant((long long int)field), Qt::EditRole);
                break;
            }
            case FieldData::Enumeration: {
                FieldEnumeration *field = new FieldEnumeration(name, description, type, dimension, size);
                QDomElement domEnumerationElement = domField.firstChildElement();
                uint code = 0;
                while(!domEnumerationElement.isNull()) {
                    FieldEnumeration::EnumerationElement elem;

                    inputCheck = domEnumerationElement.attribute("code", "_err_");
                    if(inputCheck == "_err_") {
                        qWarning() << "[Formular editor] Read from file: No \"code\" attribute. Set default" << code;
                        inputCheck = QString::number(code);
                    }
                    ++code;
                    elem.setCode(inputCheck);

                    inputCheck = domEnumerationElement.attribute("acronym", "_err_");
                    if(inputCheck == "_err_") {
                        qWarning() << "[Formular editor] Read from file: No \"acronym\" attribute. Set empty string";
                        inputCheck = "";
                    }
                    elem.setAcronym(inputCheck);

                    inputCheck = domEnumerationElement.attribute("transcript", "_err_");
                    if(inputCheck == "_err_") {
                        qWarning() << "[Formular editor] Read from file: No \"transcript\" attribute. Set empty string";
                        inputCheck = "";
                    }
                    elem.setTranscript(inputCheck);
                    domEnumerationElement = domEnumerationElement.nextSiblingElement();

                    field->getElements().append(elem);
                }
                m_formularModel->insertRow(m_formularModel->rowCount());
                m_formularModel->setData(m_formularModel->index(m_formularModel->rowCount() - 1), QVariant((long long int)field), Qt::EditRole);
                break;
            }
            case FieldData::Constant: {
                FieldConstant *field = new FieldConstant(name, description, type, dimension, size);
                inputCheck = domField.attribute("value", "_err_");
                if(inputCheck == "_err_") {
                    qWarning() << "[Formular editor] Read from file: No \"value\" attribute. Set empty string";
                    inputCheck = "";
                }
                field->setValue(inputCheck);
                m_formularModel->insertRow(m_formularModel->rowCount());
                m_formularModel->setData(m_formularModel->index(m_formularModel->rowCount() - 1), QVariant((long long int)field), Qt::EditRole);
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
    domRoot.setAttribute("capacity", Formular::capacities.at(ui->capacityBox->currentIndex()));
    domRoot.setAttribute("description", ui->descriptionEdit->toPlainText());
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
            case FieldData::Integer:
            case FieldData::Real:
            case FieldData::Boolean:
            case FieldData::String:
            case FieldData::Unused: {
                break;
            }
            case FieldData::Scalable: {
                FieldScalable *fieldScalable = static_cast<FieldScalable*>((FieldData*)m_formularModel->data(m_formularModel->index(i), Qt::EditRole).toInt());
                domField.setAttribute("highOrderBit", fieldScalable->getHighOrderBit());
                domField.setAttribute("lowerOrderBit", fieldScalable->getLowerOrderBit());
                domField.setAttribute("additionalCode", fieldScalable->hasAdditionalCode());
                domField.setAttribute("highBitSign", fieldScalable->hasHighBitSign());
                break;
            }
            case FieldData::Enumeration: {
                FieldEnumeration *fieldEnumeration = static_cast<FieldEnumeration*>((FieldData*)m_formularModel->data(m_formularModel->index(i), Qt::EditRole).toInt());
                for (int j = 0; j < fieldEnumeration->getElements().size(); j++) {
                    QDomElement domEnumerationElement = domDocument.createElement("element");
                    domField.appendChild(domEnumerationElement);
                    domEnumerationElement.setAttribute("code", fieldEnumeration->getElements()[j].getCode());
                    domEnumerationElement.setAttribute("acronym", fieldEnumeration->getElements()[j].getAcronym());
                    domEnumerationElement.setAttribute("transcript", fieldEnumeration->getElements()[j].getTranscript());
                }
                break;
            }
            case FieldData::Constant: {
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

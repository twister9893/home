#include "formulareditor.h"

const QStringList FormularEditor::m_capacities = QStringList() << QString("8")
                                                               << QString("16")
                                                               << QString("32");

FormularEditor::FormularEditor(QWidget *parent) :
    QMainWindow(parent) {
    setupUi(this);
    m_formularModel = new FormularModel(m_formularData, this);
    //m_formularModel->setSupportedDragActions(Qt::MoveAction);
    //tableView->setAcceptDrops(true);
    tableView->setModel(m_formularModel);
    tableView->setColumnWidth(Size, 50);
    tableView->setColumnWidth(Type, 120);
    tableView->setColumnWidth(Name, 95);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->setVisible(false);
    //tableView->verticalHeader()->setMovable(true);
    m_formularDelegate = new FormularDelegate(this);
    tableView->setItemDelegate(m_formularDelegate);
    setEditFlag(false);

    m_defaultDirectory = "./";
    m_defaultRowHeight = 20;
    m_defaultCapacity = 8;
    m_defaultFieldSize = 1;
    m_defaultFieldType = FieldData::Integer;
    m_defaultFieldDimension = FieldData::No;
    m_defaultHighOrderBit = 0.0;
    m_defaultLowerOrderBit = 0.0;
    m_defaultAdditionalCodeState = false;
    m_defaultHighBitSignState = false;

    QMenu *typePopup = new QMenu(addFieldButton);
    for(int i = 0; i < FieldData::fieldTypes.size(); i++) {
        m_fieldTypeActions.append(typePopup->addAction( FieldData::fieldTypes.at(i)));
    }
    addFieldButton->setMenu(typePopup);
    capacityBox->addItems(m_capacities);

    connect(newAction, SIGNAL(triggered()), this, SLOT(slot_createFormular()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(slot_openFormular()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(slot_saveFormular()));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(slot_saveFormularAs()));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(slot_close()));
    connect(typePopup, SIGNAL(triggered(QAction*)), this, SLOT(slot_addField(QAction*)));
    connect(removeFieldButton, SIGNAL(released()), this, SLOT(slot_removeField()));

    connect(m_formularModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(slot_setEditFlag()));
    connect(m_formularDelegate, SIGNAL(commitData(QWidget*)), this, SLOT(slot_setEditFlag()));

    connect(m_formularModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(slot_separateFields()));
    connect(m_formularDelegate, SIGNAL(commitData(QWidget*)), this, SLOT(slot_separateFields()));
    connect(capacityBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_separateFields()));
}

void FormularEditor::slot_createFormular() {
    bool isCancel = showSaveMessage();
    if(!isCancel) {
        m_formularFileInfo.setFile("");
        clearAll();
    }
}

void FormularEditor::slot_openFormular() {
    bool isCancel = showSaveMessage();
    if(!isCancel) {
        QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), m_defaultDirectory, "*.xml");
        if(!fileName.isEmpty()) {
            clearAll();
            bool isSuccess = readFromFile(fileName);
            if(isSuccess) {
                m_formularFileInfo.setFile(fileName);
                qDebug() << "[Formular editor] File has been opened" << m_formularFileInfo.filePath();
                setEditFlag(false);
            } else {
                qCritical() << "[Formular editor] File has not been opened";
            }
        }
    }
}

void FormularEditor::slot_saveFormular() {
    if(m_formularFileInfo.isFile()) {
        bool isSuccess = writeToFile(m_formularFileInfo.filePath());
        if(isSuccess) {
            qDebug() << "[Formular editor] File has been saved" << m_formularFileInfo.filePath();
            setEditFlag(false);
        } else {
            qCritical() << "[Formular editor] File has not been saved" << m_formularFileInfo.filePath();
        }
    }
    else {
        slot_saveFormularAs();
    }
}

void FormularEditor::slot_saveFormularAs() {
    QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), m_defaultDirectory, "*.xml");
    if(!fileName.isEmpty()) {
        m_formularFileInfo.setFile(fileName);
        bool isSuccess = writeToFile(m_formularFileInfo.filePath());
        if(isSuccess) {
            qDebug() << "[Formular editor] File has been saved" << m_formularFileInfo.filePath();
            setEditFlag(false);
        } else {
            qCritical() << "[Formular editor] File has not been saved" << m_formularFileInfo.filePath();
        }
    }
}

void FormularEditor::slot_close() {
    bool isCancel = showSaveMessage();
    if(!isCancel) {
        m_formularFileInfo.setFile("");
        clearAll();
        hide();
    }
}

void FormularEditor::closeEvent(QCloseEvent *event) {
    slot_close();
    event->ignore();
}

void FormularEditor::slot_addField(QAction *type) {
    FieldType typeIndex = (FieldType)m_fieldTypeActions.indexOf(type);
    extern QStringList g_fieldTypes;
    int position;
    if(toCurrentRadio->isChecked()) {
        position = tableView->currentIndex().row();
        if(position < 0) {
            position = 0;
        }
    } else {
        position = m_formularModel->rowCount();
    }
    qDebug() << "[Formular editor] Add field: Type" << g_fieldTypes.at(typeIndex) << "to" << position;
    switch(typeIndex) {
        case Integer:
        case Real:
        case Boolean:
        case String:
        case Unused: {
            FieldData *field = new FieldData();
            field->setType(typeIndex);
            m_formularModel->insertRow(position);
            m_formularModel->setData(m_formularModel->index(position), QVariant((int)field), Qt::EditRole);
            break;
        }
        case Scalable: {
            FieldScalable *field = new FieldScalable();
            m_formularModel->insertRow(position);
            m_formularModel->setData(m_formularModel->index(position), QVariant((int)field), Qt::EditRole);
            break;
        }
        case Enumeration: {
            FieldEnumeration *field = new FieldEnumeration();
            m_formularModel->insertRow(position);
            m_formularModel->setData(m_formularModel->index(position), QVariant((int)field), Qt::EditRole);
            break;
        }
        case Constant: {
            FieldConstant *field = new FieldConstant();
            m_formularModel->insertRow(position);
            m_formularModel->setData(m_formularModel->index(position), QVariant((int)field), Qt::EditRole);
            break;
        }
    }
    qDebug() << "[Formular editor] Add field: Count " << m_formularModel->rowCount();
}

void FormularEditor::slot_removeField() {
    QModelIndex currentIndex = tableView->currentIndex();
    FieldData *field = (FieldData*)currentIndex.data(Qt::EditRole).toInt();
    if(field != NULL) {
        m_formularModel->removeRow(currentIndex.row());
    }
}

void FormularEditor::slot_setEditFlag() {
    setEditFlag(true);
}

void FormularEditor::slot_separateFields() {
    int size = 0;
    for(int i = 0; i < m_formularModel->rowCount(); i++) {
        size += m_formularModel->index(i, Size).data(Qt::DisplayRole).toInt();
        if(size >= capacityBox->currentText().toInt()) {
            tableView->setRowHeight(i, m_defaultRowHeight * 2);
            size = 0;
        } else {
            tableView->setRowHeight(i, m_defaultRowHeight);
        }
    }
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
    extern QStringList g_capacities;
    inputCheck = domRoot.attribute("capacity", "_err_");
    if(inputCheck == "_err_") {
        qWarning() << "[Formular editor] Read from file: No \"capacity\" attribute. Set default" << m_defaultCapacity;
        inputCheck = QString::number(m_defaultCapacity);
    }
    if(g_capacities.indexOf(inputCheck) == -1) {
        qWarning() << "[Formular editor] Read from file: Bad \"capacity\" attribute. Set default" << m_defaultCapacity;
        inputCheck = QString::number(m_defaultCapacity);
    }
    capacityBox->setCurrentIndex(g_capacities.indexOf(inputCheck));

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

        inputCheck = domField.attribute("size", "_err_");
        if(inputCheck == "_err_") {
            qWarning() << "[Formular editor] Read from file: No \"size\" attribute. Set default" << m_defaultFieldSize;
            inputCheck = QString::number(m_defaultFieldSize);
        }
        if(inputCheck.toInt() <= 0) {
            qWarning() << "[Formular editor] Read from file: Bad \"size\" attribute. Set default" << m_defaultFieldSize;
            inputCheck = QString::number(m_defaultFieldSize);
        }
        int size = inputCheck.toInt();

        extern QStringList g_fieldDimensions;
        inputCheck = domField.attribute("dimension", "_err_");
        if(inputCheck == "_err_") {
            qWarning() << "[Formular editor] Read from file: No \"dimension\" attribute. Set default" << g_fieldDimensions.at(m_defaultFieldDimension);
            inputCheck = g_fieldDimensions.at(m_defaultFieldDimension);
        }
        if(g_fieldDimensions.indexOf(inputCheck) == -1) {
            qWarning() << "[Formular editor] Read from file: Bad \"dimension\" attribute. Set default" << g_fieldDimensions.at(m_defaultFieldDimension);
            inputCheck = g_fieldDimensions.at(m_defaultFieldDimension);
        }
        FieldDimension dimension = (FieldDimension)g_fieldDimensions.indexOf(inputCheck);

        extern QStringList g_fieldTypes;
        inputCheck = domField.attribute("type", "_err_");
        if(inputCheck == "_err_") {
            qWarning() << "[Formular editor] Read from file: No \"type\" attribute. Set default" << g_fieldTypes.at(m_defaultFieldType);
            inputCheck = g_fieldTypes.at(m_defaultFieldType);
        }
        if(g_fieldTypes.indexOf(inputCheck) == -1) {
            qWarning() << "[Formular editor] Read from file: Bad \"type\" attribute. Set default" << g_fieldTypes.at(m_defaultFieldType);
            inputCheck = g_fieldTypes.at(m_defaultFieldType);
        }
        FieldType type = (FieldType)g_fieldTypes.indexOf(inputCheck);

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
                inputCheck = domField.attribute("highOrderBit", "_err_");
                if(inputCheck == "_err_") {
                    qWarning() << "[Formular editor] Read from file: No \"highOrderBit\" attribute. Set default" << m_defaultHighOrderBit;
                    inputCheck = QString::number(m_defaultHighOrderBit);
                }
                field->setHighOrderBit(inputCheck.toDouble());
                inputCheck = domField.attribute("lowerOrderBit", "_err_");
                if(inputCheck == "_err_") {
                    qWarning() << "[Formular editor] Read from file: No \"lowerOrderBit\" attribute. Set default" << m_defaultLowerOrderBit;
                    inputCheck = QString::number(m_defaultLowerOrderBit);
                }
                field->setLowerOrderBit(inputCheck.toDouble());
                inputCheck = domField.attribute("additionalCode", "_err_");
                if(inputCheck == "_err_") {
                    qWarning() << "[Formular editor] Read from file: No \"additionalCode\" attribute. Set default" << m_defaultAdditionalCodeState;
                    inputCheck = QString::number(m_defaultAdditionalCodeState);
                }
                field->setAdditionalCode(inputCheck.toInt());
                inputCheck = domField.attribute("highBitSign", "_err_");
                if(inputCheck == "_err_") {
                    qWarning() << "[Formular editor] Read from file: No \"highBitSign\" attribute. Set default" << m_defaultHighBitSignState;
                    inputCheck = QString::number(m_defaultHighBitSignState);
                }
                field->setHighBitSign(inputCheck.toInt());
                m_formularModel->insertRow(m_formularModel->rowCount());
                m_formularModel->setData(m_formularModel->index(m_formularModel->rowCount() - 1), QVariant((int)field), Qt::EditRole);
                break;
            }
            case Enumeration: {
                FieldEnumeration *field = new FieldEnumeration(name, description, type, dimension, size);
                QDomElement domEnumerationElement = domField.firstChildElement();
                while(!domEnumerationElement.isNull()) {
                    field->getModel()->insertRow(field->getModel()->rowCount());
                    inputCheck = domEnumerationElement.attribute("code", "_err_");
                    if(inputCheck == "_err_") {
                        qWarning() << "[Formular editor] Read from file: No \"code\" attribute. Set default" << m_defaultEnumerationCode;
                        inputCheck = QString::number(m_defaultEnumerationCode);
                    }
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
    extern QStringList g_capacities;
    domRoot = domDocument.createElement("formular");
    domRoot.setAttribute("capacity", g_capacities.at(capacityBox->currentIndex()));
    domRoot.setAttribute("description", descriptionEdit->toPlainText());
    domDocument.appendChild(domRoot);
    for(int i = 0; i < m_formularModel->rowCount(); i++) {
        QDomElement domField = domDocument.createElement("field");
        extern QStringList g_fieldTypes;
        extern QStringList g_fieldDimensions;
        domRoot.appendChild(domField);
        FieldData *field = (FieldData*)m_formularModel->data(m_formularModel->index(i), Qt::EditRole).toInt();
        domField.setAttribute("name", field->getName());
        domField.setAttribute("description", field->getDescription());
        domField.setAttribute("type", g_fieldTypes.at(field->getType()));
        domField.setAttribute("dimension", g_fieldDimensions.at(field->getDimension()));
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

void FormularEditor::clearAll() {
    m_formularModel->removeRows(0, m_formularModel->rowCount());
}

bool FormularEditor::showSaveMessage() {
    int answer = QMessageBox::No;
    if(m_isEdited) {
        answer = QMessageBox::question(this, QString::fromUtf8("Сохранить"), QString::fromUtf8("Сохранить изменения в файле?\n") + m_formularFileInfo.filePath(), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
    }
    switch(answer) {
        case QMessageBox::Yes: {
            slot_saveFormular();
            break;
        }
        case QMessageBox::No: {
            break;
        }
        case QMessageBox::Cancel: {
            return true;
        }
    }
    return false;
}

void FormularEditor::setEditFlag(bool isEdited) {
    qDebug() << "[Formular editor] Set edit flag" << isEdited;
    m_isEdited = isEdited;

    QString windowTitle;
    if(m_formularFileInfo.isFile()) {
        windowTitle.append(m_formularFileInfo.fileName());
        if(isEdited)
            windowTitle.append("*");
        windowTitle.append(" - ");
    }
    windowTitle.append(QString::fromUtf8("Редактор формуляров"));
    setWindowTitle(windowTitle);
}

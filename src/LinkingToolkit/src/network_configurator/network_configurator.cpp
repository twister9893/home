#include "network_configurator.h"

#include <QPluginLoader>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDir>
#include <QRegExp>
#include <QStatusBar>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>

NetworkConfigurator::NetworkConfigurator(QWidget *parent) :
    QMainWindow(parent), _defaultDir("./"), _isEdited(false)
{
    setupUi(this);

    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(save()));
    connect(saveAsAction, SIGNAL(triggered(bool)), this, SLOT(saveAs()));
    connect(defaultButton, SIGNAL(clicked()), this, SLOT(setDefault()));
    connect(quitAction, SIGNAL(triggered(bool)), this, SLOT(quit()));
    connect(interfaceCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setDefault(int)));

    loadPlugins();
}

void NetworkConfigurator::setDefaultDir(QString defaultDir)
{
    _defaultDir = defaultDir;
}

void NetworkConfigurator::open()
{
    bool isCancel = showSaveMessage();
    if(!isCancel) {
        QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), _defaultDir, "*.xml");
        if(!fileName.isEmpty()) {
            bool isSuccess = readFromFile(fileName);
            if(isSuccess) {
                _fileInfo.setFile(fileName);
                setEdited(false);
            }
        }
    }
}

void NetworkConfigurator::save()
{
    if(_fileInfo.isFile()) {
        bool isSuccess = writeToFile(_fileInfo.filePath());
        if(isSuccess) {
            setEdited(false);
        }
    }
    else {
        saveAs();
    }
}

void NetworkConfigurator::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), _defaultDir, "*.xml");
    if(!fileName.isEmpty()) {
        if(!fileName.contains(QRegExp(".xml$", Qt::CaseInsensitive)))
            fileName.append(".xml");
        _fileInfo.setFile(fileName);
        bool isSuccess = writeToFile(_fileInfo.filePath());
        if(isSuccess) {
            setEdited(false);
        }
    }
}

void NetworkConfigurator::quit()
{
    bool isCancel = showSaveMessage();
    if(!isCancel) {
        exit(0);
    }
}

void NetworkConfigurator::setDefault()
{
    setDefault(interfaceCombo->currentIndex());
}

void NetworkConfigurator::setDefault(int id)
{
    if(id < 0 || id >= _interfaces.size())
        return;
    QString xml = _interfaces.at(id)->configure();
    constructWindow(xml);
    setEdited();
}

void NetworkConfigurator::setEdited()
{
    setEdited(true);
}

void NetworkConfigurator::setEdited(bool edited)
{
    if(edited) {
        statusBar()->showMessage(_fileInfo.fileName() + "*");
//        setWindowTitle(_fileInfo.fileName() + "*");
    } else {
        statusBar()->showMessage(_fileInfo.fileName());
//        setWindowTitle(_fileInfo.fileName());
    }
    _isEdited = edited;
}

void NetworkConfigurator::closeEvent(QCloseEvent *e)
{
    quit();
    e->ignore();
}

bool NetworkConfigurator::readFromFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        return false;
    QTextStream stream(&file);
    QString xml = stream.readAll();
    file.close();
    constructWindow(xml);
    return true;
}

bool NetworkConfigurator::writeToFile(const QString &fileName)
{
    QDomElement domRoot = _config.documentElement();
    QFileInfo info(fileName);
    domRoot.setAttribute("name", info.baseName());
    QDomElement param = domRoot.firstChildElement();
    int num=0;
    while(!param.isNull()) {
        setValue(param, num);
        num++;
        param = param.nextSiblingElement();
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
            return false;
    QTextStream st(&file);
    _config.save(st, 4);
    file.close();
    return true;
}

bool NetworkConfigurator::showSaveMessage() {
    int answer = QMessageBox::No;
    if(_isEdited) {
        answer = QMessageBox::question(this, QString::fromUtf8("Сохранить"), QString::fromUtf8("Сохранить изменения в файле?\n") + _fileInfo.filePath(), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
    }
    switch(answer) {
    case QMessageBox::Yes: {
        save();
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

void NetworkConfigurator::loadPlugins()
{
    qDebug() << "Loading plugins...";
    _interfaces.clear();
    interfaceCombo->clear();
    QDir pluginsDir( "../lib/" );
    QStringList entryList = pluginsDir.entryList(QDir::Files);
    for(int i = 0; i < entryList.size(); i++) {
        QString pluginName = entryList.at(i);
        QPluginLoader loader(pluginsDir.absoluteFilePath(pluginName));

        if(loader.load()) {
            if(ConnectionInterface* interface = qobject_cast<ConnectionInterface*>(loader.instance())) {
                _interfaces.push_back(interface);
                interfaceCombo->addItem(interface->name());
                qDebug() << "[OK]" << pluginName;
            } else {
                qDebug() << "Skip" << pluginName;
            }
        } else {
            qCritical() << "[ERROR]" << pluginName;
            qCritical() << loader.errorString();
        }
    }
}

void NetworkConfigurator::clearWindow()
{
    while(parametersLayout->count())
    {
        QLayoutItem *item = parametersLayout->itemAt(0);
        QLayout *row = item->layout();
        while(row->count()) {
            delete row->itemAt(0)->widget();
        }
        delete row;
        parametersLayout->update();
    }
}

void NetworkConfigurator::constructWindow(const QDomDocument &config)
{
    if(config.isNull()) {
        qCritical() << "Can't construct window, bad config";
        return;
    }

    QDomElement domRoot = config.documentElement();
    if(domRoot.tagName() != "config") {
        qCritical() << "Can't construct window from config, incorrect root tag name" << domRoot.tagName();
        return;
    }

    int id = interfaceCombo->findText(domRoot.attribute("interface"));
    interfaceCombo->setCurrentIndex(id);

    clearWindow();
    QDomElement param = domRoot.firstChildElement();
    while(!param.isNull()) {
        QHBoxLayout *row = new QHBoxLayout();
        row->addWidget(labelFor(param), 2);
        row->addWidget(editorFor(param), 1);
        param = param.nextSiblingElement();
        parametersLayout->addLayout(row);
    }
    _config = config;
}

void NetworkConfigurator::constructWindow(const QString &xml) {
    QDomDocument config = xmlStringToDom(xml);
    constructWindow(config);
}

QDomDocument NetworkConfigurator::xmlStringToDom(const QString &xml)
{
    QDomDocument config;
    QString errorMsg;
    int errorLine;
    int errorColumn;
    if(!config.setContent(xml, &errorMsg, &errorLine, &errorColumn)) {
        qCritical() << "Can't read config";
        qCritical() << "Line:" << errorLine << "Colunm:" << errorColumn;
        qCritical() << errorMsg;
    }
    return config;
}

QWidget *NetworkConfigurator::editorFor(const QDomElement &param)
{
    if(param.attribute("type") == "integer") {
        QSpinBox *spinBox = new QSpinBox(parametersGroup);
        if(!param.attribute("min").isEmpty())
            spinBox->setMinimum(param.attribute("min").toInt());
        else
            spinBox->setMinimum(-1000000);
        if(!param.attribute("max").isEmpty())
            spinBox->setMaximum(param.attribute("max").toInt());
        else
            spinBox->setMaximum(1000000);
        spinBox->setValue(param.attribute("value").toInt());
        connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(setEdited()));
        return spinBox;
    } else if(param.attribute("type") == "boolean") {
        QCheckBox *checkBox = new QCheckBox(parametersGroup);
        checkBox->setChecked(param.attribute("value").toInt());
        connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setEdited()));
        return checkBox;
    } else if(param.attribute("type") == "enumeration") {
        QComboBox *comboBox = new QComboBox(parametersGroup);
        QDomElement value = param.firstChildElement();
        while(!value.isNull()) {
            comboBox->addItem(value.text());
            value = value.nextSiblingElement();
        }
        int id = comboBox->findText(param.attribute("value"));
        comboBox->setCurrentIndex(id);
        connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setEdited()));
        return comboBox;
    } else if(param.attribute("type") == "string") {
        QLineEdit *lineEdit = new QLineEdit(parametersGroup);
        lineEdit->setText(param.attribute("value"));
        connect(lineEdit, SIGNAL(textEdited(QString)), this, SLOT(setEdited()));
        return lineEdit;
    } else {
        return 0;
    }
}

QLabel *NetworkConfigurator::labelFor(const QDomElement &param) const
{
    QLabel *label = new QLabel(parametersGroup);
    label->setText(param.attribute("description") + ":");
    label->setWordWrap(true);
    return label;
}

bool NetworkConfigurator::setValue(QDomElement &param, int num)
{
    if(parametersLayout->count() <= num) {
        return false;
    }

    if(param.attribute("type") == "integer") {
        QSpinBox *spinBox = static_cast<QSpinBox*>(parametersLayout->itemAt(num)->layout()->itemAt(1)->widget());
        param.setAttribute("min", spinBox->minimum());
        param.setAttribute("max", spinBox->maximum());
        param.setAttribute("value", spinBox->value());
    } else if(param.attribute("type") == "boolean") {
        QCheckBox *checkBox = static_cast<QCheckBox*>(parametersLayout->itemAt(num)->layout()->itemAt(1)->widget());
        param.setAttribute("value", (int)checkBox->isChecked());
    } else if(param.attribute("type") == "enumeration") {
        QComboBox *comboBox = static_cast<QComboBox*>(parametersLayout->itemAt(num)->layout()->itemAt(1)->widget());
        param.setAttribute("value", comboBox->currentText());
    } else if(param.attribute("type") == "string") {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(parametersLayout->itemAt(num)->layout()->itemAt(1)->widget());
        param.setAttribute("value", lineEdit->text());
    }
    return true;
}

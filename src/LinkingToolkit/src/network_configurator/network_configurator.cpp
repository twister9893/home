#include "network_configurator.h"

#include <QPluginLoader>
#include <QDir>
#include <QSpinBox>
#include <QCheckBox>
#include <QDebug>

NetworkConfigurator::NetworkConfigurator(QWidget *parent) :
    FileEditor(parent)
{
    setupUi(this);

    connect(openButton, SIGNAL(clicked()), this, SLOT(openConfig()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveConfig()));
    connect(defaultButton, SIGNAL(clicked()), this, SLOT(setConfigDefault()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));
    connect(protocolCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setConfigDefault(int)));

    loadPlugins();
}

void NetworkConfigurator::openConfig()
{
    open();
}

void NetworkConfigurator::saveConfig()
{
    save();
}

void NetworkConfigurator::quit()
{
    close();
    exit(0);
}

void NetworkConfigurator::setConfigDefault()
{
    setConfigDefault(protocolCombo->currentIndex());
}

void NetworkConfigurator::setConfigDefault(int id)
{
    if(id < 0 || id >= _protocols.size())
        return;
    QString xml = _protocols.at(id)->configure();
    constructWindow(xml);
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
        setValue(_config, param, num);
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

void NetworkConfigurator::clear()
{

}

void NetworkConfigurator::loadPlugins()
{
    qDebug() << "Loading plugins...";
    _protocols.clear();
    protocolCombo->clear();
    QDir pluginsDir( "../lib/" );
    QStringList entryList = pluginsDir.entryList(QDir::Files);
    for(int i = 0; i < entryList.size(); i++) {
        QString pluginName = entryList.at(i);
        QPluginLoader loader(pluginsDir.absoluteFilePath(pluginName));

        if(loader.load()) {
            if(Protocol* protocol = qobject_cast<Protocol*>(loader.instance())) {
                _protocols.push_back(protocol);
                protocolCombo->addItem(protocol->name());
                qDebug() << "[OK]" << pluginName;
            } else {
                qDebug() << "Skip" << pluginName;
            }
            loader.unload();
        } else {
            qCritical() << "[ERROR]" << pluginName;
            qCritical() << loader.errorString();
        }
    }
}

void NetworkConfigurator::constructWindow(const QDomDocument &config)
{
    clearWindow();

    if(config.isNull()) {
        qCritical() << "Can't construct window, bad config";
        return;
    }

    QDomElement domRoot = config.documentElement();
    if(domRoot.tagName() != "config") {
        qCritical() << "Can't construct window from config, incorrect root tag name" << domRoot.tagName();
        return;
    }

    int id = protocolCombo->findText(domRoot.attribute("protocol"));
    protocolCombo->setCurrentIndex(id);
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
        if(!param.attribute("max").isEmpty())
            spinBox->setMaximum(param.attribute("max").toInt());
        spinBox->setValue(param.attribute("value").toInt());
        return spinBox;
    } else if(param.attribute("type") == "boolean") {
        QCheckBox *checkBox = new QCheckBox(parametersGroup);
        checkBox->setChecked(param.attribute("value").toInt());
        return checkBox;
    } else if(param.attribute("type") == "enumeration") {
        QComboBox *comboBox = new QComboBox(parametersGroup);
        QDomElement value = param.firstChildElement();
        while(!value.isNull()) {
            comboBox->addItem(value.text());
            value = value.nextSiblingElement();
        }
        comboBox->setCurrentIndex(param.attribute("value").toInt());
        return comboBox;
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

bool NetworkConfigurator::setValue(QDomDocument &doc, QDomElement &param, int num)
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
        param.setAttribute("value", comboBox->currentIndex());
    }
    return true;
}

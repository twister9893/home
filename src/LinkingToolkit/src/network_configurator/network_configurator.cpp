#include "network_configurator.h"

#include <QPluginLoader>
#include <QDir>
#include <QSpinBox>
#include <QCheckBox>
#include <QDebug>

NetworkConfigurator::NetworkConfigurator(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(protocolCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(showConfig(int)));

    loadProtocols();
}

void NetworkConfigurator::showConfig(int id)
{
    //Очистка области параметров
    QLayoutItem *item;
    while( (item = parametersLayout->itemAt(0)) )
    {
            parametersLayout->removeItem(item);
            parametersLayout->removeWidget(item->widget());
            delete item->widget();
            delete item;
//            parametersLayout->update();
    }

    //Загрузка конфигурационного файла
    QDomDocument config;
    QString errorMsg;
    int errorLine;
    int errorColumn;
    if(!config.setContent(_protocols.at(id)->configure(), &errorMsg, &errorLine, &errorColumn)) {
        qCritical() << "Can't read config for" << _protocols.at(id)->name();
        qCritical() << "Line:" << errorLine << "Colunm:" << errorColumn;
        qCritical() << errorMsg;

        QLabel *errorLabel = new QLabel(parametersGroup);
        errorLabel->setText(QString::fromUtf8("Ошибка чтения конфигурационного файла"));
        parametersLayout->addWidget(errorLabel);
        return;
    }

    //Заполнение области параметров
    QDomElement domRoot = config.documentElement();
    if(domRoot.tagName() != "config") {
        qCritical() << "Can't read config, incorrect root tag name" << domRoot.tagName();
        return;
    }

    QDomElement param = domRoot.firstChildElement();
    while(!param.isNull()) {
        QHBoxLayout *row = new QHBoxLayout();
        row->addWidget(labelFor(param), 2);
        row->addWidget(editorFor(param), 1);
        param = param.nextSiblingElement();
        parametersLayout->addLayout(row);
    }
}

void NetworkConfigurator::loadProtocols()
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

QWidget *NetworkConfigurator::editorFor(QDomElement param)
{
    if(param.attribute("type") == "integer") {
        QSpinBox *spinBox = new QSpinBox(parametersGroup);
        if(!param.attribute("min").isEmpty())
            spinBox->setMinimum(param.attribute("min").toInt());
        if(!param.attribute("max").isEmpty())
            spinBox->setMaximum(param.attribute("max").toInt());
        spinBox->setValue(param.text().toInt());
        return spinBox;
    } else if(param.attribute("type") == "boolean") {
        QCheckBox *checkBox = new QCheckBox(parametersGroup);
        checkBox->setChecked(param.text().toInt());
        return checkBox;
    } else if(param.attribute("type") == "enumeration") {
        QComboBox *comboBox = new QComboBox(parametersGroup);
        QDomElement value = param.firstChildElement();
        while(!value.isNull()) {
            comboBox->addItem(value.text());
            value = value.nextSiblingElement();
        }
        comboBox->setCurrentIndex(param.text().toInt());
        return comboBox;
    } else {
        return 0;
    }
}

QLabel *NetworkConfigurator::labelFor(QDomElement param)
{
    QLabel *label = new QLabel(parametersGroup);
    label->setText(param.attribute("description") + ":");
    label->setWordWrap(true);
    return label;
}

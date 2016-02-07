#include <QDebug>

#include "linkingtools.h"

LinkingTools::LinkingTools(QWidget *parent) :
    QDialog(parent) {
    setupUi(this);
    m_formularEditor = NULL;

    extern QStringList g_fieldTypes;
    extern QStringList g_fieldDimensions;
    extern QStringList g_capacities;
    extern QStringList g_formularHeaderSections;
    extern QStringList g_enumerationHeaderSections;

    g_fieldTypes    << QString::fromUtf8("Целое")
                    << QString::fromUtf8("Дробное")
                    << QString::fromUtf8("Масштабируемое")
                    << QString::fromUtf8("Перечисляемое")
                    << QString::fromUtf8("Константное")
                    << QString::fromUtf8("Логическое")
                    << QString::fromUtf8("Строковое")
                    << QString::fromUtf8("Неиспользуемое");

    g_fieldDimensions   << QString::fromUtf8("Метры")
                        << QString::fromUtf8("Километры")
                        << QString::fromUtf8("Мили")
                        << QString::fromUtf8("Метры в секунду")
                        << QString::fromUtf8("Узлы")
                        << QString::fromUtf8("Секунды")
                        << QString::fromUtf8("Микросекунды")
                        << QString::fromUtf8("Градусы")
                        << QString::fromUtf8("ТД")
                        << QString::fromUtf8("Радианы")
                        << QString::fromUtf8("Нет");

    g_capacities    << QString::number(8)
                    << QString::number(16)
                    << QString::number(32);

    g_formularHeaderSections    << QString::fromUtf8("Размер")
                                << QString::fromUtf8("Тип")
                                << QString::fromUtf8("Наименование")
                                << QString::fromUtf8("Описание");

    g_enumerationHeaderSections << QString::fromUtf8("Код")
                                << QString::fromUtf8("Наименование")
                                << QString::fromUtf8("Описание");

    loadModules();

    connect(formularEditorButton, SIGNAL(released()), this, SLOT(slot_openFormularEditor()));
}

void LinkingTools::loadModules() {
    if(m_formularEditor != NULL) {
        delete m_formularEditor;
    }
    m_formularEditor = new FormularEditor(this);
    if(m_formularEditor != NULL) {
        qDebug() << "[Global] Loading modules: Formular editor\t[OK]";
    } else {
        qCritical() << "[Global] Loading modules: Formular editor\t[ERROR]";
    }
}

void LinkingTools::slot_openFormularEditor() {
    m_formularEditor->show();
}

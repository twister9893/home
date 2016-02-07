#ifndef FORMULAREDITOR_H
#define FORMULAREDITOR_H

#include <QtXml>

#include "../abstractfileeditor.h"
#include "../fielddata.h"
#include "../formularmodel.h"
#include "../formulardelegate.h"
#include "ui_formulareditor.h"

class FormularEditor : public AbstractFileEditor, Ui::FormularEditor {
    Q_OBJECT
public:
    explicit FormularEditor(QWidget *parent = 0);

public slots:
    void slot_addField(QAction *type);
    void slot_removeField();
    void slot_separateFields();

private:
    bool readFromFile(QString fileName);
    bool writeToFile(QString fileName);
    void clearAll();

    QList<QAction*>         m_fieldTypeActions;
    QList<FieldData*>       m_formularData;
    FormularModel           *m_formularModel;
    FormularDelegate        *m_formularDelegate;
    bool m_isEdited;

    static const QStringList m_capacities;

    int m_defaultRowHeight;
    int m_defaultCapacity;
    int m_defaultFieldSize;
    FieldData::Type m_defaultFieldType;
    FieldData::Dimension m_defaultFieldDimension;
    double m_defaultHighOrderBit;
    double m_defaultLowerOrderBit;
    bool m_defaultAdditionalCodeState;
    bool m_defaultHighBitSignState;
    bool m_defaultEnumerationCode;
};

#endif // FORMULAREDITOR_H

#ifndef FORMULAREDITOR_H
#define FORMULAREDITOR_H

#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtXml>

#include "fielddata.h"
#include "formularmodel.h"
#include "formulardelegate.h"
#include "ui_formulareditor.h"

class FormularEditor : public QMainWindow, Ui::FormularEditor {
    Q_OBJECT
    public:
        explicit FormularEditor(QWidget *parent = 0);

    public slots:
        void slot_createFormular();
        void slot_openFormular();
        void slot_saveFormular();
        void slot_saveFormularAs();
        void slot_close();
        void slot_addField(QAction *type);
        void slot_removeField();
        void slot_setEditFlag();
        void slot_separateFields();

    protected:
        virtual void closeEvent(QCloseEvent *);

    private:
        bool readFromFile(QString fileName);
        bool writeToFile(QString fileName);
        void clearAll();
        bool showSaveMessage();
        void setEditFlag(bool isEdited);

        QList<QAction*>         m_fieldTypeActions;
        QList<FieldData*>       m_formularData;
        FormularModel           *m_formularModel;
        FormularDelegate        *m_formularDelegate;
        QFileInfo               m_formularFileInfo;
        bool m_isEdited;

        QString m_defaultDirectory;
        int m_defaultRowHeight;
        int m_defaultCapacity;
        int m_defaultFieldSize;
        FieldType m_defaultFieldType;
        FieldDimension m_defaultFieldDimension;
        double m_defaultHighOrderBit;
        double m_defaultLowerOrderBit;
        bool m_defaultAdditionalCodeState;
        bool m_defaultHighBitSignState;
        bool m_defaultEnumerationCode;
};

#endif // FORMULAREDITOR_H

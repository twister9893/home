#include "enumerationdelegate.h"

EnumerationDelegate::EnumerationDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

QWidget* EnumerationDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const {
    QWidget* editor = NULL;
    EnumerationHeaderSection section = (EnumerationHeaderSection)index.column();
    switch(section) {
        case Code: {
            QSpinBox *spinEditor = new QSpinBox(parent);
            spinEditor->setMinimum(0);
            spinEditor->setMaximum(9999999);
            editor = spinEditor;
            break;
        }
        case Acronym:
        case Transcript: {
            QLineEdit *lineEditor = new QLineEdit(parent);
            editor = lineEditor;
            break;
        }
    }
    extern QStringList g_enumerationHeaderSections;
    if(editor != NULL) {
        qDebug() << "[Enumeration delegate] Create editor: For" << g_enumerationHeaderSections.at(section) << "section\t[OK]";
    } else {
        qCritical() << "[Enumeration delegate] Create editor: For" << g_enumerationHeaderSections.at(section) << "section\t[ERROR]";
    }
    return editor;
}

void EnumerationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    extern QStringList g_enumerationHeaderSections;
    EnumerationHeaderSection section = (EnumerationHeaderSection)index.column();
    if(editor != NULL) {
        switch(section) {
            case Code: {
                QSpinBox *spinEditor = static_cast<QSpinBox*>(editor);
                spinEditor->setValue(index.data(Qt::EditRole).toInt());
                break;
            }
            case Acronym:
            case Transcript: {
                QLineEdit *lineEditor = static_cast<QLineEdit*>(editor);
                lineEditor->setText(index.data(Qt::EditRole).toString());
                break;
            }
        }
        qDebug() << "[Enumeration delegate] Set editor data: For" << g_enumerationHeaderSections.at(section) << "section\t[OK]";
    }
    else {
        qCritical() << "[Enumeration delegate] Set editor data: For" << g_enumerationHeaderSections.at(section) << "section\t[ERROR]";
    }
}

void EnumerationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    EnumerationHeaderSection section = (EnumerationHeaderSection)index.column();
    switch(section) {
        case Code: {
            QSpinBox *spinEditor = static_cast<QSpinBox*>(editor);
            model->setData(index, QVariant(spinEditor->value()));
            break;
        }
        case Acronym:
        case Transcript: {
            QLineEdit *lineEditor = static_cast<QLineEdit*>(editor);
            model->setData(index, QVariant(lineEditor->text()));
            break;
        }
    }
}

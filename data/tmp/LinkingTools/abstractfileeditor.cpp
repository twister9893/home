#include <QFileDialog>

#include "abstractfileeditor.h"

AbstractFileEditor::AbstractFileEditor(QWidget *parent)
    : QMainWindow(parent) {
    m_defaultDirectory = "./";
}

void AbstractFileEditor::slot_createFormular() {
    bool isCancel = showSaveMessage();
    if(!isCancel) {
        m_formularFileInfo.setFile("");
        clearAll();
    }
}

void AbstractFileEditor::slot_open() {
    bool isCancel = showSaveMessage();
    if(!isCancel) {
        QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), m_defaultDirectory, "Xml documents (*.xml);;All files (*.*)");
        if(!fileName.isEmpty()) {
            clearAll();
            bool isSuccess = readFromFile(fileName);
            if(isSuccess) {
                m_fileInfo.setFile(fileName);
                qDebug() << "[File editor] File has been opened" << m_fileInfo.filePath();
                setEditFlag(false);
            } else {
                qCritical() << "[File editor] File has not been opened";
            }
        }
    }
}

void AbstractFileEditor::slot_saveFormular() {
    if(m_fileInfo.isFile()) {
        bool isSuccess = writeToFile(m_fileInfo.filePath());
        if(isSuccess) {
            qDebug() << "[File editor] File has been saved" << m_fileInfo.filePath();
            setEditFlag(false);
        } else {
            qCritical() << "[File editor] File has not been saved" << m_fileInfo.filePath();
        }
    }
    else {
        slot_saveAs();
    }
}

void AbstractFileEditor::slot_saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), m_defaultDirectory + ".xml", "Xml file (*.xml)");
    if(!fileName.isEmpty()) {
        m_fileInfo.setFile(fileName);
        bool isSuccess = writeToFile(m_fileInfo.filePath());
        if(isSuccess) {
            qDebug() << "[File editor] File has been saved" << m_fileInfo.filePath();
            setEditFlag(false);
        } else {
            qCritical() << "[File editor] File has not been saved" << m_fileInfo.filePath();
        }
    }
}

void AbstractFileEditor::slot_quit() {
    bool isCancel = showSaveMessage();
    if(!isCancel) {
        clearAll();
        exit(0);
    }
}

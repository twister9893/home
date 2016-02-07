#ifndef FEDIT_H
#define FEDIT_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

class FileEditor : public QMainWindow {
public:
    FileEditor(QWidget *parent) : QMainWindow(parent), m_defaultDir("./"), m_isEdited(false) {}
    virtual ~FileEditor();

    void setDefaultDir(QString defaultDir) {m_defaultDir = defaultDir;}

public slots:
    void create() {
        bool isCancel = showSaveMessage();
        if(!isCancel) {
            clear();
        }
    }

    void open() {
        bool isCancel = showSaveMessage();
        if(!isCancel) {
            QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), m_defaultDir, "*.xml");
            if(!fileName.isEmpty()) {
                clear();
                bool isSuccess = readFromFile(fileName);
                if(isSuccess) {
                    m_info.setFile(fileName);
                    m_isEdited = false;
                }
            }
        }
    }

    void save() {
        if(m_info.isFile()) {
            bool isSuccess = writeToFile(m_info.filePath());
            if(isSuccess) {
                m_isEdited = false;
            }
        }
        else {
            saveAs();
        }
    }

    void saveAs() {
        QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), m_defaultDir, "*.xml");
        if(!fileName.isEmpty()) {
            m_info.setFile(fileName);
            bool isSuccess = writeToFile(m_info.filePath());
            if(isSuccess) {
                m_isEdited = false;
            }
        }
    }

    void close() {
        bool isCancel = showSaveMessage();
        if(!isCancel) {
            clear();
        }
    }

    void setEdited() {m_isEdited = true;}

protected:
    virtual bool readFromFile(QString fileName)=0;
    virtual bool writeToFile(QString fileName)=0;
    virtual void clear() {
        m_info.setFile(QString());
        m_isEdited = false;
    }

    bool showSaveMessage() {
        int answer = QMessageBox::No;
        if(m_isEdited) {
            answer = QMessageBox::question(this, QString::fromUtf8("Сохранить"), QString::fromUtf8("Сохранить изменения в файле?\n") + m_info.filePath(), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
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

    QFileInfo m_info;
    QString m_defaultDir;
    bool m_isEdited;
};

#endif // FEDIT_H

#ifndef FEDIT_H
#define FEDIT_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

class FileEditor : public QWidget {
public:
    FileEditor(QWidget *parent) : QWidget(parent), _defaultDir("./"), _isEdited(false) {}
    virtual ~FileEditor() {}

    void setDefaultDir(QString defaultDir) {_defaultDir = defaultDir;}

public:
    void create() {
        bool isCancel = showSaveMessage();
        if(!isCancel) {
            clear();
        }
    }

    void open() {
        bool isCancel = showSaveMessage();
        if(!isCancel) {
            QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), _defaultDir, "*.xml");
            if(!fileName.isEmpty()) {
                clear();
                bool isSuccess = readFromFile(fileName);
                if(isSuccess) {
                    _info.setFile(fileName);
                    _isEdited = false;
                }
            }
        }
    }

    void save() {
        if(_info.isFile()) {
            bool isSuccess = writeToFile(_info.filePath());
            if(isSuccess) {
                _isEdited = false;
            }
        }
        else {
            saveAs();
        }
    }

    void saveAs() {
        QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), _defaultDir, "*.xml");
        if(!fileName.isEmpty()) {
            _info.setFile(fileName);
            bool isSuccess = writeToFile(_info.filePath());
            if(isSuccess) {
                _isEdited = false;
            }
        }
    }

    void close() {
        bool isCancel = showSaveMessage();
        if(!isCancel) {
            clear();
        }
    }

    void setEdited() {_isEdited = true;}

protected:
    virtual bool readFromFile(const QString &fileName)=0;
    virtual bool writeToFile(const QString &fileName)=0;
    virtual void clear() {
        _info.setFile(QString());
        _isEdited = false;
    }

    bool showSaveMessage() {
        int answer = QMessageBox::No;
        if(_isEdited) {
            answer = QMessageBox::question(this, QString::fromUtf8("Сохранить"), QString::fromUtf8("Сохранить изменения в файле?\n") + _info.filePath(), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
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

    QFileInfo _info;
    QString _defaultDir;
    bool _isEdited;
};

#endif // FEDIT_H

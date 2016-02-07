#ifndef ABSTRACTFILEEDITOR_H
#define ABSTRACTFILEEDITOR_H

#include <QMainWindow>
#include <QFileInfo>

class AbstractFileEditor : public QMainWindow {
    Q_OBJECT
public:
    explicit AbstractFileEditor(QWidget *parent = 0);
    virtual ~AbstractFileEditor() {}
    void setDefaultDirectory(QString defaultDirectory) {m_defaultDirectory = defaultDirectory;}

public slots:
    void slot_create();
    void slot_open();
    void slot_save();
    void slot_saveAs();
    void slot_setEditFlag();
    void slot_quit();

protected:
    virtual bool readFromFile(QString fileName) = 0;
    virtual bool writeToFile(QString fileName) = 0;
    virtual void clearAll() = 0;
    bool showSaveMessage();
    void setEditFlag(bool isEdited);

private:
    QString m_defaultDirectory;
    QFileInfo m_fileInfo;
    bool m_isEdited;
};

#endif // ABSTRACTFILEEDITOR_H

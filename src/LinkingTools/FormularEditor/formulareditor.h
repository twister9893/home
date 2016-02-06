#ifndef FORMULAREDITOR_H
#define FORMULAREDITOR_H

#include <QMainWindow>
#include "fedit.h"

namespace Ui {
class FormularEditor;
}

class FormularEditor : public QMainWindow, public FileEditor {
    Q_OBJECT
public:
    explicit FormularEditor(QWidget *parent = 0);
    ~FormularEditor();

private:
    bool readFromFile(QString fileName);
    bool writeToFile(QString fileName);

    Ui::FormularEditor *ui;
};

#endif // FORMULAREDITOR_H

#ifndef FORMULAREDITOR_H
#define FORMULAREDITOR_H

#include <QMainWindow>

namespace Ui {
class FormularEditor;
}

class FormularEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormularEditor(QWidget *parent = 0);
    ~FormularEditor();

private:
    Ui::FormularEditor *ui;
};

#endif // FORMULAREDITOR_H

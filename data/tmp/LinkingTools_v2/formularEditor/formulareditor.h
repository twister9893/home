#ifndef FORMULAREDITOR_H
#define FORMULAREDITOR_H

#include "ui_formulareditor.h"

class FormularEditor : public QMainWindow, private Ui::FormularEditor
{
    Q_OBJECT

public:
    explicit FormularEditor(QWidget *parent = 0);
};

#endif // FORMULAREDITOR_H

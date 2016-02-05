#include "formulareditor.h"
#include "ui_formulareditor.h"

FormularEditor::FormularEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormularEditor)
{
    ui->setupUi(this);
}

FormularEditor::~FormularEditor()
{
    delete ui;
}

#ifndef FIELDDATAEDITOR_H
#define FIELDDATAEDITOR_H

#include <QWidget>
#include <QCloseEvent>
#include <QDebug>
#include "ui_fielddataeditor.h"

class FieldDataEditor : public QWidget, public Ui::FieldDataEditor {
Q_OBJECT
public:
    explicit FieldDataEditor(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void reject();
    void accept();
};

#endif // FIELDDATAEDITOR_H

#ifndef ENUMERATIONWIDGET_H
#define ENUMERATIONWIDGET_H

#include <QWidget>
#include "ui_enumerationwidget.h"

class EnumerationWidget : public QWidget, public Ui::EnumerationWidget
{
    Q_OBJECT
public:
    explicit EnumerationWidget(QWidget *parent = 0);
};

#endif // ENUMERATIONWIDGET_H

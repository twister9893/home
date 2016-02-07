#ifndef CONSTANTWIDGET_H
#define CONSTANTWIDGET_H

#include <QWidget>
#include "ui_constantwidget.h"

class ConstantWidget : public QWidget, public Ui::ConstantWidget
{
    Q_OBJECT
public:
    explicit ConstantWidget(QWidget *parent = 0); 
};

#endif // CONSTANTWIDGET_H

#ifndef SCALABLEWIDGET_H
#define SCALABLEWIDGET_H

#include <QWidget>
#include "ui_scalablewidget.h"

class ScalableWidget : public QWidget, public Ui::ScalableWidget
{
    Q_OBJECT
public:
    explicit ScalableWidget(QWidget *parent = 0); 
};

#endif // SCALABLEWIDGET_H

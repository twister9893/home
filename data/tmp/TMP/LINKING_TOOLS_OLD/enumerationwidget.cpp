#include "enumerationwidget.h"

EnumerationWidget::EnumerationWidget(QWidget *parent)
    : QWidget(parent) {
    setupUi(this);
    tableView->verticalHeader()->setDefaultSectionSize(20);
}

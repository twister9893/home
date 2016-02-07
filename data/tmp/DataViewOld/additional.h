#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include <QDomElement>
#include <QStandardItem>

void buildStandardTree(QStandardItem *parentItem, QDomElement parentDom, int *columnCount);
QDomElement getElementAt(int column, int currentColumn, QDomElement parentDom);

#endif // ADDITIONAL_H

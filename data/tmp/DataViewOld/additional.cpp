#include "additional.h"

void buildStandardTree(QStandardItem *parentItem, QDomElement parentDom, int *columnCount) {
	for(int i = 0; i < parentDom.childNodes().size(); i++) {
		QDomElement childDom = parentDom.childNodes().at(i).toElement();
		QStandardItem *childItem = new QStandardItem(childDom.attribute("name"));
		//childItem->setToolTip(childDom.attribute("description", childDom.attribute("name")));
		//childItem->setData(childDom.attribute("name"), Qt::DisplayRole);
		childItem->setData(childDom.attribute("description", childDom.attribute("name")), Qt::ToolTipRole);
		if(childDom.hasChildNodes()) {
			buildStandardTree(childItem, childDom, columnCount);
		} else {
			(*columnCount)++;
		}
		parentItem->appendColumn(QList<QStandardItem*>() << childItem);
	}
}

QDomElement getElementAt(int column, int currentColumn, QDomElement parentDom) {
	for(int i = 0; i < parentDom.childNodes().size(); i++) {
		QDomElement childDom = parentDom.childNodes().at(i).toElement();
		if(childDom.hasChildNodes()) {
			return getElementAt(column, currentColumn, childDom);
		} else {
			if(column == currentColumn) {
				currentColumn = 0;
				return childDom;
			}
			currentColumn++;
		}
	}
}

#include "xmlparser.h"

#include <QFile>
#include <QDebug>

QDomDocument parseXmlFile(QString fileName) {
	QString errorString;
	int errorLine;
	int errorColumn;
	QFile file(fileName);
	QDomDocument domDocument;

	if(!file.open(QIODevice::ReadOnly)) {
		return QDomDocument();
	}
	if(!domDocument.setContent(&file, true, &errorString, &errorLine, &errorColumn)) {
		qWarning() << "[Xml parser]\tLine " << errorLine << "colunm " << errorColumn << " message ";
	}
	file.close();
	return domDocument;
}

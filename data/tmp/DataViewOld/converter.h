#ifndef CONVERTER_H
#define CONVERTER_H

#include "xmlparser.h"
#include <QStringList>

enum ColumnType {
	ColumnType_Int = 0,
	ColumnType_Float,
	ColumnType_Scalable,
	ColumnType_Enumeration,
	ColumnType_Constant,
	ColumnType_Logical,
	ColumnType_String,
	ColumnType_Unused
};
enum ColumnMask {
	ColumnMask_Regular = 0,
	ColumnMask_Time,
	ColumnMask_Date,
	ColumnMask_Latitude,
	ColumnMask_Longitude
};

const QStringList columnTypes(QStringList()	<< "INT"
											<< "FLOAT"
											<< "SCAL"
											<< "ORDIN"
											<< "CONST"
											<< "LOGIC"
											<< "SYMB"
											<< "UN");

const QStringList columnMasks(QStringList()	<< "REGULAR"
											<< "TIME"
											<< "DATE"
											<< "LATITUDE"
											<< "LONGITUDE");

QStringList convertData(QVariant data, QString formularFileName, QString fieldName, QString mask);
QDomElement getFormularElementNamed(QString fieldName, QString formularFileName);
void insertValueWithRole(QStringList &data, QString value, int role);

#endif // CONVERTER_H

#include "converter.h"

#include <QVariant>
#include <QPixmap>
#include <QDateTime>
#include <QDebug>

#include "../include/qcoordstring.h"
extern "C" {
	#include "../include/glob_mat.h"
}

QStringList convertData(QVariant data, QString formularFileName, QString fieldName, QString mask) {
	//qDebug() << "[Converter] Convert data: At" << section;


	QStringList fieldTypes, fieldTypesInXml;
	fieldTypes		<< QString::fromUtf8("Целое")
					<< QString::fromUtf8("Дробное")
					<< QString::fromUtf8("Масштабируемое")
					<< QString::fromUtf8("Перечисляемое")
					<< QString::fromUtf8("Константное")
					<< QString::fromUtf8("Логическое")
					<< QString::fromUtf8("Строковое")
					<< QString::fromUtf8("Неиспользуемое");

	fieldTypesInXml	<< QString::fromUtf8("INT")
					<< QString::fromUtf8("FLOAT")
					<< QString::fromUtf8("SCAL")
					<< QString::fromUtf8("ORDIN")
					<< QString::fromUtf8("CONST")
					<< QString::fromUtf8("LOGIC")
					<< QString::fromUtf8("SYMBOL")
					<< QString::fromUtf8("UN");

	QStringList fieldDimensions, fieldDimensionsInXml;
	fieldDimensions		<< QString::fromUtf8("Метры")
						<< QString::fromUtf8("Километры")
						<< QString::fromUtf8("Мили")
						<< QString::fromUtf8("Футы")
						<< QString::fromUtf8("Метры в секунду")
						<< QString::fromUtf8("Узлы")
						<< QString::fromUtf8("Секунды")
						<< QString::fromUtf8("Микросекунды")
						<< QString::fromUtf8("Градусы")
						<< QString::fromUtf8("ТД")
						<< QString::fromUtf8("Радианы")
						<< QString::fromUtf8("Нет");

	fieldDimensionsInXml<< QString::fromUtf8("M")
						<< QString::fromUtf8("KM")
						<< QString::fromUtf8("ML")
						<< QString::fromUtf8("FOOT")
						<< QString::fromUtf8("MS")
						<< QString::fromUtf8("UZ")
						<< QString::fromUtf8("S")
						<< QString::fromUtf8("MCS")
						<< QString::fromUtf8("GRAD")
						<< QString::fromUtf8("TD")
						<< QString::fromUtf8("RAD")
						<< QString::fromUtf8("NO");


	QStringList convertedData;
	QDomElement fieldDom = getFormularElementNamed(fieldName, formularFileName);
	QString dataTypeFromXml = fieldDom.attribute("type", columnTypes.at(ColumnType_Int));
	//qDebug() << "[Converter] Convert data: Type" << dataTypeFromXml;
	ColumnType dataType = (ColumnType)(columnTypes.indexOf(dataTypeFromXml));
	ColumnMask dataMask = (ColumnMask)(columnMasks.indexOf(mask));
	qDebug() << "CONVERT T : M" << (int)dataType << (int)dataMask;
	QHash<int, QStringList> enumeration;
	if(dataType == ColumnType_Enumeration) {
		QDomElement enumerationElement = fieldDom.firstChildElement();
		while(!enumerationElement.isNull()) {
			QStringList enumerationDescription;
			enumerationDescription << enumerationElement.attribute("acronym") << enumerationElement.attribute("transcript");
			enumeration.insert(enumerationElement.attribute("code").toInt(), enumerationDescription);
			//qDebug() << "[Converter] Convert data: Read enum" << enumerationElement.attribute("code").toInt() << enumerationElement.attribute("acronym") << enumerationElement.attribute("transcript");
			enumerationElement = enumerationElement.nextSiblingElement();
		}
	}

	QString toolTip = QString::fromUtf8("Описание:\t%description%dimension\n"
										"Тип:\t%type");
	toolTip.replace("%description", fieldDom.attribute("description"));
	int index = fieldDimensionsInXml.indexOf(fieldDom.attribute("dimension"));
	if(index < fieldDimensions.size() && index >= 0) {
		if(index != fieldDimensions.size() - 1) {
			toolTip.replace("%dimension", ", " + fieldDimensions.at(index));
		} else {
			toolTip.replace("%dimension", QString());
		}
	}
	toolTip.replace("%type", fieldTypes.at(fieldTypesInXml.indexOf(fieldDom.attribute("type"))));

	switch(dataType) {
		case ColumnType_Int: {
			insertValueWithRole(convertedData, data.toString(), Qt::DisplayRole);
			insertValueWithRole(convertedData, toolTip, Qt::ToolTipRole);
			break;
		}
		case ColumnType_Float: {
			double value = data.toDouble();
			insertValueWithRole(convertedData, QString::number(value, 'g', 6), Qt::DisplayRole);

			QString toolTipFloat = QString::fromUtf8("\n\nЗначение:\t%value");
			toolTipFloat.replace("%value", data.toString());
			toolTip.append(toolTipFloat);
			insertValueWithRole(convertedData, toolTip, Qt::ToolTipRole);
			break;
		}
		case ColumnType_Scalable: {
			insertValueWithRole(convertedData, data.toString(), Qt::DisplayRole);

			QString toolTipScalable = QString::fromUtf8("\n\nЦена %order разряда: %value"
														"%sign");
			if(fieldDom.attribute("lowerOrderBit", "0").toInt() != 0) {
				toolTipScalable.replace("%order", QString::fromUtf8("младшего"));
				toolTipScalable.replace("%value", fieldDom.attribute("lowerOrderBit"));
			} else if(fieldDom.attribute("highOrderBit", "0").toInt() != 0) {
				toolTipScalable.replace("%order", QString::fromUtf8("старшего"));
				toolTipScalable.replace("%value", fieldDom.attribute("highOrderBit"));
			} else {
				toolTipScalable.clear();
			}

			if(fieldDom.attribute("additionalCode", "0").toInt() != 0) {
				toolTipScalable.replace("%sign", QString::fromUtf8("\nЗнак в дополнительном коде"));
			} else if(fieldDom.attribute("highOrderBitSign", "0").toInt() != 0) {
				toolTipScalable.replace("%sign", QString::fromUtf8("\nЗнак в старшем разряде"));
			} else {
				toolTipScalable.replace("%sign", QString());
			}
			toolTip.append(toolTipScalable);
			break;
		}
		case ColumnType_Enumeration: {
			QStringList description = enumeration.value(data.toInt());
			if(description.size() == 2) {
				insertValueWithRole(convertedData, description.at(0), Qt::DisplayRole);
			} else {
				insertValueWithRole(convertedData, data.toString(), Qt::DisplayRole);
			}

			QString toolTipEnumeration = QString::fromUtf8("\n\nЗначение:\t%value");
			if(description.size() == 2) {
				toolTipEnumeration.replace("%value", enumeration.value(data.toInt()).at(1));
			} else {
				toolTipEnumeration.replace("%value", QString::fromUtf8("Ошибка"));
			}
			toolTip.append(toolTipEnumeration);
			insertValueWithRole(convertedData, toolTip, Qt::ToolTipRole);
			break;
		}
		case ColumnType_Constant: {
			insertValueWithRole(convertedData, data.toString(), Qt::DisplayRole);
			insertValueWithRole(convertedData, toolTip, Qt::ToolTipRole);
			break;
		}
		case ColumnType_Logical: {
			if(data.toInt() == 0) {
				insertValueWithRole(convertedData, QString(":/logic/icon/ledgrey32.png"), Qt::DecorationRole);
			} else {
				insertValueWithRole(convertedData, QString(":/logic/icon/ledon32.png"), Qt::DecorationRole);
			}
			insertValueWithRole(convertedData, toolTip, Qt::ToolTipRole);
			break;
		}
		case ColumnType_String: {
			insertValueWithRole(convertedData, data.toString(), Qt::DisplayRole);
			insertValueWithRole(convertedData, toolTip, Qt::ToolTipRole);
			break;
		}
		case ColumnType_Unused: {
			insertValueWithRole(convertedData, data.toString(), Qt::DisplayRole);
			insertValueWithRole(convertedData, toolTip, Qt::ToolTipRole);
			break;
		}
		default: {
			insertValueWithRole(convertedData, QString::fromUtf8("ошибка"), Qt::DisplayRole);
			insertValueWithRole(convertedData, QString::fromUtf8("Неизвестный тип данных"), Qt::ToolTipRole);
			break;
		}
	}

	if(convertedData.size() > Qt::DisplayRole) {
		switch(dataMask) {
			case ColumnMask_Regular: {
				break;
			}
			case ColumnMask_Time: {
				//break;
			}
			case ColumnMask_Date: {
				QDateTime dateTime = QDateTime::fromTime_t(data.toInt());
				convertedData[Qt::DisplayRole] = dateTime.toString("dd.MM.yyyy hh:mm:ss");
				break;
			}
			case ColumnMask_Latitude: {
				convertedData[Qt::DisplayRole] = QCoordString(grad(data.toDouble()), QCoordString::Fi);
				break;
			}
			case ColumnMask_Longitude: {
				convertedData[Qt::DisplayRole] = QCoordString(grad(data.toDouble()), QCoordString::La);
				break;
			}
		}
	}
	qDebug() << "Convert finish:" << fieldName;

	return convertedData;
}

 QDomElement getFormularElementNamed(QString fieldName, QString formularFileName) {
	//qDebug() << "[Converter] Get dom element named:" << name;
	QDomDocument formularDom = parseXmlFile(formularFileName);
	QDomElement domElementNamed;
	QDomElement word = formularDom.firstChildElement().firstChildElement();
	while(!word.isNull()) {
		bool isFound = false;
		QDomElement field = word.firstChildElement();
		while(!field.isNull()) {
			if(field.attribute("name") == fieldName) {
				domElementNamed = field;
				isFound = true;
				break;
			}
			field = field.nextSiblingElement();
		}
		if(isFound) {
			break;
		}
		word = word.nextSiblingElement();
	}

	return domElementNamed;
}

 void insertValueWithRole(QStringList &data, QString value, int role) {
	while(data.size() <= role) {
		data << QString();
	}
	data.replace(role, value);
 }

#include <QDebug>

#include "fielddata.h"

FieldData::FieldData(QString name, QString description, FieldType type, FieldDimension dimension, int size) {
    setName(name);
    setDescription(description);
    setType(type);
    setDimension(dimension);
    setSize(size);
}

void FieldData::setName(QString name) {
    m_name = name;
}

void FieldData::setDescription(QString description) {
    m_description = description;
}

void FieldData::setType(FieldType type) {
    m_type = type;
}

void FieldData::setDimension(FieldDimension dimension) {
    m_dimension = dimension;
}

void FieldData::setSize(int size) {
    m_size = size;
}

QString FieldData::getName() {
    return m_name;
}

QString FieldData::getDescription() {
    return m_description;
}

FieldType FieldData::getType() {
    return m_type;
}

FieldDimension FieldData::getDimension() {
    return m_dimension;
}

int FieldData::getSize() {
    return m_size;
}

FieldScalable::FieldScalable(QString name, QString description, FieldType type, FieldDimension dimension, int size)
    : FieldData(name, description, type, dimension, size) {
    setHighOrderBit(0.0);
    setLowerOrderBit(0.0);
    setAdditionalCode(false);
    setHighBitSign(false);
}

void FieldScalable::setHighOrderBit(double highOrderBit) {
    m_highOrderBit = highOrderBit;
}

void FieldScalable::setLowerOrderBit(double lowerOrderBit) {
	m_lowerOrderBit = lowerOrderBit;
}

void FieldScalable::setAdditionalCode(bool hasAdditionalCode) {
	m_hasAdditionalCode = hasAdditionalCode;
}

void FieldScalable::setHighBitSign(bool hasHighBitSign) {
    m_hasHighBitSign = hasHighBitSign;
}

double FieldScalable::getHighOrderBit() {
    return m_highOrderBit;
}

double FieldScalable::getLowerOrderBit() {
	return m_lowerOrderBit;
}

bool FieldScalable::hasAdditionalCode() {
	return m_hasAdditionalCode;
}

bool FieldScalable::hasHighBitSign() {
    return m_hasHighBitSign;
}

FieldEnumeration::FieldEnumeration(QString name, QString description, FieldType type, FieldDimension dimension, int size)
    :FieldData(name, description, type, dimension, size) {
    m_enumerationModel = new EnumerationModel(m_enumeration, this);
    m_enumerationDelegate = new EnumerationDelegate(this);
}

EnumerationModel* FieldEnumeration::getModel() {
    return m_enumerationModel;
}

EnumerationDelegate* FieldEnumeration::getDelegate() {
    return m_enumerationDelegate;
}

void FieldEnumeration::slot_addElement() {
    m_enumerationModel->insertRow(m_enumerationModel->rowCount());
}

void FieldEnumeration::slot_removeLastElement() {
    m_enumerationModel->removeRow(m_enumerationModel->rowCount() - 1);
}

FieldConstant::FieldConstant(QString name, QString description, FieldType type, FieldDimension dimension, int size)
    : FieldData(name, description, type, dimension, size) {
    setValue(QString());
}

void FieldConstant::setValue(QString value) {
	m_value = value;
}

QString FieldConstant::getValue() {
	return m_value;
}

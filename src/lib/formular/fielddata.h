#ifndef FIELDDATA_H
#define FIELDDATA_H

#include <QStringList>

class FieldData {
public:
    enum Type {
        Integer = 0,
        Real,
        Scalable,
        Enumeration,
        Constant,
        Boolean,
        String,
        Unused
    };

    enum Dimension {
        Meters = 0,
        kMeters,
        Miles,
        MetersPerSecond,
        Knots,
        Seconds,
        mcSeconds,
        Degrees,
        TD,
        Radians,
        No
    };

    FieldData()
        : m_size(0) {}
    FieldData(QString name, QString description = QString(), FieldData::Type type = Integer, FieldData::Dimension dimension = No, int size = 1)
        : m_name(name), m_description(description), m_type(type), m_dimension(dimension), m_size(size) {}

    void setName(QString name) {m_name = name;}
    void setDescription(QString description) {m_description = description;}
    void setType(FieldData::Type type) {m_type = type;}
    void setDimension(FieldData::Dimension dimension) {m_dimension = dimension;}
    void setSize(int size) {m_size = size;}

    QString getName() {return m_name;}
    QString getDescription() {return m_description;}
    FieldData::Type getType() {return m_type;}
    FieldData::Dimension getDimension() {return m_dimension;}
    int getSize() {return m_size;}

    static const QStringList types;
    static const QStringList dimensions;

protected:
    QString m_name;
    QString m_description;
    FieldData::Type m_type;
    FieldData::Dimension m_dimension;
    int m_size;
};

class FieldScalable : public FieldData {
public:
    FieldScalable()
        : FieldData(), m_highOrderBit(0.0), m_lowerOrderBit(0.0), m_hasAdditionalCode(false), m_hasHighBitSign(false) {}
    FieldScalable(QString name = QString(), QString description = QString(), FieldData::Type type = Scalable, FieldData::Dimension dimension = No, int size = 1)
        : FieldData(name,description,type,dimension,size), m_highOrderBit(0.0), m_lowerOrderBit(0.0), m_hasAdditionalCode(false), m_hasHighBitSign(false) {}

    void setHighOrderBit(double highOrderBit) {m_highOrderBit = highOrderBit;}
    void setLowerOrderBit(double lowerOrderBit) {m_lowerOrderBit = lowerOrderBit;}
    void setAdditionalCode(bool hasAdditionalCode) {m_hasAdditionalCode = hasAdditionalCode;}
    void setHighBitSign(bool hasHighBitSign) {m_hasHighBitSign = hasHighBitSign;}

    double getHighOrderBit() {return m_highOrderBit;}
    double getLowerOrderBit() {return m_lowerOrderBit;}
    bool hasAdditionalCode() {return m_hasAdditionalCode;}
    bool hasHighBitSign() {return m_hasHighBitSign;}

private:
    double 	m_highOrderBit;
    double 	m_lowerOrderBit;
    bool 	m_hasAdditionalCode;
    bool 	m_hasHighBitSign;
};

class FieldEnumeration : public FieldData {
public:
    class EnumerationElement {
        public:
            EnumerationElement() {}
            EnumerationElement(QString code, QString acronym, QString description = QString())
                : m_code(code), m_acronym(acronym), m_transcript(description) {}

            void setCode(QString code) {m_code = code;}
            void setAcronym(QString acronym) {m_acronym = acronym;}
            void setTranscript(QString transcript) {m_transcript = transcript;}

            QString getCode() {return m_code;}
            QString getAcronym() {return m_acronym;}
            QString getTranscript() {return m_transcript;}
        private:
            QString m_code;
            QString m_acronym;
            QString m_transcript;
    };

    FieldEnumeration()
        : FieldData() {}
    FieldEnumeration(QString name = QString(), QString description = QString(), FieldData::Type type = Enumeration, FieldData::Dimension dimension = No, int size = 1)
        : FieldData(name, description, type, dimension, size) {}

    QList<EnumerationElement> & getElements() {return m_enumeration;}
private:
    QList<EnumerationElement> m_enumeration;
};

class FieldConstant : public FieldData {
public:
    FieldConstant()
        : FieldData() {}
    FieldConstant(QString name = QString(), QString description = QString(), FieldData::Type type = Constant, FieldData::Dimension dimension = No, int size = 1)
        : FieldData(name, description, type, dimension, size) {}

    void setValue(QString value) {m_value = value;}
    QString getValue() {return m_value;}

private:
    QString m_value;
};

#endif // FIELDDATA_H

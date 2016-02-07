#ifndef FIELDDATA_H
#define FIELDDATA_H

#include <QStringList>

#include "enumerationmodel.h"
#include "enumerationdelegate.h"

class FieldData : public QObject {
    Q_OBJECT
    public:
        FieldData(QString name = QString(), QString description = QString(), FieldType type = Integer, FieldDimension dimension = No, int size = 1);

        void setName(QString name);
        void setDescription(QString description);
        void setType(FieldType type);
        void setDimension(FieldDimension dimension);
        void setSize(int size);

        QString getName();
        QString getDescription();
        FieldType getType();
        FieldDimension getDimension();
        int getSize();

    protected:
        QString m_name;
        QString m_description;
        FieldType m_type;
        FieldDimension m_dimension;
        int m_size;
};

class FieldScalable : public FieldData {
    Q_OBJECT
    public:
        FieldScalable(QString name = QString(), QString description = QString(), FieldType type = Scalable, FieldDimension dimension = No, int size = 1);

        void setHighOrderBit(double highOrderBit);
        void setLowerOrderBit(double lowerOrderBit);
        void setAdditionalCode(bool hasAdditionalCode);
        void setHighBitSign(bool hasHighBitSign);

        double getHighOrderBit();
        double getLowerOrderBit();
        bool hasAdditionalCode();
        bool hasHighBitSign();

    private:
        double 	m_highOrderBit;
        double 	m_lowerOrderBit;
        bool 	m_hasAdditionalCode;
        bool 	m_hasHighBitSign;
};

class FieldEnumeration : public FieldData {
    Q_OBJECT
    public:
        FieldEnumeration(QString name = QString(), QString description = QString(), FieldType type = Enumeration, FieldDimension dimension = No, int size = 1);

        EnumerationElement* getElement(int position);
        int getElementCount();
        EnumerationModel* getModel();
        EnumerationDelegate* getDelegate();

    public slots:
        void slot_addElement();
        void slot_removeLastElement();

    private:
        EnumerationModel *m_enumerationModel;
        EnumerationDelegate *m_enumerationDelegate;
        QList<EnumerationElement*> m_enumeration;
};

class FieldConstant : public FieldData {
    Q_OBJECT
    public:
        FieldConstant(QString name = QString(), QString description = QString(), FieldType type = Constant, FieldDimension dimension = No, int size = 1);

        void setValue(QString value);
        QString getValue();

    private:
        QString m_value;
};

#endif // FIELDDATA_H

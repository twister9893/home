#ifndef FORMULARMODEL_H
#define FORMULARMODEL_H

#include <QAbstractItemModel>
#include "fielddata.h"

class FormularModel : public QAbstractItemModel {
    enum HeaderSection {
        Size = 0,
        Type,
        Name,
        Description
    };

    public:
        FormularModel(QList<FieldData*> &formularData, QObject *parent);

        QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
        QModelIndex parent(const QModelIndex &child) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;
        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent = QModelIndex()) const;
        QVariant data(const QModelIndex &index, int role) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role);
        bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
        bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
        Qt::ItemFlags flags(const QModelIndex &index) const;
        Qt::DropActions supportedDropActions() const;

        static const QStringList formularHeaderSections;

    private:
        QList<FieldData*> m_formularData;
};

#endif // FORMULARMODEL_H

#ifndef ENUMERATIONMODEL_H
#define ENUMERATIONMODEL_H

#include <QAbstractItemModel>
#include <QStringList>

#include "enumerationelement.h"
#include "libenum.h"

class EnumerationModel : public QAbstractItemModel {
    public:
        EnumerationModel(QList<EnumerationElement*> &enumeration, QObject *parent);

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

    private:
        QList<EnumerationElement*> m_enumeration;
};
#endif // ENUMERATIONMODEL_H

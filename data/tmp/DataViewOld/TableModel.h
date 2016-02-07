#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractItemModel>
#include <QList>
#include <QString>

class TableModel : public QAbstractItemModel {
	Q_OBJECT
public:
	TableModel(int columnCount, QObject *parent = 0);

	QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &child) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::EditRole) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	void setHeader(Qt::Orientation orientation, QAbstractItemModel *headerData);
	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	Qt::ItemFlags flags(const QModelIndex &index) const;

	static const QStringList columnTypes;
	static const QStringList columnMasks;

private:
	QAbstractItemModel *m_horizontalHeaderData;
	QList< QList<QVariant> > m_data;
	int m_columnCount;
};

#endif // TABLEMODEL_H

#include "TableModel.h"

#include <QDebug>

#include "hvLib/HierarchicalHeaderView.h"

TableModel::TableModel(int columnCount, QObject *parent)
		: QAbstractItemModel(parent) {
	m_columnCount = columnCount;
	m_horizontalHeaderData = NULL;
}

QModelIndex TableModel::index(int row, int column, const QModelIndex &/*parent*/) const {
	QModelIndex modelIndex;
	if(row >= 0 && row < rowCount() && column >= 0 && column < columnCount()) {
		modelIndex = createIndex(row, column/*, (void*)&(m_data.at(row).at(column))*/);
	}
	return modelIndex;
}

QModelIndex TableModel::parent(const QModelIndex &/*child*/) const {
	return QModelIndex();
}

int TableModel::rowCount(const QModelIndex &/*parent*/) const {
	return m_data.size();
}

int TableModel::columnCount(const QModelIndex &/*parent*/) const {
	return m_columnCount;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
	QVariant outData;
	if(index.isValid()) {
		QStringList data = m_data.at(index.row()).at(index.column()).toStringList();
		//QStringList data;
		//data << m_data.at(index.row()).at(index.column()).toString();
		switch(role) {
			case Qt::ToolTipRole: {
				if(data.size() > Qt::ToolTipRole) {
					outData.setValue(data.at(Qt::ToolTipRole));
				}
				break;
			}
			case Qt::DisplayRole: {
				if(data.size() > Qt::DisplayRole) {
					outData.setValue(data.at(Qt::DisplayRole));
				}
				break;
			}
			case Qt::DecorationRole: {
				if(data.size() > Qt::DecorationRole) {
					outData.setValue(QPixmap(data.at(Qt::DecorationRole)));
				}
				break;
			}
			case Qt::EditRole: {
				outData.setValue(data);
				break;
			}
			default: {
				outData = QVariant();
				break;
			}
		}
	}

	if(role == HierarchicalHeaderView::HorizontalHeaderDataRole && m_horizontalHeaderData != NULL) {
		outData.setValue(static_cast<QObject*>(m_horizontalHeaderData));
	}

	return outData;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
	if(index.isValid() && role == Qt::EditRole) {
		m_data[index.row()][index.column()] = value;
		emit dataChanged(index, index);
		return true;
	} else {
		return false;
	}
}

void TableModel::setHeader(Qt::Orientation orientation, QAbstractItemModel *headerData) {
	switch(orientation) {
		case Qt::Horizontal: {
			if(m_horizontalHeaderData != NULL) {
				delete m_horizontalHeaderData;
			}
			m_horizontalHeaderData = headerData;
			break;
		}
		default: {
			break;
		}
	}
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent) {
	//qDebug() << "[TableModel]\tInsert rows:" << count << "to" << row << "position";
	bool isOk = false;
	if(row >= 0) {
		beginInsertRows(parent, row, row + count - 1);
		for(int i = 0; i < count; i++) {
			qDebug() << "[Table model]\tInsert rows:" << i + 1;
			QList<QVariant> rowData;
			while(rowData.size() != columnCount()) {
				rowData.append(QVariant());
			}
			m_data.insert(row, rowData);
		}
		endInsertRows();
		isOk = true;
	}
	return isOk;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent) {
	//qDebug() << "[TableModel]\tRemove rows:" << count << "from" << row << "position";
	bool isOk = false;
	if(row >= 0 && row + count - 1 < rowCount() && count > 0) {
		beginRemoveRows(parent, row, row + count - 1);
		for(int i = 0; i < count; i++) {
			qDebug() << "[Table model]\tRemove rows:" << i+1;
			m_data.removeAt(row);
		}
		endRemoveRows();
		isOk = true;
	}
	return isOk;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const {
	Qt::ItemFlags flags/* = QAbstractItemModel::flags(index)*/;
	if(index.isValid()) {
		flags = Qt::ItemIsEnabled;
	}
	return flags;
}

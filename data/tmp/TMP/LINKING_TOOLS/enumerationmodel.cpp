#include "enumerationmodel.h"

EnumerationModel::EnumerationModel(QList<EnumerationElement *> &enumeration, QObject *parent)
    : QAbstractItemModel(parent) {
    m_enumeration = enumeration;
}

QModelIndex EnumerationModel::index(int row, int column, const QModelIndex &/*parent*/) const {
    QModelIndex modelIndex = QModelIndex();
    if(row >= 0 && column >= 0) {
        modelIndex = createIndex(row, column, m_enumeration.at(row));
    }
    return modelIndex;
}

QModelIndex EnumerationModel::parent(const QModelIndex &/*child*/) const {
    return QModelIndex();
}

QVariant EnumerationModel::headerData(int section, Qt::Orientation orientation, int role) const {
    QVariant data = QVariant();
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        extern QStringList g_enumerationHeaderSections;
        data = QVariant(g_enumerationHeaderSections.at(section));
    }
    else {
        data = QAbstractItemModel::headerData(section, orientation, role);
    }
    return data;
}

int EnumerationModel::rowCount(const QModelIndex &/*parent*/) const {
    return m_enumeration.size();
}

int EnumerationModel::columnCount(const QModelIndex &/*parent*/) const {
    extern QStringList g_enumerationHeaderSections;
    return g_enumerationHeaderSections.size();
}

QVariant EnumerationModel::data(const QModelIndex &index, int role) const {
    QVariant data = QVariant();
    if(index.isValid()) {
        switch(role) {
            case Qt::EditRole:
            case Qt::DisplayRole: {
                EnumerationElement *element = m_enumeration.at(index.row());
                if(element != NULL) {
                    EnumerationHeaderSection section = (EnumerationHeaderSection)index.column();
                    switch(section) {
                        case Code: {
                            data = QVariant(element->getCode());
                            break;
                        }
                        case Acronym: {
                            data = QVariant(element->getAcronym());
                            break;
                        }
                        case Transcript: {
                            data = QVariant(element->getTranscript());
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
    return data;
}

bool EnumerationModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(index.isValid() && role == Qt::EditRole) {
        EnumerationElement *element = m_enumeration.at(index.row());
        if(element != NULL) {
            EnumerationHeaderSection section = (EnumerationHeaderSection)index.column();
            switch(section) {
                case Code: {
                    element->setCode(value.toInt());
                    break;
                }
                case Acronym: {
                    element->setAcronym(value.toString());
                    break;
                }
                case Transcript: {
                    element->setTranscript(value.toString());
                    break;
                }
            }
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

bool EnumerationModel::insertRows(int row, int count, const QModelIndex &parent) {
    if (row >= 0) {
        beginInsertRows(parent, row, row + count - 1);
        for(int i = 0; i < count; i++) {
            m_enumeration.insert(row, new EnumerationElement(row + i));
        }
        endInsertRows();
        return true;
    }
    return false;
}

bool EnumerationModel::removeRows(int row, int count, const QModelIndex &parent) {
    if (row >= 0) {
        beginRemoveRows(parent, row, row + count - 1);
        for(int i = 0; i < count; i++) {
            EnumerationElement *element = m_enumeration.takeAt(row);
            if(element != NULL) {
                delete element;
            }
        }
        endRemoveRows();
        return true;
    }
    return false;
}

Qt::ItemFlags EnumerationModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if(index.isValid()) {
        return flags | Qt::ItemIsEditable;
    } else {
        return flags;
    }
}

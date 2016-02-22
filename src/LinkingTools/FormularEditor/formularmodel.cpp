#include "formularmodel.h"

const QStringList FormularModel::formularHeaderSections = QStringList() << QString::fromUtf8("Размер")
                                                                        << QString::fromUtf8("Тип")
                                                                        << QString::fromUtf8("Наименование")
                                                                        << QString::fromUtf8("Описание");


FormularModel::FormularModel(QList<FieldData*> &formularData, QObject *parent)
    : QAbstractItemModel(parent) {
    m_formularData = formularData;
}

QModelIndex FormularModel::index(int row, int column, const QModelIndex &/*parent*/) const {
    QModelIndex modelIndex = QModelIndex();
    if(row >= 0 && column >= 0) {
        modelIndex = createIndex(row, column, m_formularData.at(row));
    }
    return modelIndex;
}

QModelIndex FormularModel::parent(const QModelIndex &/*child*/) const {
    return QModelIndex();
}

QVariant FormularModel::headerData(int section, Qt::Orientation orientation, int role) const {
    QVariant data = QVariant();
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        data = QVariant(formularHeaderSections.at(section));
    }
    else {
        data = QAbstractItemModel::headerData(section, orientation, role);
    }
    return data;
}

int FormularModel::rowCount(const QModelIndex &/*parent*/) const {
    return m_formularData.size();
}

int FormularModel::columnCount(const QModelIndex &/*parent*/) const {
    return formularHeaderSections.size();
}

QVariant FormularModel::data(const QModelIndex &index, int role) const {
    QVariant data = QVariant();
    if(index.isValid()) {
        FieldData *field = m_formularData.at(index.row());
        if(field != NULL) {
            switch(role) {
                case Qt::DisplayRole: {
                    HeaderSection section = (HeaderSection)index.column();
                    switch(section) {
                        case Size: {
                            data = QVariant(field->getSize());
                            break;
                        }
                        case Type: {
                            data = QVariant(FieldData::types.at(field->getType()));
                            break;
                        }
                        case Name: {
                            data = QVariant(field->getName());
                            break;
                        }
                        case Description: {
                            data = QVariant(field->getDescription());
                            break;
                        }
                    }
                    break;
                }
                case Qt::EditRole: {
                    data = QVariant((long long int)field);
                    break;
                }
                case Qt::ToolTipRole: {
                    QString toolTip = QString::fromUtf8(    "Размер:\t\t%size\n"
                                                            "Тип:\t\t\t%type\n"
                                                            "Размерность:\t\t%dimension\n"
                                                            "Наименование:\t%name\n"
                                                            "Описание:\t\t%description"
                                                            "%additional"
                                                            );
                    toolTip.replace("%size", QString::number(field->getSize()));
                    toolTip.replace("%type", FieldData::types.at(field->getType()));
                    toolTip.replace("%dimension", FieldData::dimensions.at(field->getDimension()));
                    toolTip.replace("%name", field->getName());
                    toolTip.replace("%description", field->getDescription());
                    switch(field->getType()) {
                        case FieldData::Integer:
                        case FieldData::Real:
                        case FieldData::Boolean:
                        case FieldData::String:
                        case FieldData::Unused: {
                            toolTip.replace("%additional", QString());
                            break;
                        }
                        case FieldData::Scalable: {
                            FieldScalable *fieldScalable = static_cast<FieldScalable*>(field);
                            QString additional = QString::fromUtf8( "\n\nЦена %kind разряда:\t%order\n"
                                                                    "%sign"
                                                                    );
                            if(fieldScalable->hasAdditionalCode()) {
                                additional.replace("%sign", QString::fromUtf8("Знак в дополнительном коде"));
                            } else if(fieldScalable->hasHighBitSign()) {
                                additional.replace("%sign", QString::fromUtf8("Знак в старшем разряде"));
                            } else {
                                additional.replace("%sign", QString());
                            }
                            if(fieldScalable->getHighOrderBit() != 0.0) {
                                additional.replace("%kind", QString::fromUtf8("старшего"));
                                additional.replace("%order", QString::number(fieldScalable->getHighOrderBit()));
                            } else if(fieldScalable->getLowerOrderBit() != 0.0) {
                                additional.replace("%kind", QString::fromUtf8("младшего"));
                                additional.replace("%order", QString::number(fieldScalable->getLowerOrderBit()));
                            } else {
                                additional = QString();
                            }
                            toolTip.replace("%additional", additional);
                            break;
                        }
                        case FieldData::Enumeration: {
                            FieldEnumeration *fieldEnumeration = static_cast<FieldEnumeration*>(field);
                            QString additional = "\n";
                            for(int i = 0; i < fieldEnumeration->getElements().size(); i++) {
                                additional.append("\n%code - %transcript");
                                additional.replace("%code", fieldEnumeration->getElements()[i].getCode());
                                additional.replace("%transcript", fieldEnumeration->getElements()[i].getTranscript());
                            }
                            toolTip.replace("%additional", additional);
                            break;
                        }
                        case FieldData::Constant: {
                            FieldConstant *fieldConstant = static_cast<FieldConstant*>(field);
                            QString additional = QString::fromUtf8("\n\nКонстанта %constant");
                            additional.replace("%constant", fieldConstant->getValue());
                            toolTip.replace("%additional", additional);
                            break;
                        }
                    }
                    data = QVariant(toolTip);
                    break;
                }
//                case Qt::SizeHintRole: {
//                    int size = 0;
//                    for(int i = 0; i <= index.row(); i++) {
//                        size += index.model()->index(i, Size).data(Qt::DisplayRole).toInt();
//                    }
//                    qDebug() << "Size" << size;
//                    if(size == 16) {
//                        data = QVariant(QSize(50,40));
//                    } else {
//                        data = QVariant(QSize(50, 20));
//                    }
//                    break;
//                }
            }
        }
    }
    return data;
}

bool FormularModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(index.isValid() && role == Qt::EditRole) {
        FieldData *field = m_formularData.at(index.row());
        if(field != NULL) {
            switch(field->getType()) {
                case FieldData::Integer:
                case FieldData::Real:
                case FieldData::Boolean:
                case FieldData::String:
                case FieldData::Unused: {
                    delete field;
                    break;
                }
                case FieldData::Scalable: {
                    delete static_cast<FieldScalable*>(field);
                    break;
                }
                case FieldData::Enumeration: {
                    delete static_cast<FieldEnumeration*>(field);
                    break;
                }
                case FieldData::Constant: {
                    delete static_cast<FieldConstant*>(field);
                    break;
                }
            }
        }
        m_formularData.replace(index.row(), (FieldData*)value.toInt());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool FormularModel::insertRows(int row, int count, const QModelIndex &parent) {
    if (row >= 0) {
        beginInsertRows(parent, row, row + count - 1);
        for(int i = 0; i < count; i++) {
            m_formularData.insert(row, NULL);
        }
        endInsertRows();
        return true;
    }
    return false;
}

bool FormularModel::removeRows(int row, int count, const QModelIndex &parent) {
    if (row >= 0) {
        beginRemoveRows(parent, row, row + count - 1);
        for(int i = 0; i < count; i++) {
            FieldData *field = m_formularData.takeAt(row);
            if(field != NULL) {
                switch(field->getType()) {
                    case FieldData::Integer:
                    case FieldData::Real:
                    case FieldData::Boolean:
                    case FieldData::String:
                    case FieldData::Unused: {
                        delete field;
                        break;
                    }
                    case FieldData::Scalable: {
                        delete static_cast<FieldScalable*>(field);
                        break;
                    }
                    case FieldData::Enumeration: {
                        delete static_cast<FieldEnumeration*>(field);
                        break;
                    }
                    case FieldData::Constant: {
                        delete static_cast<FieldConstant*>(field);
                        break;
                    }
                }
            }
        }
        endRemoveRows();
        emit dataChanged(index(row), index(row + count - 1, formularHeaderSections.size() - 1));
        return true;
    }
    return false;
}

Qt::ItemFlags FormularModel::flags(const QModelIndex &index) const {
    //FieldData *field = (FieldData*)index.data(Qt::EditRole).toInt();
    Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (index.isValid()) {
            flags = Qt::ItemIsEditable | flags;
    }
    return flags;
}

Qt::DropActions FormularModel::supportedDropActions() const {
    return Qt::MoveAction;
}

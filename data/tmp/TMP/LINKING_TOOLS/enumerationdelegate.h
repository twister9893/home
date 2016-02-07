#ifndef ENUMERATIONDELEGATE_H
#define ENUMERATIONDELEGATE_H

#include <QStyledItemDelegate>
#include <QSpinBox>
#include <QLineEdit>
#include <QDebug>

#include "enumerationelement.h"
#include "libenum.h"

class EnumerationDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit EnumerationDelegate(QObject *parent = 0);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // ENUMERATIONDELEGATE_H

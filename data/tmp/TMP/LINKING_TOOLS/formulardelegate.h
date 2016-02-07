#ifndef FORMULARDELEGATE_H
#define FORMULARDELEGATE_H

#include <QAbstractItemDelegate>
#include <QItemDelegate>
#include <QPainter>
#include <QDebug>

#include "fielddata.h"
#include "fielddataeditor.h"
#include "scalablewidget.h"
#include "enumerationwidget.h"
#include "constantwidget.h"

class FormularDelegate : public QAbstractItemDelegate {
    Q_OBJECT
    public:
        explicit FormularDelegate(QObject *parent = 0);

        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
        QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
        void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

    public slots:
        void slot_reject();
        void slot_accept();

};

#endif // FORMULARDELEGATE_H

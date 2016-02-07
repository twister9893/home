#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <QTableView>
#include <QLabel>
#include <QDateTime>

#include "TableModel.h"
#include "xmlparser.h"
#include "additional.h"
#include "hvLib/HierarchicalHeaderView.h"
#include "ui_DataView.h"

class DataView : public QMainWindow, private Ui::DataView {
    Q_OBJECT
public:
	DataView(QString viewFile, QWidget *parent = 0);

	void initDataView(QString viewFile);

public slots:
	void slot_setData(int tableNumber, QList<QVariant> data, QDateTime receiveTime);
	void slot_updateGeometry();

protected:
    void changeEvent(QEvent *e);
	void closeEvent(QCloseEvent *e);

	virtual QList<TableModel*> initTableModels();
	virtual QVariant convertValue(QVariant value, int tableNumber, int column);

	QDomDocument m_abonentDoc;

private:
	QList<QTableView*> m_tables;
	QLabel *m_receiveTime;

private slots:
	void slot_setFont();
};

#endif // DATAVIEW_H

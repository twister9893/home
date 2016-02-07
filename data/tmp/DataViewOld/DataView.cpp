#include "DataView.h"

#include <QFontDialog>
#include <QTimer>
#include <QDesktopWidget>
#include <QDebug>

#include "converter.h"

DataView::DataView(QString viewFile, QWidget *parent)
		: QMainWindow(parent) {
    setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	m_receiveTime = new QLabel(statusbar);
	statusbar->addWidget(new QLabel(QString::fromUtf8("Время принятия пакета: "), statusbar));
	statusbar->addWidget(m_receiveTime);

	initDataView(viewFile);

	connect(fontAction, SIGNAL(triggered()), this, SLOT(slot_setFont()));
	connect(fontAction, SIGNAL(triggered()), this, SLOT(slot_updateGeometry()));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void DataView::initDataView(QString viewFile) {
	qDebug() << "[Data view]\tInit data view:" << viewFile;
	m_abonentDoc = parseXmlFile(viewFile);
	//Очищаем область отображения
	while(!m_tables.isEmpty()) {
		QTableView *table = m_tables.takeFirst();
		if(table != NULL) {
			delete table;
		}
	}

	QList<TableModel*> tableModels = initTableModels();
	for(int i = 0; i < tableModels.size(); i++) {
		qDebug() << "[Data view]\tInit data view: Set table" << i;
		QTableView *table = new QTableView(this);
		HierarchicalHeaderView *headerView = new HierarchicalHeaderView(Qt::Horizontal, table);
		table->setHorizontalHeader(headerView);
		
		tableModels.at(i)->setParent(table);
		table->setModel(tableModels.at(i));
		table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
		table->verticalHeader()->setVisible(false);
		table->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		table->setWordWrap(true);
		table->setFocusPolicy(Qt::NoFocus);
		table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

		m_tables.append(table);
		scrollAreaLayout->addWidget(table);
	}
	slot_updateGeometry();
	scrollAreaLayout->addSpacerItem(new QSpacerItem(0, QApplication::desktop()->height(), QSizePolicy::Expanding, QSizePolicy::Expanding));
	qDebug() << "[Data view]\tInit data view: Finish";
}

void DataView::slot_setData(int tableNumber, QList<QVariant> data, QDateTime receiveTime) {
	if(tableNumber >= m_tables.size()) {
		return;
	}

	qDebug() << "[Data view]\tSet data: Size " << data.size();

	TableModel *model = static_cast<TableModel*>(m_tables.at(tableNumber)->model());
	if(model != NULL) {
		int row = -1;
		int column = 0;
		for(int i = 0; i < data.size(); i++) {
			if(i % model->columnCount() == 0) {
				row++;
				column = 0;
			}
			QModelIndex newIndex = model->index(row, column);
			while(row >= model->rowCount()) {
				model->insertRow(model->rowCount());
			}
			model->setData(newIndex, convertValue(data.at(i), tableNumber, column), Qt::EditRole);
			column++;
		}
		m_receiveTime->setText(receiveTime.toString());
	}
}

void DataView::slot_updateGeometry() {
	for(int i = 0; i < m_tables.size(); i++) {
		QTableView *table = m_tables.at(i);
		if(table != NULL) {
			if(table->model() != NULL) {
				table->setMinimumHeight(table->horizontalHeader()->height() * (table->model()->rowCount() + 1));
				table->verticalHeader()->setDefaultSectionSize(table->horizontalHeader()->height());
			}
		}
	}
}

void DataView::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		retranslateUi(this);
		break;
	default:
		break;
	}
}

void DataView::closeEvent(QCloseEvent *e) {
	QMainWindow::closeEvent(e);
}

QList<TableModel*> DataView::initTableModels() {
	QList<TableModel*> tableModels;
	QDomElement tableElement = m_abonentDoc.firstChildElement().firstChildElement();
	while(!tableElement.isNull()) {
		qDebug() << "[Data view]\tInit table models:" << tableModels.size() + 1;

		int columnCount = 0;
		QStandardItem *headerRoot = new QStandardItem(tableElement.attribute("name"));
		buildStandardTree(headerRoot, tableElement, &columnCount);

		TableModel *tableModel = new TableModel(columnCount);
		QStandardItemModel *headerModel = new QStandardItemModel(tableModel);
		headerModel->setItem(0,0,headerRoot);

		//tableModel->insertRows(0, tableElement.attribute("count", "1").toInt());
		tableModel->setHeader(Qt::Horizontal, headerModel);

		tableModels.append(tableModel);
		tableElement = tableElement.nextSiblingElement();
	}
	qDebug() << "[Data view]\tInit table models: Finish";
	return tableModels;
}

QVariant DataView::convertValue(QVariant value, int tableNumber, int column) {
	QString formularFileName = m_abonentDoc.firstChildElement().attribute("formularPath");
	QDomElement tableDom = m_abonentDoc.firstChildElement().childNodes().at(tableNumber).toElement();
	int currentColumn = 0;
	QDomElement fieldDom = getElementAt(column, currentColumn, tableDom);
	return QVariant(convertData(value, formularFileName, fieldDom.attribute("name"), fieldDom.attribute("format", columnMasks.at(ColumnMask_Regular))));
}

void DataView::slot_setFont() {
	bool isOk;
	QFont font = QFontDialog::getFont(&isOk, scrollArea->font(), this);
	if(isOk) {
		scrollArea->setFont(font);
	}
}

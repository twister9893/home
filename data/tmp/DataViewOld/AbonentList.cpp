#include "AbonentList.h"

AbonentList::AbonentList(QFileInfoList viewFiles, QString groupSeparator, QWidget *parent)
		: QDialog(parent) {
    setupUi(this);
	treeWidget->setHeaderLabel(QString::fromUtf8("Абонент"));
	initAbonents(viewFiles, groupSeparator);

	connect(treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(slot_setAbonent()));
	connect(treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slot_accept(QTreeWidgetItem*)));
	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void AbonentList::initAbonents(QFileInfoList viewFiles, QString groupSeparator) {
	treeWidget->clear();
	QTreeWidgetItem *groupItem = NULL;
	for(int i = 0; i < viewFiles.size(); i++) {
		QDomDocument abonentDoc = parseXmlFile(viewFiles.at(i).absoluteFilePath());
		QString fullName = abonentDoc.firstChildElement().attribute("name", "_error_");
		if(fullName != "_error_") {
			QStringList tmp = fullName.split(groupSeparator);
			QString groupName = tmp.takeFirst();
			if(groupItem == NULL || groupName != groupItem->text(0)) {
				groupItem = new QTreeWidgetItem(treeWidget);
				groupItem->setText(0, groupName);
				treeWidget->addTopLevelItem(groupItem);
			}
			if(groupItem != NULL && groupName == groupItem->text(0)) {
				QTreeWidgetItem *abonentItem = new QTreeWidgetItem(groupItem);
				QString abonentName = tmp.join(groupSeparator);
				//В элементах дерева храним:
				//0 - Имя абонента
				//1 - Путь к view файлу абонента
				//2 - Порядковый номер абонента
				abonentItem->setText(0, abonentName);
				abonentItem->setText(1, viewFiles.at(i).absoluteFilePath());
				abonentItem->setText(2, QString::number(i));
				qDebug() << "[Abonent list]\tInit abonent: [ OK  ] [" << i << "]" << viewFiles.at(i).absoluteFilePath();
			}
		}
		else {
			qDebug() << "[Abonent list]\tInit abonent: [ERROR] [" << i << "]" << viewFiles.at(i).absoluteFilePath();
			QMessageBox::warning(this, QString::fromUtf8("Внимание"), QString::fromUtf8("Не удалось открыть файл абонента\n") + viewFiles.at(i).fileName());
		}
	}
}

QString AbonentList::getViewFile() {
	return m_viewFile;
}

int AbonentList::getAbonent() {
	return m_abonent;
}

void AbonentList::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void AbonentList::slot_setAbonent() {
	QTreeWidgetItem *currentItem = treeWidget->currentItem();
	while(currentItem->childCount() != 0) {
		currentItem = currentItem->child(0);
	}
	m_viewFile = currentItem->text(1);
	m_abonent = currentItem->text(2).toInt();
	qDebug() << "[Abonent list]\tSet abonent: [" << m_abonent << "]" << m_viewFile;
}

void AbonentList::slot_accept(QTreeWidgetItem *currentItem) {
	if(currentItem != NULL) {
		if(currentItem->childCount() == 0) {
			accept();
		}
	}
}

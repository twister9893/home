#ifndef ABONENTLIST_H
#define ABONENTLIST_H

#include <QList>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>

#include "xmlparser.h"
#include "ui_AbonentList.h"

class AbonentList : public QDialog, private Ui::AbonentList {
    Q_OBJECT
public:
	AbonentList(QFileInfoList viewFiles, QString groupSeparator, QWidget *parent = 0);

	void initAbonents(QFileInfoList viewFiles, QString groupSeparator);
	QString getViewFile();
	int getAbonent();

protected:
    void changeEvent(QEvent *e);

private:
	QString m_viewFile;
	int m_abonent;

private slots:
	void slot_setAbonent();
	void slot_accept(QTreeWidgetItem *currentItem);
};

#endif // ABONENTLIST_H

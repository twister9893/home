#include "AbonentNetworkTool.h"
#include "project/AbonentGetDataFunctions.h"

AbonentNetworkTool::AbonentNetworkTool(QObject *parent)
	: QObject(parent) {
	m_timer = new QTimer(this);

	connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_update()));
}

void AbonentNetworkTool::start(int msecUpdateInterval) {
	m_timer->start(msecUpdateInterval);
}

void AbonentNetworkTool::stop() {
	m_timer->stop();
}

void AbonentNetworkTool::setAdditionalInfo(QVariant additionalInfo) {
	m_additionalInfo = additionalInfo;
}

bool AbonentNetworkTool::transferData() {
	QList<int> tableNumbers;
	QList< QList<QVariant> > data;
	QDateTime receiveTime;

#include "project/AbonentCases.h"
	/*static int time = 1103700000;
	QList<QVariant> row;
	row << QVariant(time % 2) << QVariant(time++) << QVariant(0.8) << QVariant(0.3);
	emit gotData(0, row, QDateTime::currentDateTime());
	*/
}

void AbonentNetworkTool::slot_update() {
	bool isOk = transferData();
	if(isOk) {
		qDebug() << "[AbonentNetworkTool] Update: Ok";
	} else {
		qWarning() << "[AbonentNetworkTool] Update: Failed!";
	}
}

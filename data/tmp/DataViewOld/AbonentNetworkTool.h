#ifndef ABONENTNETWORKTOOL_H
#define ABONENTNETWORKTOOL_H

#include <QList>
#include <QDateTime>
#include <QTimer>
#include <QVariant>

class AbonentNetworkTool : public QObject {
Q_OBJECT
public:
	AbonentNetworkTool(QObject *parent = 0);
	void start(int msecUpdateInterval);
	void stop();
	void setAdditionalInfo(QVariant additionalInfo);

protected:
	virtual bool transferData();

signals:
	void gotData(int tableNumber, QList<QVariant> data, QDateTime receiveTime);

private slots:
	void slot_update();

private:
	QTimer *m_timer;
	QVariant m_additionalInfo;

};

#endif // ABONENTNETWORKTOOL_H

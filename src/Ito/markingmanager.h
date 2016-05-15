#ifndef MARKINGMANAGER_H
#define MARKINGMANAGER_H

#include <QObject>
#include <QPainter>
#include "state.h"

class MarkingManager : public QObject
{
    Q_OBJECT
public:
    explicit MarkingManager(QObject *parent = 0)
        : QObject(parent) {}

    void draw(QPainter *painter);

public slots:
    /**
     * @brief Слот получения состояния ИТО
     * @param state Структура состояния ИТО
     */
    void setCoreState(const State &state) {_coreState = state;}

private:
    void drawPelengs(QPainter *painter);
    void drawDistances(QPainter *painter);
    void drawInfo(QPainter *painter);

    State _coreState;
};

#endif // MARKINGMANAGER_H

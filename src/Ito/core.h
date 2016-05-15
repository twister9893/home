#ifndef CORE_H
#define CORE_H

#include "state.h"
#include "markingmanager.h"
#include "objectmanager.h"

/**
 * @brief Класс ядра ИТО
 */
class Core : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State _state READ state WRITE setState NOTIFY stateChanged)
public:
    explicit Core(QObject *parent = 0);

    /**
     * @brief Установка состояния ИТО
     * @param state Структура состояния ИТО
     */
    void setState(State state);

    /**
     * @brief Получение состояния ИТО
     * @return Структура состояния ИТО
     */
    State state() const {return _state;}

    /**
     * @brief Получить менеджер объектов, предоставляющий интерфейс изменения их состава
     * @return Менеджер объектов
     */
    ObjectManager * objectManager() {return _objectManager;}

    /**
     * @brief Запуск процесса отрисовки
     * @todo Вызвать в цикле отрисовки
     * @param painter QPainter из реализованного QPaintEngine
     */
    void process(QPainter *painter);




    //****FOR TESTING****
    int64_t addEllipse(qreal x, qreal y, qreal width, qreal height, bool scalable, int64_t anchor = -1) {
        Ellipse *ellipse = new Ellipse(_objectManager->objectCount(), QRectF(x,y,width,height));
        if(anchor >= 0) {
            ellipse->setAnchor(anchor);
        }
        ellipse->setScalable(scalable);
        QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(2);
        ellipse->setPen(pen);
        QBrush brush;
        brush.setColor(QColor(240,50,0,100));
        brush.setStyle(Qt::SolidPattern);
        ellipse->setBrush(brush);
        _objectManager->addObject(ellipse);
        return _objectManager->objectCount() - 1;
    }
    int64_t addTarget(qreal x, qreal y, Target::TargetIff iff, Target::TargetType type, int64_t anchor = -1) {
        Target *target = new Target(_objectManager->objectCount(), iff, type);
        if(anchor >= 0) {
            target->setAnchor(anchor);
        }
        target->setPos(QPointF(x,y));
        _objectManager->addObject(target);
        return _objectManager->objectCount() - 1;
    }
    //******************




signals:
    /**
     * @brief Сигнал изменения состояния ИТО
     * @param state Структура состояния ИТО
     */
    void stateChanged(const State &state);

private:
    MarkingManager *_markingManager;
    ObjectManager *_objectManager;
    //    MapManager *mapManager;
    State _state;
};

#endif // CORE_H

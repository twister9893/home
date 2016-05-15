#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>
#include <QMap>
#include <QPainter>

#include "state.h"
#include "target.h"
#include "point.h"
#include "ellipse.h"

/**
 * @brief Класс менеджера объектов ИТО
 */
class ObjectManager : public QObject
{
    Q_OBJECT
public:
    explicit ObjectManager(QObject *parent = 0)
        : QObject(parent) {}

    /**
     * @brief Добавление объекта на ИТО
     * @param object Объект ИТО (цели, пользовательская графика и т.п.)
     * @return Признак успешного выполнения
     */
    bool addObject(Object *object);

    /**
     * @brief Удаление объекта с ИТО
     * @param id Идентификатор удаляемого объекта
     * @return Признак успешного выполнения
     */
    bool removeObject(qint64 id);

    /**
     * @brief Получение объекта ИТО
     * @param id Идентификатор получаемого объекта
     * @return Объект ИТО
     */
    Object * object(qint64 id) const;

    /**
     * @brief Получение количества объктов на ИТО
     * @return Количество объектов на ИТО
     */
    int objectCount() const {return _objects.size();}

    /**
     * @brief Отрисовка объектов ИТО
     * @param painter QPainter из реализованного QPaintEngine
     */
    void draw(QPainter *painter);

public slots:
    /**
     * @brief Слот получения состояния ИТО
     * @param state Структура состояния ИТО
     */
    void setCoreState(const State &state) {_coreState = state;}

private:
    /**
     * @brief Получения полного смещения объекта относительно условного центра
     * @warning Метод рекурсивный
     * @param anchor Якорь объекта
     * @param dx Указатель на переменную смещения по оси X
     * @param dy Указатель на переменную смещения по оси Y
     * @param device Устройство QPaintDevice
     */
    void getFullOffset(Object *anchor, qreal *dx, qreal *dy, QPaintDevice *device);

    /**
     * @brief Отрисовка целей
     * @param painter QPainter из реализованного QPaintEngine
     * @param target Цель
     */
    void drawTarget(QPainter *painter, Target *target);

    /**
     * @brief Отрисовка графических примитивов
     * @param painter QPainter из реализованного QPaintEngine
     * @param primitive Графический примитив
     */
    void drawPrimitive(QPainter *painter, Primitive *primitive);

    QMap<qint64,Object*> _objects;
    State _coreState;
};

#endif // OBJECTMANAGER_H

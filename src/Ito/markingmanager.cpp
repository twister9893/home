#include "markingmanager.h"

//MarkingManager::MarkingManager(QObject *parent) : QObject(parent)
//{

//}


void MarkingManager::draw(QPainter *painter)
{
    drawPelengs(painter);
    drawDistances(painter);
    drawInfo(painter);
}

void MarkingManager::drawPelengs(QPainter *painter)
{
    if(!painter)
        return;

    const int step = 10;
    const int deadZone = 5;

    painter->save();

    QPen pen;
    pen.setWidthF(1.0);
    pen.setColor(QColor(0,70,70,80));
    QPen fontPen(QColor(0,70,70,150));
    painter->setFont(QFont("DeJaVu", 10));
//    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPoint(0,0);
    int side = qMin( painter->device()->width(), painter->device()->height() );
//    painter->drawEllipse(QPoint(0,0),side/2,side/2);
//    painter->rotate(180);
    for(int angle=0; angle < 360; angle += 10) {
        painter->setPen(pen);
        painter->drawLine(QLine(0,deadZone,0,side/2));
        painter->scale(1.0,-1.0);
        painter->setPen(fontPen);
        painter->drawText(QPoint(5,-side/2+15), QString::number(angle));
        painter->scale(1.0,-1.0);
        painter->rotate(-step);
    }

    painter->restore();
}

void MarkingManager::drawDistances(QPainter *painter)
{
    if(!painter)
        return;

    painter->save();

    QPen pen;
    pen.setWidthF(1.5);
    pen.setColor(QColor(0,110,110,80));
    painter->setPen(pen);
//    painter->setRenderHint(QPainter::Antialiasing);
    qreal side = (qreal)qMin( painter->device()->width(), painter->device()->height() );
    const int distanceCount = 4;
    qreal step = side / distanceCount / 2;

    painter->drawEllipse(QPoint(0,0),side/2,side/2);
    for(int i=1; i <= distanceCount; ++i) {
        painter->drawEllipse(QPoint(0,0), step*i, step*i);
    }

    painter->restore();
}

void MarkingManager::drawInfo(QPainter *painter)
{
    painter->save();

    QPen pen;
    pen.setColor(QColor(30,30,30));
    painter->setPen(pen);
    painter->setFont(QFont("DeJaVu", 10));

    painter->scale(1.0,-1.0);
    painter->drawText(-painter->device()->width()/2 + 5, -painter->device()->height()/2 + 15, "Scale: "+QString::number(_coreState.scale));

    painter->restore();
}

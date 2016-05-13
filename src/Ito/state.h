#ifndef STATE
#define STATE

#include <QPointF>

struct State {
    State()
        : scale(0.0),
          angle(0.0),
          relative(false),
          nose(false),
          night(false) {}

    qreal scale;
    QPointF offset;
    qreal angle;
    bool relative;
    bool nose;
    bool night;
};

#endif // STATE


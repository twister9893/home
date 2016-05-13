#ifndef STATE
#define STATE

#include <QPointF>

struct State {
    State()
        : scale(256.0),
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

    bool operator==(const State& other) {
        if(scale - other.scale < 0.001 &&
           offset == other.offset &&
           angle - other.angle < 0.001 &&
           relative == other.relative &&
           nose == other.nose &&
           night == other.night)
            return true;
        else
            return false;
    }
};

#endif // STATE


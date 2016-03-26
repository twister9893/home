#ifndef TSICORE_H
#define TSICORE_H

#include <QPointF>

class TsiCore {
    Q_PROPERTY(Projection projection READ getProjection WRITE setProjection NOTIFY projectionChanged)

    Q_PROPERTY(float scale READ getScale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(QPointF offset READ getOffset WRITE setOffset NOTIFY offsetChanged)
    Q_PROPERTY(float angle READ getAngle WRITE setAngle NOTIFY angleChanged)

    Q_PROPERTY(bool relative READ isRelative WRITE setRelative NOTIFY relativeChanged)
    Q_PROPERTY(bool nose READ isNose WRITE setNose NOTIFY noseChanged)
    Q_PROPERTY(bool night READ isNight WRITE setNight NOTIFY nightChanged)

    Q_PROPERTY(bool mapVisibility READ getMapVisibility WRITE setMapVisibility NOTIFY mapVisibilityChanged)
    Q_PROPERTY(bool primaryVisibility READ getPrimaryVisibility WRITE setPrimaryVisibility NOTIFY primaryVisibilityChanged)
    Q_PROPERTY(bool targetsVisibility READ getTargetsVisibility WRITE setTargetsVisibility NOTIFY targetsVisibilityChanged)
    Q_PROPERTY(bool limbVisibility READ getLimbVisibility WRITE setLimbVisibility NOTIFY limbVisibilityChanged)
    Q_PROPERTY(bool loupeVisibility READ getLoupeVisibility WRITE setLoupeVisibility NOTIFY loupeVisibilityChanged)

public:
    float getScale() const {
        return m_scale;
    }

    QPointF getOffset() const {
        return m_offset;
    }

    float getAngle() const {
        return m_angle;
    }

    bool isRelative() const {
        return m_relative;
    }

    bool isNose() const {
        return m_nose;
    }

    bool isNight() const {
        return m_night;
    }

    bool getMapVisibility() const {
        return m_mapVisibility;
    }

    bool getPrimaryVisibility() const {
        return m_primaryVisibility;
    }

    bool getTargetsVisibility() const {
        return m_targetsVisibility;
    }

    bool getLimbVisibility() const {
        return m_limbVisibility;
    }

    bool getLoupeVisibility() const {
        return m_loupeVisibility;
    }

public slots:
    void setScale(float scale) {
        if (m_scale == scale)
            return;

        m_scale = scale;
        emit scaleChanged(scale);
    }

    void setOffset(QPointF offset) {
        if (m_offset == offset)
            return;

        m_offset = offset;
        emit offsetChanged(offset);
    }

    void setAngle(float angle) {
        if (m_angle == angle)
            return;

        m_angle = angle;
        emit angleChanged(angle);
    }

    void setRelative(bool relative) {
        if (m_relative == relative)
            return;

        m_relative = relative;
        emit relativeChanged(relative);
    }

    void setNose(bool nose) {
        if (m_nose == nose)
            return;

        m_nose = nose;
        emit noseChanged(nose);
    }

    void setNight(bool night) {
        if (m_night == night)
            return;

        m_night = night;
        emit nightChanged(night);
    }

    void setMapVisibility(bool mapVisibility) {
        if (m_mapVisibility == mapVisibility)
            return;

        m_mapVisibility = mapVisibility;
        emit mapVisibilityChanged(mapVisibility);
    }

    void setPrimaryVisibility(bool primaryVisibility) {
        if (m_primaryVisibility == primaryVisibility)
            return;

        m_primaryVisibility = primaryVisibility;
        emit primaryVisibilityChanged(primaryVisibility);
    }

    void setTargetsVisibility(bool targetsVisibility) {
        if (m_targetsVisibility == targetsVisibility)
            return;

        m_targetsVisibility = targetsVisibility;
        emit targetsVisibilityChanged(targetsVisibility);
    }

    void setLimbVisibility(bool limbVisibility) {
        if (m_limbVisibility == limbVisibility)
            return;

        m_limbVisibility = limbVisibility;
        emit limbVisibilityChanged(limbVisibility);
    }

    void setLoupeVisibility(bool loupeVisibility) {
        if (m_loupeVisibility == loupeVisibility)
            return;

        m_loupeVisibility = loupeVisibility;
        emit loupeVisibilityChanged(loupeVisibility);
    }

signals:
    void scaleChanged(float scale);
    void offsetChanged(QPointF offset);
    void angleChanged(float angle);
    void relativeChanged(bool relative);
    void noseChanged(bool nose);
    void nightChanged(bool night);
    void mapVisibilityChanged(bool mapVisibility);
    void primaryVisibilityChanged(bool primaryVisibility);
    void targetsVisibilityChanged(bool targetsVisibility);
    void limbVisibilityChanged(bool limbVisibility);
    void loupeVisibilityChanged(bool loupeVisibility);

private:
    float m_scale;
    QPointF m_offset;
    float m_angle;
    bool m_relative;
    bool m_nose;
    bool m_night;
    bool m_mapVisibility;
    bool m_primaryVisibility;
    bool m_targetsVisibility;
    bool m_limbVisibility;
    bool m_loupeVisibility;
};

#endif // TSICORE_H

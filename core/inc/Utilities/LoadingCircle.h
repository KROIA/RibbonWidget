#pragma once


#include "RibbonWidget_base.h"
#include <QObject>
#include <QRect>
#include <QColor>
#include <QPainter>

class RIBBON_WIDGET_API LoadingCircle : public QObject
{
    Q_OBJECT
    public:
        LoadingCircle();
        LoadingCircle(const QPoint &center, float radius);
        ~LoadingCircle();

        void setColor(const QColor &color);
        void setCenter(const QPoint &center);
        void setRadius(float radius);
        void setAngle(float angle);
        void setDeltaAngle(float delta);
        void setVisible(bool visible);

        const QColor &getColor() const;
        const QPoint &getCenter() const;
        float getRadius() const;
        float getAngle() const;
        float getDeltaAngle() const;
        bool isVisible() const;

        void rotate();
        void draw(QPainter &painter);

    private:
        QColor m_color;
        QPoint m_center;
        float m_radius;
        float m_angle;
        float m_deltaAngle;
        bool m_isVisible;
};

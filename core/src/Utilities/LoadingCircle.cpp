#define _USE_MATH_DEFINES
#include <cmath>

#include "utilities/LoadingCircle.h"




LoadingCircle::LoadingCircle()
{
    m_color = QColor(0,200,0);
    m_center = QPoint(0,0);
    m_radius = 10;
    m_angle = 0;
    m_deltaAngle = 0.1;
    m_isVisible = false;
}
LoadingCircle::LoadingCircle(const QPoint &center, float radius)
{
    m_color = QColor(0,200,0);
    m_center = center;
    m_radius = radius;
    m_angle = 0;
    m_deltaAngle = 0.1;
    m_isVisible = false;
}
LoadingCircle::~LoadingCircle()
{

}
void LoadingCircle::setColor(const QColor &color)
{
    m_color = color;
}
void LoadingCircle::setCenter(const QPoint &center)
{
    m_center = center;
}
void LoadingCircle::setRadius(float radius)
{
    m_radius = radius;
}
void LoadingCircle::setAngle(float angle)
{
    m_angle = angle;
}
void LoadingCircle::setDeltaAngle(float delta)
{
    m_deltaAngle = delta;
}
void LoadingCircle::setVisible(bool visible)
{
    m_isVisible = visible;
}

const QColor &LoadingCircle::getColor() const
{
    return m_color;
}
const QPoint &LoadingCircle::getCenter() const
{
    return m_center;
}
float LoadingCircle::getRadius() const
{
    return m_radius;
}
float LoadingCircle::getAngle() const
{
    return m_angle;
}
float LoadingCircle::getDeltaAngle() const
{
    return m_deltaAngle;
}
bool LoadingCircle::isVisible() const
{
    return m_isVisible;
}

void LoadingCircle::rotate()
{
    m_angle += m_deltaAngle;
}
void LoadingCircle::draw(QPainter &painter)
{
    if(!m_isVisible)return;
    qreal circleRadius = m_radius*0.25f;
    

    int pointCount = 5;
    qreal circleRadiusIncrement = circleRadius / (pointCount*3);
    float angleOffset = M_PI_4;
    for(int i=0; i<pointCount; ++i)
    {
        QColor col = m_color;
        col.setAlpha(255*(i+1)/pointCount);
        QPointF dotPos;
        dotPos.setX(m_radius*cos(m_angle + angleOffset*i)+m_center.x());
        dotPos.setY(m_radius*sin(m_angle + angleOffset*i)+m_center.y());

        painter.setPen(Qt::NoPen);
        painter.setBrush(col);
        painter.drawEllipse(dotPos, circleRadius, circleRadius);
        circleRadius += circleRadiusIncrement;
    }


}

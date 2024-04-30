#include "utilities/ProgressBar.h"

ProgressBar::ProgressBar()
{
    m_isVisible = false;
    m_percentage = 0;
    m_direction = Direction::leftRight;
}
ProgressBar::ProgressBar(const QRect &area)
{
    m_isVisible = false;
    m_percentage = 0;
    m_direction = Direction::leftRight;
    m_area = area;
}
ProgressBar::ProgressBar(const QRect &area, float percentage)
{
    m_isVisible = false;
    m_area = area;
    m_percentage = percentage;
    m_direction = Direction::leftRight;
}
ProgressBar::ProgressBar(const QRect &area, float percentage, const QColor color)
{
    m_isVisible = false;
    m_area = area;
    m_percentage = percentage;
    m_color = color;
    m_direction = Direction::leftRight;
}

float ProgressBar::getProgress() const
{
    return m_percentage;
}
const QColor &ProgressBar::getColor() const
{
    return m_color;
}
bool ProgressBar::isVisible() const
{
    return m_isVisible;
}
const QRect &ProgressBar::getRect()
{
    return m_area;
}
const ProgressBar::Direction &ProgressBar::getDirection() const
{
    return m_direction;
}

void ProgressBar::draw(QPainter &painter)
{
     if(!m_isVisible || m_percentage == 0)
         return;
    painter.setRenderHint(QPainter::Antialiasing);


    QRect rect = m_area;
    switch (m_direction) {
    case leftRight:
        rect.setWidth(static_cast<int>(rect.width()*m_percentage));
        break;
    case rightLeft:
        rect.setLeft(rect.width() - static_cast<int>(rect.width()*m_percentage));
        break;
    case bottomTop:
        rect.setHeight(static_cast<int>(rect.height()*m_percentage));
        break;
    case topBottom:
        rect.setBottom(rect.height() - static_cast<int>(rect.height()*m_percentage));
        break;
    }
    painter.fillRect(rect,QBrush(m_color));
}
void ProgressBar::setProgress(float percentage)
{
    m_percentage = percentage;
    if(m_percentage < 0)
        m_percentage = 0;
    else if(m_percentage > 1)
        m_percentage = 1;
}
void ProgressBar::setColor(const QColor color)
{
    m_color = color;
}
void ProgressBar::setVisible(bool isVisible)
{
    m_isVisible = isVisible;
}
void ProgressBar::setRect(const QRect area)
{
    m_area = area;
}
void ProgressBar::setDirection(Direction direction)
{
    m_direction = direction;
}

#include "Buttons/InformativeToolButton.h"

#include <QDebug>

namespace RibbonWidget
{
    InformativeToolButton::InformativeToolButton(RibbonButtonGroup* parent)
        : RibbonButton(parent)
    {
        setup();
    }
    InformativeToolButton::InformativeToolButton(const QString& text,
        const QString& toolTip,
        const QIcon& icon,
        bool enabled,
        RibbonButtonGroup* parent)
        : RibbonButton(text, toolTip, icon, enabled, parent)
    {
        setup();
    }
    InformativeToolButton::InformativeToolButton(const QString& text,
        const QString& toolTip,
        const QString& iconName,
        bool enabled,
        RibbonButtonGroup* parent)
        : RibbonButton(text, toolTip, iconName, enabled, parent)
    {
        setup();
    }

    InformativeToolButton::~InformativeToolButton()
    {
        delete m_updateTimer;
    }
    void InformativeToolButton::setOverlayColor(const QColor& color)
    {
        m_overlayColor = color;
        if (m_overlayEnable)
            this->update();
    }
    void InformativeToolButton::setOverlayEnable(bool enable)
    {
        m_overlayEnable = enable;
        this->update();
    }
    void InformativeToolButton::overlayFlash(float flashSpeed, int flashCount, bool endWithEnabledOverlay)
    {
        m_flashCount = flashCount;
        m_flashSpeed = flashSpeed;
        m_flashEndWithEnabledOverlay = endWithEnabledOverlay;
        if (m_flashEndWithEnabledOverlay)
            m_flashEndPhase = M_PI / 2.f;
        else
            m_flashEndPhase = 0;
        if (m_flashCount < 0)
            m_flashCount = 0;
        if (m_flashCount)
        {
            setOverlayEnable(true);
            m_doFlash = true;
        }
        else
            m_doFlash = false;
        checkForTimerNeeded();
    }

    const QColor& InformativeToolButton::getOverlayColor() const
    {
        return m_overlayColor;
    }
    bool InformativeToolButton::overlayEnabled() const
    {
        return m_overlayEnable;
    }
    void InformativeToolButton::setPercentage(float percentage)
    {

        m_progressBar.setPercentage(percentage);
        if (m_progressBar.getPercentage() > 0)
            m_progressBar.setVisible(true);
        else
            m_progressBar.setVisible(false);
        checkForTimerNeeded();
    }
    float InformativeToolButton::getPercentage() const
    {
        return m_progressBar.getPercentage();
    }
    void InformativeToolButton::enableLoadingCircle(bool enable)
    {
        m_loadingCircle.setVisible(enable);
        checkForTimerNeeded();
        if (enable)
            this->update();
    }
    bool InformativeToolButton::isLoadingCircleEnabled() const
    {
        return m_loadingCircle.isVisible();
    }


    void InformativeToolButton::setup()
    {
        m_overlayColor = QColor(100, 0, 0, 50);
        m_overlayEnable = false;
        m_flashPhase = 0;
        m_flashSpeed = 1;
        m_flashCount = 0;
        m_doFlash = false;
        m_flashEndWithEnabledOverlay = false;
        m_flashEndPhase = 0;

        m_progressBar.setColor(QColor(0, 230, 0, 255));
        m_progressBar.setVisible(false);


        m_updateTimer = new QTimer();
        connect(m_updateTimer, &QTimer::timeout, this, &InformativeToolButton::onUpdateTimer);
        checkForTimerNeeded();
    }
    void InformativeToolButton::paintEvent(QPaintEvent* e)
    {
        QToolButton::paintEvent(e);
        QPainter painter;
        painter.begin(this);
        painter.setRenderHint(QPainter::Antialiasing);
        if (m_overlayEnable)
        {
            QColor col = m_overlayColor;
            if (m_doFlash)
            {
                col.setAlpha(static_cast<int>(m_flashColorFactor * col.alpha()));
            }
            painter.fillRect(QRect(QPoint(0, 0), this->size()), QBrush(col));
        }

        if (m_progressBar.getPercentage() > 0)
        {
            int width = size().width();
            int height = size().height();
            int offset = 10;
            int barWidth = 5;
            QRect rect(QPoint(offset, height - offset - barWidth), QSize(width - 2 * offset, barWidth));
            m_progressBar.setRect(rect);
            /*float percentage = m_progressBar.getPercentage();
            percentage += 0.01;
            if(percentage > 1)
                percentage = 0;
            m_progressBar.setPercentage(percentage);*/
            m_progressBar.draw(painter);
        }

        m_loadingCircle.setCenter(QPoint(size().width() / 2, size().height() / 2));
        m_loadingCircle.draw(painter);

        painter.end();
    }
    void InformativeToolButton::onUpdateTimer()
    {

        if (m_doFlash)
        {
            m_flashColorFactor = sin(m_flashPhase);
            m_flashColorFactor *= m_flashColorFactor;
            m_flashPhase += m_flashSpeed * 10.f / (M_PI * (float)m_updateTimer->interval());
            //qDebug() << m_flashColorFactor << " phase: "<<m_flashPhase;
            if (m_flashPhase >= M_PI)
            {
                m_flashPhase = 0;
                m_flashCount--;
            }
            if (m_flashCount <= 0 && m_flashPhase >= m_flashEndPhase)
            {
                m_flashPhase = m_flashEndPhase;
                m_doFlash = false;
                if (!m_flashEndWithEnabledOverlay)
                    setOverlayEnable(false);
            }
        }


        m_loadingCircle.rotate();
        this->update();
    }
    void InformativeToolButton::activateTimer()
    {
        m_updateTimer->start(20);
    }
    void InformativeToolButton::stopTimer()
    {
        m_updateTimer->stop();
        onUpdateTimer();
    }
    void InformativeToolButton::checkForTimerNeeded()
    {
        if (m_updateTimer->isActive())
        {
            if (!m_overlayEnable &&
                !m_progressBar.isVisible() &&
                !m_loadingCircle.isVisible())
                stopTimer();
        }
        else
        {
            if (m_overlayEnable ||
                m_progressBar.isVisible() ||
                m_loadingCircle.isVisible())
                activateTimer();
        }


    }
}
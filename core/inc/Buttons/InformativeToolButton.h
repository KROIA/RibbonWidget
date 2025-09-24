#pragma once

#include <QToolButton>
#include <QPainter>
#include <QTimer>
#include <QLabel>

#include "RibbonWidget_base.h"
#include "RibbonStructure/ribbonButton.h"
#include "utilities/progressBar.h"
#include "utilities/loadingCircle.h"

namespace RibbonWidget
{
    class RIBBON_WIDGET_API InformativeToolButton : public RibbonButton
    {
        Q_OBJECT
    public:
        InformativeToolButton(RibbonButtonGroup* parent = nullptr);
        InformativeToolButton(const QString& text,
            const QString& toolTip,
            const QIcon& icon,
            bool enabled,
            RibbonButtonGroup* parent = nullptr);
        InformativeToolButton(const QString& text,
            const QString& toolTip,
            const QString& iconName,
            bool enabled,
            RibbonButtonGroup* parent = nullptr);
        ~InformativeToolButton();

        void setOverlayColor(const QColor& color);
        void setOverlayEnable(bool enable);
        void overlayFlash(float flashSpeed, int flashCount = 1, bool endWithEnabledOverlay = false);

        const QColor& getOverlayColor() const;
        bool overlayEnabled() const;

        void setProgressColor(const QColor& color);
        const QColor& getProgressColor() const;
        void setProgress(float percentage);
        float getProgress() const;
        void setProgressBarVerticalOffset(int offset);

        void setLoadingCircleColor(const QColor& color);
        const QColor& getLoadingCircleColor() const;
        void enableLoadingCircle(bool enable);
        bool isLoadingCircleEnabled() const;
        void setLoadingCircleSpeed(float speed);
        float getLoadingCircleSpeed() const;
        void setLoadingCircleAngle(float angle);
        float getLoadingCircleAngle() const;

    private slots:
        void onUpdateTimer();
        void activateTimer();
        void stopTimer();
        void checkForTimerNeeded();

    private:
        void setup();
        void paintEvent(QPaintEvent* e);


        // Overlay
        QColor m_overlayColor;
        bool m_overlayEnable;
        int m_flashCount;
        bool m_doFlash;
        bool m_flashEndWithEnabledOverlay;
        float m_flashSpeed;
        float m_flashPhase;
        float m_flashEndPhase;
        float m_flashColorFactor;
        int m_progressBarVerticalOffset;


        // Loadingbar
        ProgressBar m_progressBar;

        LoadingCircle m_loadingCircle;

        QTimer* m_updateTimer;
    };

}
#pragma once
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <QToolButton>
#include <QPainter>
#include <QTimer>
#include <QLabel>

#include "RW_base.h"
#include "utilities/progressBar.h"
#include "utilities/loadingCircle.h"

class RIBBONWIDGET_EXPORT InformativeToolButton: public QToolButton
{
    Q_OBJECT
    public:
        InformativeToolButton(QWidget *parent = nullptr);
        ~InformativeToolButton();

        void setOverlayColor(const QColor &color);
        void setOverlayEnable(bool enable);
        void overlayFlash(float flashSpeed, int flashCount = 1, bool endWithEnabledOverlay = false);

        const QColor &getOverlayColor() const;
        bool overlayEnabled() const;

        void setPercentage(float percentage);
        float getPercentage() const;

        void enableLoadingCircle(bool enable);
        bool isLoadingCircleEnabled() const;

    private:
        void paintEvent (QPaintEvent *e);

    private slots:
        void onUpdateTimer();
        void activateTimer();
        void stopTimer();
        void checkForTimerNeeded();

	private:
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


        // Loadingbar
        ProgressBar m_progressBar;

        LoadingCircle m_loadingCircle;



        QTimer *m_updateTimer;
};


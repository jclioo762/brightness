#include "lightslider.h"
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>

LightSlider::LightSlider(QWidget *parent)
    : DSlider(Qt::Horizontal, parent),
      m_pressed(false),
      m_timer(new QTimer(this))
{
    setPageStep(50);
    m_timer->setInterval(100);

    connect(m_timer, &QTimer::timeout, this, &LightSlider::onTimeout);
}

void LightSlider::setValue(const int value)
{
    if (m_pressed)
        return;

    blockSignals(true);
    DSlider::setValue(value);
    blockSignals(false);
}

void LightSlider::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (!rect().contains(e->pos()))
            return;
        m_pressed = true;
        DSlider::setValue(maximum() * e->x() / rect().width());
    }
}

void LightSlider::mouseMoveEvent(QMouseEvent *e)
{
    const int value = minimum() + (double((maximum()) - minimum()) * e->x() / rect().width());
    const int normalized = std::max(std::min(maximum(), value), 0);

    DSlider::setValue(normalized);

    blockSignals(true);
    emit valueChanged(normalized);
    blockSignals(false);
}

void LightSlider::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_pressed = false;
        emit requestPlaySoundEffect();
    }
}

void LightSlider::wheelEvent(QWheelEvent *e)
{
    e->accept();

    m_timer->start();

    DSlider::setValue(value() + (e->delta() > 0 ? 2 : -2));
}

void LightSlider::onTimeout()
{
    m_timer->stop();
    emit requestPlaySoundEffect();
}

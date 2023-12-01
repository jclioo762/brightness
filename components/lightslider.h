#ifndef LIGHTSLIDER_H
#define LIGHTSLIDER_H

#include <DSlider>
#include <QTimer>

class LightSlider : public DTK_WIDGET_NAMESPACE::DSlider
{
    Q_OBJECT

public:
    explicit LightSlider(QWidget *parent = 0);

    void setValue(const int value);

signals:
    void requestPlaySoundEffect() const;

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

private slots:
    void onTimeout();

private:
    bool m_pressed;
    QTimer *m_timer;
};

#endif // LightSlider_H

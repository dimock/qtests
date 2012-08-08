#pragma once

#include <QWidget>

class QPixmap;

class PixmapWidget : public QWidget
{
  Q_OBJECT

public:

  PixmapWidget(QWidget * parent = 0);
  ~PixmapWidget();

  void paintEvent(QPaintEvent *);
  void timerEvent(QTimerEvent *);

  void setPixmap(QPixmap & );
  void setAnimationDuration(int ms);
  void setAnimationStepsNum(int);

  /**
    this method starts the animation in given direction:
      0 - don't perform animation, just show finial state
      -1 - animate collapsing
      +1 - animate expansion

    percent - % of image to show at start
   */
  void startAnimation(int direction, int percent);

signals:

  void stopAnimationSignal();

private:

  void stopAnimation();
 
  int durationMs_;
  int percent_;
  int direction_;
  int steps_;
  int timerId_;

  QRectF imageRect_;
  QPointF destPt_;

  QPixmap pixmap_;
};

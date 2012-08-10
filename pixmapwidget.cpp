#include "pixmapwidget.h"

#include <QPainter>
#include <QPixmap>

PixmapWidget::PixmapWidget(QWidget * parent) :
  QWidget(parent),
  durationMs_(0),
  percent_(0),
  direction_(0),
  steps_(1),
  timerId_(0)
{
}

PixmapWidget::~PixmapWidget()
{
}

void PixmapWidget::setPixmap(const QPixmap & pixmap)
{
  pixmap_ = pixmap;
}

void PixmapWidget::paintEvent(QPaintEvent * )
{
  if ( !pixmap_ )
    return;

  QPainter painter(this);
  QImage image = pixmap_.toImage();
  QSize sz = image.size();
  painter.drawImage( destPt_, image, imageRect_ );
}

void PixmapWidget::setAnimationDuration(int ms)
{
  durationMs_ = ms;
  if ( durationMs_ < 0 )
    durationMs_ = 0;
}

void PixmapWidget::setAnimationStepsNum(int steps)
{
  steps_ = steps;
  if ( steps_ < 1 )
    steps_ = 1;
}

void PixmapWidget::startAnimation(int direction, int percent)
{
  direction_ = direction;
  percent_ = percent;

  if ( timerId_ != 0 )
    killTimer(timerId_);

  timerId_ = 0;

  if ( direction_ != 0 )
    timerId_ = startTimer(durationMs_/steps_);

  updateContentSize();
}

void PixmapWidget::stopAnimation()
{
  killTimer(timerId_);
  timerId_ = 0;
  emit stopAnimationSignal();
}

void PixmapWidget::timerEvent(QTimerEvent * )
{
  percent_ += direction_ * 100 / steps_;
  if ( percent_ < 0 )
  {
    percent_ = 0;
    stopAnimation();
  }
  else if ( percent_ > 100 )
  {
    percent_ = 100;
    stopAnimation();
  }

  updateContentSize();
}

void PixmapWidget::updateContentSize()
{
  QImage image = pixmap_.toImage();
  QSize sz = image.size();

  if ( sz.width() == 0 || sz.height() == 0 )
    return;

  int w = sz.width();
  int h = sz.height() * percent_ / 100;
  int x = 0, y = sz.height() - h;

  imageRect_ = QRectF(x, y, w, h);
  destPt_ = QPointF(0, 0);

  resize(imageRect_.size().width(), imageRect_.size().height());

  update();
  updateGeometry();

  //((QWidget*)parent())->updateGeometry();
  //((QWidget*)(parent()->parent()))->updateGeometry();
}

QSize PixmapWidget::sizeHint() const
{
  QSize sz(imageRect_.width(), imageRect_.height());
  return sz;
}

QSize PixmapWidget::minimumSizeHint() const
{
  return sizeHint();
}

#pragma once

#include <QWidget>
#include <QSize>

class QImage;

class TheIcon : public QWidget
{
  Q_OBJECT

public:

  TheIcon(QWidget * parent);

  void paintEvent(QPaintEvent *);

  QSize sizeHint() const;
  QSize minimumSizeHint() const;

private:

  QImage * icons_[2];
};
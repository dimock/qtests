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

  void setPixmap(QPixmap * );

private:
 
  QPixmap * pixmap_;  
};

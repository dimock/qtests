#pragma once

#include <QWidget>

class QImage;
class QLabel;
class QHBoxLayout;
class QPushButton;
class TheIcon;

class TheCaption : public QWidget
{
  Q_OBJECT

public:

  TheCaption(QWidget * parent);

  void paintEvent(QPaintEvent *);

private:

  QHBoxLayout * mainLayout_;
  TheIcon * icon_;
  QLabel * captionLabel_;
};

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
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);
  void mousePressEvent(QMouseEvent *);

private:

signals:

  void expandButton();

private:

  QHBoxLayout * mainLayout_;
  TheIcon * icon_;
  QLabel * captionLabel_;
  QPushButton * closeButton_;
};

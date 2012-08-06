#pragma once

#include <QWidget>
#include <QPolygon>

class QMouseEvent;

class TheWidget : public QWidget
{
  Q_OBJECT;

public:

  TheWidget(QWidget * parent = 0);
  ~TheWidget();

  void mouseMoveEvent(QMouseEvent *);
  void mousePressEvent(QMouseEvent *);
  void paintEvent(QPaintEvent *);

private:

  typedef QVector<QPolygon> PolygonesArray;

  PolygonesArray polygones_;
  QPoint pos_;
};
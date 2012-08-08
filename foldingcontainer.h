#pragma once

#include <QWidget>

class QMouseEvent;
class QVBoxLayout;
class QResizeEvent;
class QPushButton;
class PixmapWidget;

class QFoldingContainer : public QWidget
{
  Q_OBJECT

public:

  QFoldingContainer(QWidget * parent = 0);
  ~QFoldingContainer();

  void enableAnimation(bool enable);
  void setAnimationDuration(int ms);
  void setAnimationStepsNum(int);
  void setContent(QWidget * content);
  bool isCollapsed() const;

public slots:

    void collapse();
    void expand();
    void onCollapsed(bool collapsed);

private:

  void killContent();
  void updateContent(bool start /* starts animation from 100% content visibility */ );

private slots:

  void onStopAnimation();

private:

  QVBoxLayout * mainLayout_, * captionLayout_, * widgetLayout_, * pixmapLayout_;
  QWidget * contentWidget_;
  PixmapWidget * pixmapWidget_;
  QPushButton * collapseButton_;
};

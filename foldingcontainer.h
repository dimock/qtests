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

  void setContent(QWidget * content);

public slots:

    void collapse();
    void expand();
    void onCollapsed(bool collapsed);

private:

  void killContent();
  void updateContent();

private:

  QVBoxLayout * mainLayout_, * captionLayout_, * widgetLayout_, * pixmapLayout_;
  QWidget * contentWidget_;
  PixmapWidget * pixmapWidget_;
  QPushButton * collapseButton_;

  int height_;
  bool collapsed_;
  QPixmap * contentPixmap_;
};

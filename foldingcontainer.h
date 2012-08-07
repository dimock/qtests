#pragma once

#include <QWidget>

class QMouseEvent;
class QVBoxLayout;
class QResizeEvent;
class QPushButton;

class QFoldingContainer : public QWidget
{
  Q_OBJECT

public:

  QFoldingContainer(QWidget * parent = 0);
  ~QFoldingContainer();

  void paintEvent(QPaintEvent *);

  void enableAnimation(bool enable);
  void setAnimationDuration(int ms);

  void setContent(QWidget * content);

public slots:

    void collapse();
    void expand();
    void onCollapsed(bool collapsed);

private:

  void killContent();

  QSize sizeHint() const;

private:

  QVBoxLayout * mainLayout_, * captionLayout_, * contentPanelLayout_, * contentWidgetLayout_;
  QWidget * contentWidget_;
  QWidget * contentPanel_;
  QPushButton * collapseButton_;

  int height_;
  bool collapsed_;
};

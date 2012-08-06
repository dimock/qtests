#pragma once

#include <QWidget>

class QMouseEvent;
class QVBoxLayout;

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
    void onExpanded(bool expanded);

private:

  void killContent();

private:

  QVBoxLayout * mainLayout_, * captionLayout_, * contentLayout_;
  QWidget * contentWidget_;
};

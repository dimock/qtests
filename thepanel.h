#pragma once

#include <QWidget>

class QImage;
class QVBoxLayout;
class QFoldingContainer;
class QPushButton;

class ThePanel : public QWidget
{
  Q_OBJECT

public:

  ThePanel(QWidget * parent);

  void setCaption(const QString &);

private slots:

  void onCollapseExpand(bool);

private:

  QString caption_;
  QImage * stateImages_[2];
  QVBoxLayout * mainLayout_, * captionLayout_, * foldingLayout_;
  QFoldingContainer * foldingContainer_;
  QPushButton * collapseButton_;
};

#pragma once

#include <QWidget>

class QImage;
class QVBoxLayout;
class QFoldingContainer;
class QPushButton;
class TheCaption;

class ThePanel : public QWidget
{
  Q_OBJECT

public:

  ThePanel(QWidget * parent);

  void setCaption(const QString &);
  QFoldingContainer * getFoldingContainer();

private slots:

  void onCollapseExpand();

private:

  TheCaption * caption_;
  QVBoxLayout * mainLayout_, * captionLayout_, * foldingLayout_;
  QFoldingContainer * foldingContainer_;
};

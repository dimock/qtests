#include <QApplication>
#include <QListWidget>
#include "foldingcontainer.h"
#include "thewidget.h"
#include "thepanel.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>

void createMainWindow()
{
  QWidget * mainWdg = new QWidget(0);
  mainWdg->setAttribute(Qt::WA_DeleteOnClose);

  QGridLayout * mainLayout = new QGridLayout(mainWdg);
  mainWdg->setLayout(mainLayout);

  // filling left
  {
    QScrollArea * scrollArea = new QScrollArea(mainWdg);
    QWidget * leftWidget = new QWidget(scrollArea);
    mainLayout->addWidget(scrollArea, 1, 0);
    scrollArea->setWidget(leftWidget);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout * leftWidgetLayout = new QVBoxLayout;
    leftWidget->setLayout(leftWidgetLayout);

    ThePanel * panel1 = new ThePanel(leftWidget);
    leftWidgetLayout->addWidget(panel1);

    QFoldingContainer * qfc1 = panel1->getFoldingContainer();
    if ( qfc1 )
    {
      QListWidget * lw = new QListWidget;

      for (int i = 0; i < 20; ++i)
      {
        QString qstr;
        qstr.sprintf("Item number %d", i);
        lw->addItem(qstr);
      }

      qfc1->setContent(lw);
      qfc1->setAnimationDuration(300);
      qfc1->setAnimationStepsNum(20);
      qfc1->enableAnimation(true);
    }

    leftWidgetLayout->addWidget(panel1);

    ThePanel * panel2 = new ThePanel(leftWidget);
    leftWidgetLayout->addWidget(panel2, 0);

    QFoldingContainer * qfc2 = panel2->getFoldingContainer();
    if ( qfc2 )
    {
      TheWidget * tw = new TheWidget;
      qfc2->setContent(tw);
      qfc2->setAnimationDuration(300);
      qfc2->setAnimationStepsNum(20);
      qfc2->enableAnimation(true);
    }

    leftWidgetLayout->addStretch(1);

    leftWidget->adjustSize();
  }

  // filling center
  {
    QWidget * centerWidget = new QWidget(mainWdg);
    mainLayout->addWidget(centerWidget, 1, 1);

    QVBoxLayout * centerWidgetLayout = new QVBoxLayout;
    centerWidget->setLayout(centerWidgetLayout);

    ThePanel * panel1 = new ThePanel(centerWidget);
    centerWidgetLayout->addWidget(panel1);

    QFoldingContainer * qfc1 = panel1->getFoldingContainer();
    if ( qfc1 )
    {
      QListWidget * lw = new QListWidget;

      for (int i = 0; i < 20; ++i)
      {
        QString qstr;
        qstr.sprintf("Item number %d", i);
        lw->addItem(qstr);
      }

      qfc1->setContent(lw);
      qfc1->setAnimationDuration(300);
      qfc1->setAnimationStepsNum(20);
      qfc1->enableAnimation(true);
    }

    centerWidgetLayout->addWidget(panel1);

    ThePanel * panel2 = new ThePanel(centerWidget);
    centerWidgetLayout->addWidget(panel2, 0);

    QFoldingContainer * qfc2 = panel2->getFoldingContainer();
    if ( qfc2 )
    {
      TheWidget * tw = new TheWidget;
      qfc2->setContent(tw);
      qfc2->setAnimationDuration(300);
      qfc2->setAnimationStepsNum(20);
      qfc2->enableAnimation(true);
    }

    centerWidgetLayout->addStretch(1);

    centerWidget->adjustSize();
  }


  // filling right
  {
    QWidget * rightWidget = new QWidget(mainWdg);
    mainLayout->addWidget(rightWidget, 1, 2);

    QVBoxLayout * rightWidgetLayout = new QVBoxLayout;
    rightWidget->setLayout(rightWidgetLayout);

    ThePanel * panel1 = new ThePanel(rightWidget);
    rightWidgetLayout->addWidget(panel1);

    QFoldingContainer * qfc1 = panel1->getFoldingContainer();
    if ( qfc1 )
    {
      QListWidget * lw = new QListWidget;

      for (int i = 0; i < 60; ++i)
      {
        QString qstr;
        qstr.sprintf("Item number %d", i);
        lw->addItem(qstr);
      }

      qfc1->setContent(lw);
      qfc1->setAnimationDuration(1000);
      qfc1->setAnimationStepsNum(50);
      qfc1->enableAnimation(true);
    }

    rightWidgetLayout->addWidget(panel1);

    rightWidget->adjustSize();
  }

  mainWdg->adjustSize();
  mainWdg->show();
}

int main(int argn, char * argv[])
{
  QApplication qapp(argn, argv);

  createMainWindow();

  qapp.exec();
}

#pragma once

#include <QComboBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QMainWindow>
#include <QPixmap>

#include "../Controller/controller.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();

 private:
  void PlaceWidgets();
  void ConnectWidgets();

  enum class Mode{
    kLight,
    kPolygons
  };

  Mode mode_;

  QWidget* widget_;
  QGridLayout* layout_;

  QComboBox* mode_selector_;

  QPixmap pixmap_{800, 600};

  QGraphicsScene* scene_;
  QGraphicsView* view_;

  Controller controller_;
};

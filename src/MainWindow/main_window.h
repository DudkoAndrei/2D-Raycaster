#pragma once

#include <QComboBox>
#include <QGridLayout>
#include <QMainWindow>
#include <vector>

#include "../Controller/controller.h"
#include "../PaintWidget/paint_widget.h"

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

  PaintWidget* paint_widget_;

  std::vector<QPointF> points_;
  Polygon light_area_;

  Controller controller_;
};

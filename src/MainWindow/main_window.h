#pragma once

#include <QComboBox>
#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <vector>

#include "../AreaSettingsDialog/area_settings.h"
#include "../Controller/controller.h"
#include "../PaintWidget/paint_widget.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();

  void paintEvent(QPaintEvent* event) override;

 private:
  void PlaceWidgets();
  void ConnectWidgets();

  enum class Mode{
    kPolygons,
    kLight,
    kStaticLight
  };

  Mode mode_ = Mode::kPolygons;

  QWidget* widget_;
  QGridLayout* layout_;

  QComboBox* mode_selector_;

  PaintWidget* paint_widget_;

  QPushButton* button_;

  std::vector<Polygon> light_areas_;

  Controller controller_;

  AreaSettings settings_;
};

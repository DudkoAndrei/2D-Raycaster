#include "main_window.h"

#include <QPainter>
#include <utility>

MainWindow::MainWindow()
    : widget_(new QWidget(this)),
      layout_(new QGridLayout(widget_)),
      mode_selector_(new QComboBox(widget_)),
      paint_widget_(new PaintWidget(widget_)) {
  PlaceWidgets();
  ConnectWidgets();

  setCentralWidget(widget_);
}

void MainWindow::PlaceWidgets() {
  layout_->addWidget(paint_widget_, 0, 0, 1, 2);
  layout_->addWidget(mode_selector_, 1, 0, 1, 1);

  widget_->setLayout(layout_);
}

void MainWindow::ConnectWidgets() {
  connect(mode_selector_, &QComboBox::currentIndexChanged, [&](int index) {
    mode_ = static_cast<Mode>(index);

    points_.clear();
  });

  connect(paint_widget_, &PaintWidget::MouseLeftClicked, [&](
      const QPointF& point) {
    if (mode_ == Mode::kPolygons) {
      points_.push_back(point);
    }
  });

  connect(paint_widget_, &PaintWidget::MouseRightClicked, [&](
      const QPointF& point) {
    if (mode_ == Mode::kPolygons) {
      if (controller_.Polygons().empty()) {
        InitializeController();
      }
      if(!points_.empty()) {
        controller_.AddPolygon(Polygon(std::move(points_)));
        points_.clear();

        repaint();
      }
    }
  });

  connect(paint_widget_, &PaintWidget::MouseMoved, [&](const QPointF& point) {
    if (mode_ == Mode::kLight) {
      controller_.SetLightSource(point);
      light_area_ = controller_.CreateLightArea();

      repaint();
    }
  });
}

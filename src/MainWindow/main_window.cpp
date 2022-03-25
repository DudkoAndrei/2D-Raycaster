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

  mode_selector_->addItem("Polygons");
  mode_selector_->addItem("Light");

  setFixedSize(screen()->availableSize() * 0.8);

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
  });

  connect(paint_widget_, &PaintWidget::MouseLeftClicked, [&](
      const QPointF& point) {
    if (mode_ == Mode::kPolygons) {
      if (controller_.Polygons().empty()) {
        InitializeController();
        controller_.AddPolygon({});
      }
      controller_.AddVertexToLastPolygon(point);
      light_areas_ = controller_.CreateLightAreas();

      repaint();
    }
  });

  connect(paint_widget_, &PaintWidget::MouseRightClicked, [&](
      const QPointF& point) {
    if (mode_ == Mode::kPolygons) {
      if (controller_.Polygons().empty()) {
        InitializeController();
      }
      controller_.AddPolygon({});
    }
  });

  connect(paint_widget_, &PaintWidget::MouseMoved, [&](const QPointF& point) {
    if (controller_.Polygons().empty()) {
      InitializeController();
      controller_.AddPolygon({});
    }
    if (mode_ == Mode::kLight) {
      controller_.SetLightSource(point);
      light_areas_ = controller_.CreateLightAreas();

      repaint();
    }
  });
}

void MainWindow::paintEvent(QPaintEvent* event) {
  QPainter painter(this);

  paint_widget_->Paint(
      &painter,
      controller_.Polygons(),
      light_areas_);
}

void MainWindow::InitializeController() {
  double view_width = paint_widget_->width();
  double view_height = paint_widget_->height();

  std::vector<QPointF> polygon
      {{0, 0}, {view_width, 0}, {view_width, view_height},
       {0, view_height}};

  controller_.AddPolygon(Polygon(std::move(polygon)));
}


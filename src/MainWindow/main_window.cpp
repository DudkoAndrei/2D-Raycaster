#include "main_window.h"

#include <QPainter>

#include "../AreaSettingsDialog/area_settings_dialog.h"

MainWindow::MainWindow()
    : widget_(new QWidget(this)),
      layout_(new QGridLayout(widget_)),
      mode_selector_(new QComboBox(widget_)),
      button_ (new QPushButton("Settings", widget_)),
      paint_widget_(new PaintWidget(widget_)) {
  PlaceWidgets();
  ConnectWidgets();

  mode_selector_->addItem("Polygons");
  mode_selector_->addItem("Light");
  mode_selector_->addItem("Static Light");

  setFixedSize(screen()->availableSize() * 0.8);

  setCentralWidget(widget_);
}

void MainWindow::PlaceWidgets() {
  layout_->addWidget(paint_widget_, 0, 0, 1, 2);
  layout_->addWidget(mode_selector_, 1, 0);
  layout_->addWidget(button_, 1, 1);

  widget_->setLayout(layout_);
}

void MainWindow::ConnectWidgets() {
  connect(mode_selector_, &QComboBox::currentIndexChanged, [&](int index) {
    mode_ = static_cast<Mode>(index);
  });

  connect(paint_widget_, &PaintWidget::MouseLeftClicked, [&](
      const QPointF& point) {
    switch (mode_) {
      case Mode::kPolygons: {
        controller_.AddVertexToLastPolygon(point);

        repaint();
        break;
      }
      case Mode::kStaticLight: {
        controller_.AddStaticLightSource(point);

        repaint();
        break;
      }
      default: {}
    }
  });

  connect(paint_widget_, &PaintWidget::MouseRightClicked, [&](
      const QPointF& point) {
    if (mode_ == Mode::kPolygons) {
      controller_.AddPolygon({});
    }
  });

  connect(paint_widget_, &PaintWidget::MouseMoved, [&](const QPointF& point) {
    if (mode_ == Mode::kLight) {
      controller_.SetLightSource(point);

      repaint();
    }
  });

  connect(button_, &QPushButton::clicked, [&](){
    AreaSettingsDialog dialog(this, settings_);
    dialog.exec();

    settings_ = dialog.Settings();

    controller_.SetFuzzyPointsCount(settings_.fuzzy_points_count);
    controller_.SetLightSourceRadius(settings_.light_source_radius);
  });
}

void MainWindow::paintEvent(QPaintEvent* event) {
  if (!controller_.HasPolygons()) {
    controller_.SetBounds(paint_widget_->size().width(),
                          paint_widget_->size().height());
  }

  QPainter painter(this);

  paint_widget_->Paint(
      &painter,
      controller_.Polygons(),
      controller_.LightAreas(),
      controller_.StaticLightSources(),
      settings_,
      controller_.HasLightSource());
}

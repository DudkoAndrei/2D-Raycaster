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
}

#include "main_window.h"

MainWindow::MainWindow() :
    widget_(new QWidget(this)),
    layout_(new QGridLayout(widget_)),
    mode_selector_(new QComboBox(widget_)),
    scene_(new QGraphicsScene(widget_)),
    view_(new QGraphicsView(scene_, widget_)) {
  resize(1000, 800);

  PlaceWidgets();
  ConnectWidgets();

  setCentralWidget(widget_);
}

void MainWindow::PlaceWidgets() {
  layout_->addWidget(view_, 0, 0, 1, 2);
  layout_->addWidget(mode_selector_, 1, 0, 1, 1);

  widget_->setLayout(layout_);
}

void MainWindow::ConnectWidgets() {
}

#include "paint_widget.h"

PaintWidget::PaintWidget(QWidget* parent) : QWidget(parent) {
  setMouseTracking(true);
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event) {
  QWidget::mouseMoveEvent(event);

  emit MouseMoved(event->position());
}

void PaintWidget::mousePressEvent(QMouseEvent* event) {
  QWidget::mousePressEvent(event);

  switch (event->button()) {
    case Qt::LeftButton: {
      emit MouseLeftClicked(event->position());

      break;
    }
    case Qt::RightButton: {
      emit MouseRightClicked(event->position());

      break;
    }
    default: {}
  }
}

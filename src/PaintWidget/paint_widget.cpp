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

void PaintWidget::Paint(
    QPainter* painter,
    const std::vector<Polygon>& polygons,
    const Polygon& light_area) {
  painter->save();

  painter->translate(pos());
  painter->fillRect(0, 0, width(), height(), Qt::black);

  painter->setPen(Qt::white);
  painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));

  painter->drawConvexPolygon(light_area.Vertices().data(), light_area.Size());

  painter->setPen(QPen(Qt::gray, 2));
  painter->setBrush(QBrush(Qt::NoBrush));

  for (const auto& polygon : polygons) {
    painter->drawConvexPolygon(polygon.Vertices().data(), polygon.Size());
  }

  painter->restore();
}

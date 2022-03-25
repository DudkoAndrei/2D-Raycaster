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
    const std::vector<Polygon>& light_areas) {
  painter->save();

  painter->translate(pos());
  painter->fillRect(0, 0, width(), height(), QColorConstants::Black);

  if (!light_areas.empty()) {
    QColor white = QColorConstants::White;

    white.setAlphaF(1.0 / light_areas.size());

    painter->setPen(QColorConstants::Transparent);
    painter->setBrush(QBrush(white, Qt::SolidPattern));

    for (const auto& light_area : light_areas) {
      painter->drawConvexPolygon(light_area.Vertices().data(),
                                 light_area.Size());
    }
  }

  painter->setPen(QPen(QColorConstants::DarkGray, 2));
  painter->setBrush(QBrush(Qt::NoBrush));

  for (const auto& polygon : polygons) {
    painter->drawConvexPolygon(polygon.Vertices().data(), polygon.Size());
  }

  painter->restore();
}

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
    const std::vector<Polygon>& light_areas,
    size_t count) {
  painter->save();

  painter->translate(pos());
  painter->fillRect(0, 0, width(), height(), QColorConstants::Black);

  if (!light_areas.empty()) {
    QColor main_color = QColorConstants::White.toExtendedRgb();

    main_color.setAlphaF(1.0 / (count + 1));

    QColor static_color = QColorConstants::DarkGray;

    static_color.setAlphaF(0.5 / (count + 1));

    painter->setPen(QColorConstants::Transparent);
    painter->setBrush(QBrush(main_color, Qt::SolidPattern));

    for (size_t i = 0; i < light_areas.size(); ++i) {
      painter->drawConvexPolygon(light_areas[i].Vertices().data(),
                                 light_areas[i].Size());
      if (i == count) {
        painter->setBrush(QBrush(static_color, Qt::SolidPattern));
      }
    }
  }

  painter->setPen(QPen(QColorConstants::DarkBlue, 2));
  painter->setBrush(QBrush(Qt::NoBrush));

  for (const auto& polygon : polygons) {
    painter->drawConvexPolygon(polygon.Vertices().data(), polygon.Size());
  }

  painter->restore();
}

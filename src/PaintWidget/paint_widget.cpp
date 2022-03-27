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
    const std::vector<QPointF>& static_points,
    const AreaSettings& settings,
    bool has_nonstatic_light) {
  painter->save();

  float alpha_value = 1.0 / (settings.fuzzy_points_count + 2);

  painter->translate(pos());
  painter->fillRect(0, 0, width(), height(), settings.background_color);

  if (!light_areas.empty()) {
    QColor main_color = settings.light_color;

    main_color.setAlphaF(alpha_value);

    QColor static_color = settings.static_light_color;

    static_color.setAlphaF(alpha_value);

    painter->setPen(QColorConstants::Transparent);
    if (has_nonstatic_light) {
      painter->setBrush(QBrush(main_color.toExtendedRgb(), Qt::SolidPattern));
    } else {
      painter->setBrush(QBrush(static_color.toExtendedRgb(), Qt::SolidPattern));
    }
    for (size_t i = 0; i < light_areas.size(); ++i) {
      painter->drawConvexPolygon(light_areas[i].Vertices().data(),
                                 light_areas[i].Size());

      if (i == settings.fuzzy_points_count) {
        painter->setBrush(QBrush(static_color.toExtendedRgb(),
                                 Qt::SolidPattern));
      }
    }
  }

  painter->setPen(QPen(settings.polygons_color, 2));

  painter->setBrush(settings.static_light_color);
  for (const auto& point : static_points) {
    painter->drawEllipse(point, 5, 5);
  }

  painter->setBrush(QBrush(Qt::NoBrush));

  for (const auto& polygon : polygons) {
    painter->drawConvexPolygon(polygon.Vertices().data(), polygon.Size());
  }

  painter->restore();
}

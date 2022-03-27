#pragma once

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include <vector>

#include "../AreaSettingsDialog/area_settings.h"
#include "../Polygon/polygon.h"

class PaintWidget : public QWidget {
  Q_OBJECT
 public:
  explicit PaintWidget(QWidget* parent = nullptr);

  void mouseMoveEvent(QMouseEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;

  void Paint(
      QPainter* painter,
      const std::vector<Polygon>& polygons,
      const std::vector<Polygon>& light_areas,
      const std::vector<QPointF>& static_points,
      const AreaSettings& settings,
      bool has_nonstatic_light);
 signals:
  void MouseMoved(QPointF point);

  void MouseLeftClicked(QPointF point);
  void MouseRightClicked(QPointF point);
};

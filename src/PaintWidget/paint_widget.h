#pragma once

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include <vector>

#include "../Polygon/polygon.h"

class PaintWidget : public QWidget {
  Q_OBJECT
 public:
  explicit PaintWidget(QWidget* parent = nullptr);

  void Paint(
      QPainter* painter,
      const std::vector<Polygon>& polygons,
      const Polygon& light_area_);

 signals:
  void MouseMoved(QPointF point);
  void MouseLeftClicked(QPointF point);
  void MouseRightClicked(QPointF point);

 private:
  void mouseMoveEvent(QMouseEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
};

#pragma once

#include <vector>

#include "../Polygon/polygon.h"

class Controller {
 public:
  Controller() = default;

  const std::vector<Polygon>& Polygons() const;

  const QPointF& LightSource() const;
  void SetLightSource(const QPointF& light_source);

 private:
  std::vector<Polygon> polygons_;
  QPointF light_source_;
};

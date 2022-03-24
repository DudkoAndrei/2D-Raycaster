#pragma once

#include <vector>

#include "../Polygon/polygon.h"

class Controller {
 public:
  Controller() = default;

 private:
  std::vector<Polygon> polygons_;
  QPointF light_source_;
};

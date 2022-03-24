#pragma once

#include <QPointF>
#include <vector>

class Polygon {
 public:
  Polygon() = default;
  explicit Polygon(std::vector<QPointF> vertices);

 private:
  std::vector<QPointF>  vertices_;
};


#pragma once

#include <QPointF>
#include <vector>

class Polygon {
 public:
  Polygon() = default;
  explicit Polygon(std::vector<QPointF> vertices);

  const QPointF& operator[](size_t idx) const;

  size_t Size() const;

 private:
  std::vector<QPointF>  vertices_;
};


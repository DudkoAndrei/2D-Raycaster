#pragma once

#include <optional>
#include <QPointF>
#include <utility>
#include <vector>

#include "../Ray/ray.h"

class Polygon {
 public:
  Polygon() = default;
  explicit Polygon(std::vector<QPointF> vertices);

  const QPointF& operator[](size_t idx) const;
  const std::vector<QPointF>& Vertices() const;

  size_t Size() const;

  void AddVertex(const QPointF& vertex);
  void UpdateLastVertex(const QPointF& vertex);

  std::optional<QPointF> IntersectRay(const Ray& ray) const;

 private:
  static std::optional<std::pair<QPointF, double>> GetIntersection(
      const Ray& ray,
      const QPointF& line_begin,
      const QPointF& line_end);
  static bool IsParallel(
      const QPointF& first_direction,
      const QPointF& second_direction);

  std::vector<QPointF> vertices_;
};


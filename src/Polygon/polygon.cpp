#include "polygon.h"

Polygon::Polygon(std::vector<QPointF> vertices)
    : vertices_(std::move(vertices)) {}

const QPointF& Polygon::operator[](size_t idx) const {
  Q_ASSERT(0 <= idx && idx <= vertices_.size());

  if (idx == vertices_.size()) {
    return vertices_[0];
  }

  return vertices_[idx];
}

size_t Polygon::Size() const {
  return vertices_.size();
}

void Polygon::AddVertex(const QPointF& vertex) {
  vertices_.push_back(vertex);
}

void Polygon::UpdateLastVertex(const QPointF& vertex) {
  vertices_.back() = vertex;
}

std::optional<QPointF> Polygon::IntersectRay(const Ray& ray) const {
  std::optional<QPointF> result;
  std::optional<double> length;

  for (size_t i = 0; i < vertices_.size(); ++i) {
    auto temp = GetIntersection(ray, operator[](i), operator[](i + 1));

    if (temp.has_value() && (!result.has_value() || temp->second < length)) {
      result = temp->first;
      length = temp->second;
    }
  }

  return result;
}

std::optional<std::pair<QPointF, double>> Polygon::GetIntersection(
    const Ray& ray,
    const QPointF& line_begin,
    const QPointF& line_end) {
  QPointF line_direction = line_end - line_begin;

  if (IsParallel(ray.Direction(), line_direction)) {
    return std::nullopt;
  }

  // intersection_point = ray.Begin + ray.Direction() * T1
  // intersection_point = line_begin + line_direction * T2

  double t2 = (ray.Direction().x() * (line_begin.y() - ray.Begin().y())
      + ray.Direction().y() * (ray.Begin().x() - line_begin.x()))
      / (line_direction.x() * ray.Direction().y()
          - line_direction.y() * ray.Direction().x());

  double t1 =
      (line_begin.x() + line_direction.x() * t2 - ray.Begin().x())
          / ray.Direction().x();

  if (t1 > 0 && 0 < t2 && t2 < 1) {
    return std::make_pair(ray.Begin() + ray.Direction() * t1, t1);
  }

  return std::nullopt;
}

bool Polygon::IsParallel(const QPointF& first_direction,
                         const QPointF& second_direction) {
  return first_direction.x() * second_direction.y()
      - second_direction.x() * first_direction.y() == 0;
}

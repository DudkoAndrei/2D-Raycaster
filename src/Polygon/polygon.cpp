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

const std::vector<QPointF>& Polygon::Vertices() const {
  return vertices_;
}

size_t Polygon::Size() const {
  return vertices_.size();
}

void Polygon::AddVertex(const QPointF& vertex) {
  vertices_.push_back(vertex);
}

void Polygon::UpdateLastVertex(const QPointF& vertex) {
  Q_ASSERT(!vertices_.empty());

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

  if (AreParallel(ray.Direction(), line_direction)) {
    return std::nullopt;
  }

  // intersection_point = ray.Begin + ray.Direction() * intersected_length
  // intersection_point = line_begin + line_direction * ray_length

  double intersected_length =
      (ray.Direction().x() * (line_begin.y() - ray.Begin().y())
          + ray.Direction().y() * (ray.Begin().x() - line_begin.x()))
          / (line_direction.x() * ray.Direction().y()
              - line_direction.y() * ray.Direction().x());

  double ray_length = (line_begin.x() + line_direction.x() * intersected_length
      - ray.Begin().x()) / ray.Direction().x();

  double kEps = 1e-9;

  if (ray_length < -kEps || intersected_length < -kEps
      || intersected_length > 1.0 + kEps) {
    return std::nullopt;
  }

  return std::make_pair(ray.Begin() + ray.Direction() * ray_length, ray_length);
}

bool Polygon::AreParallel(const QPointF& first_direction,
                          const QPointF& second_direction) {
  return std::fabs(first_direction.x() * second_direction.y()
                       - second_direction.x() * first_direction.y()) < 1e-9;
}

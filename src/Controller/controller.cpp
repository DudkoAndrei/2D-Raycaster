#include "controller.h"

#include <algorithm>
#include <cmath>
#include <utility>

const std::vector<Polygon>& Controller::Polygons() const {
  return polygons_;
}

const QPointF& Controller::LightSource() const {
  return light_source_;
}

void Controller::SetLightSource(const QPointF& light_source) {
  light_source_ = light_source;
}

void Controller::AddPolygon(Polygon polygon) {
  polygons_.push_back(std::move(polygon));
}

void Controller::AddVertexToLastPolygon(const QPointF& vertex) {
  polygons_.back().AddVertex(vertex);
}

void Controller::UpdateLastPolygon(const QPointF& vertex) {
  polygons_.back().UpdateLastVertex(vertex);
}

std::vector<Ray> Controller::CastRays() const {
  std::vector<Ray> result;

  for (const auto& polygon : polygons_) {
    for (size_t i = 0; i < polygon.Size(); ++i) {
      result.emplace_back(light_source_, polygon[i]);
      result.push_back(result.back().Rotate(0.0001));
      result.push_back(result.back().Rotate(-0.0002));
    }
  }

  std::sort(result.begin(), result.end());

  return result;
}

std::vector<QPointF> Controller::IntersectRays(
    const std::vector<Ray>& rays) const {
  std::vector<QPointF> result;

  for (const auto& ray : rays) {
    std::optional<QPointF> temp_point;
    std::optional<double> temp_point_length;

    for (const auto& polygon : polygons_) {
      auto temp = polygon.IntersectRay(ray);
      std::optional<double> length;

      if (temp.has_value()) {
        length = GetLineLength(light_source_, temp.value());

        if (!temp_point.has_value() || length < temp_point_length) {
          temp_point = temp;
          temp_point_length = length;
        }
      }
    }

    if (temp_point.has_value()) {
      result.push_back(temp_point.value());
    }
  }

  return result;
}

double Controller::GetLineLength(const QPointF& a, const QPointF& b) {
  return std::sqrt(
      (a.x() - b.x()) * (a.x() - b.x()) + (a.x() - b.x()) * (a.x() - b.x()));
}

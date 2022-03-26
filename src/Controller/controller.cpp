#include "controller.h"

#include <algorithm>
#include <cmath>
#include <utility>

const std::vector<Polygon>& Controller::Polygons() const {
  return polygons_;
}

const QPointF& Controller::LightSource() const {
  Q_ASSERT(!light_sources_.empty());

  return light_sources_[static_light_sources_.size()];
}

void Controller::SetLightSource(
    const QPointF& light_source,
    size_t count,
    double light_radius) {
  light_sources_ = static_light_sources_;
  light_sources_.push_back(light_source);

  Ray temp(light_source, 0);

  double angle = 2.0 * std::numbers::pi / count;

  for (int i = 0; i < count; ++i) {
    light_sources_.push_back(light_source + temp.Direction() * light_radius);
    temp = temp.Rotate(angle);
  }
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

std::vector<std::vector<Ray>> Controller::CastRays() const {
  std::vector<std::vector<Ray>> result(light_sources_.size());

  for (size_t i = 0; i < light_sources_.size(); ++i) {
    for (const auto& polygon : polygons_) {
      for (size_t j = 0; j < polygon.Size(); ++j) {
        result[i].emplace_back(light_sources_[i], polygon[j]);
        result[i].push_back(result[i].back().Rotate(0.0001));
        result[i].push_back(result[i].back().Rotate(-0.0002));
      }
    }

    std::sort(result[i].begin(), result[i].end());
  }

  return result;
}

std::vector<std::vector<QPointF>> Controller::IntersectRays(
    const std::vector<std::vector<Ray>>& rays) const {
  std::vector<std::vector<QPointF>> result(rays.size());

  for (size_t i = 0; i < rays.size(); ++i) {
    for (const auto& ray : rays[i]) {
      std::optional<QPointF> temp_point;
      std::optional<double> temp_point_length;

      for (const auto& polygon : polygons_) {
        auto temp = polygon.IntersectRay(ray);
        std::optional<double> length;

        if (temp.has_value()) {
          length = GetLineLength(light_sources_[i], temp.value());

          if (!temp_point.has_value() || length < temp_point_length) {
            temp_point = temp;
            temp_point_length = length;
          }
        }
      }

      if (temp_point.has_value()) {
        result[i].push_back(temp_point.value());
      }
    }
  }

  return result;
}

double Controller::GetLineLength(const QPointF& a, const QPointF& b) {
  return std::sqrt(
      (a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}

void Controller::RemoveAdjacentPoints(
    std::vector<std::vector<QPointF>>* points) {
  for (size_t i = 0; i < points->size(); ++i) {
    if (!points[i].empty()) {
      for (size_t j = points->operator[](i).size() - 1; j > 0; --j) {
        if (GetLineLength(points->operator[](i)[j],
                          points->operator[](i)[j - 1]) < 1e-9) {
          points->operator[](i).pop_back();
        }
      }
    }
  }
}

std::vector<Polygon> Controller::CreateLightAreas() const {
  std::vector<Polygon> result;
  result.reserve(light_sources_.size());
  std::vector<std::vector<QPointF>> temp = IntersectRays(CastRays());

  RemoveAdjacentPoints(&temp);

  for (auto& points : temp) {
    result.emplace_back(std::move(points));
  }

  return result;
}

void Controller::AddStaticLightSource(const QPointF& light_source) {
  static_light_sources_.push_back(light_source);
}

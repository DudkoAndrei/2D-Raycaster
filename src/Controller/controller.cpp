#include "controller.h"

#include <algorithm>
#include <cmath>
#include <utility>

const std::vector<Polygon>& Controller::Polygons() const {
  return polygons_;
}

const QPointF& Controller::LightSource() const {
  Q_ASSERT(light_source_.has_value());

  return light_source_.value();
}

bool Controller::HasLightSource() const {
  return light_source_.has_value();
}

void Controller::SetLightSource(
    const QPointF& light_source) {
  light_source_ = light_source;

  UpdateLightAreas();
}

void Controller::AddPolygon(Polygon polygon) {
  polygons_.push_back(std::move(polygon));

  UpdateLightAreas();
}

void Controller::AddVertexToLastPolygon(const QPointF& vertex) {
  polygons_.back().AddVertex(vertex);

  UpdateLightAreas();
}

void Controller::UpdateLastPolygon(const QPointF& vertex) {
  polygons_.back().UpdateLastVertex(vertex);

  UpdateLightAreas();
}

std::vector<std::vector<Ray>> Controller::CastRays() const {
  std::vector<std::vector<Ray>> result(fuzzy_light_sources_.size());

  for (size_t i = 0; i < fuzzy_light_sources_.size(); ++i) {
    for (const auto& polygon : polygons_) {
      for (size_t j = 0; j < polygon.Size(); ++j) {
        result[i].emplace_back(fuzzy_light_sources_[i], polygon[j]);
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
          length = GetLineLength(fuzzy_light_sources_[i], temp.value());

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

void Controller::UpdateLightAreas() {
  fuzzy_light_sources_.clear();

  if (light_source_.has_value()) {
    AddFuzzyLightSource(light_source_.value());
  }

  for (const auto& light_source : static_light_sources_) {
    AddFuzzyLightSource(light_source);
  }

  light_areas_.clear();
  light_areas_.reserve(fuzzy_light_sources_.size());
  std::vector<std::vector<QPointF>> temp = IntersectRays(CastRays());

  RemoveAdjacentPoints(&temp);

  for (auto& points : temp) {
    light_areas_.emplace_back(std::move(points));
  }
}

void Controller::AddStaticLightSource(
    const QPointF& light_source) {
  static_light_sources_.push_back(light_source);

  UpdateLightAreas();
}

void Controller::AddFuzzyLightSource(
    const QPointF& source) {
  fuzzy_light_sources_.push_back(source);

  Ray temp(source, 0);

  double angle = 2.0 * std::numbers::pi / fuzzy_points_count_;

  for (int i = 0; i < fuzzy_points_count_; ++i) {
    fuzzy_light_sources_.push_back(
        source + temp.Direction() * light_source_radius_);
    temp = temp.Rotate(angle);
  }
}

size_t Controller::FuzzyPointsCount() const {
  return fuzzy_points_count_;
}

void Controller::SetFuzzyPointsCount(size_t count) {
  fuzzy_points_count_ = count;

  UpdateLightAreas();
}

double Controller::LightSourceRadius() const {
  return light_source_radius_;
}

void Controller::SetLightSourceRadius(double radius) {
  light_source_radius_ = radius;

  UpdateLightAreas();
}

const std::vector<Polygon>& Controller::LightAreas() const {
  return light_areas_;
}

void Controller::SetBounds(const QSize& size) {
  double width = size.width();
  double height = size.height();

  Polygon bounds({{0, 0}, {width, 0}, {width, height}, {0, height}});

  if (polygons_.empty()) {
    AddPolygon(bounds);
    polygons_.emplace_back();
  } else {
    polygons_[0] = bounds;
  }

  UpdateLightAreas();
}

bool Controller::HasPolygons() const {
  return !polygons_.empty();
}

const std::vector<QPointF> Controller::StaticLightSources() const {
  return static_light_sources_;
}

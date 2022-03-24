#include "controller.h"

#include <algorithm>
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

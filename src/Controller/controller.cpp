#include "controller.h"

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

#include "controller.h"

const std::vector<Polygon>& Controller::Polygons() const {
  return polygons_;
}

const QPointF& Controller::LightSource() const {
  return light_source_;
}

void Controller::SetLightSource(const QPointF& light_source) {
  light_source_ = light_source;
}

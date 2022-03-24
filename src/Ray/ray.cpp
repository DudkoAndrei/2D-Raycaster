#include "ray.h"

#include <cmath>

Ray::Ray(const QPointF& begin, const QPointF& end)
    : begin_(begin), direction_(end - begin), angle_(GetAngle(direction_)) {}

Ray::Ray(const QPointF& begin, double angle)
    : begin_(begin), angle_(angle),
      direction_(std::cos(angle), std::sin(angle)) {}

double Ray::GetAngle(const QPointF& point) {
  double angle;

  if (point.x() == 0) {
    if (point.y() > 0) {
      angle = std::asin(1);
    } else {
      angle = std::asin(-1);
    }
  } else {
    angle = std::atan(point.y() / point.x());
  }

  if (angle < 0) {
    angle += 2.0 * std::acos(-1);
  }

  return angle;
}

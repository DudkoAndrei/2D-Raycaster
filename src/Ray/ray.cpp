#include "ray.h"

#include <cmath>
#include <numbers>

Ray::Ray(const QPointF& begin, const QPointF& end)
    : angle_(GetAngle(end - begin)),
      begin_(begin),
      direction_(GetDirection(angle_)) {}

Ray::Ray(const QPointF& begin, double angle)
    : angle_(angle), begin_(begin), direction_(GetDirection(angle)) {
  while (angle_ < 0) {
    angle += 2.0 * std::numbers::pi;
  }
  while (angle >= 2.0 * std::numbers::pi) {
    angle -= 2.0 * std::numbers::pi;
  }
}

double Ray::GetAngle(const QPointF& point) {
  double angle;

  if (point.x() == 0) {
    if (point.y() > 0) {
      angle = std::numbers::pi / 2.0;
    } else {
      angle = -std::numbers::pi / 2.0;
    }
  } else {
    angle = std::atan2(point.y(), point.x());
  }

  if (angle < 0) {
    angle += 2.0 * std::numbers::pi;
  }

  return angle;
}

const QPointF& Ray::Begin() const {
  return begin_;
}

const QPointF& Ray::Direction() const {
  return direction_;
}

double Ray::Angle() const {
  return angle_;
}

void Ray::SetBegin(const QPointF& point) {
  begin_ = point;
}

void Ray::SetDirection(const QPointF& point) {
  angle_ = GetAngle(point);
  direction_ = GetDirection(angle_);
}

void Ray::SetAngle(double angle) {
  angle_ = angle;
  direction_ = GetDirection(angle_);
}

Ray Ray::Rotate(double angle) const {
  return {begin_, angle_ + angle};
}

std::partial_ordering Ray::operator<=>(const Ray& rhs) const {
  return angle_ <=> rhs.angle_;
}

QPointF Ray::GetDirection(double angle) {
  return {std::cos(angle), std::sin(angle)};
}

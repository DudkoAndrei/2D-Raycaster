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

const QPointF& Ray::Begin() const {
  return begin_;
}

const QPointF& Ray::Direction() const {
  return direction_;
}

QPointF Ray::End() const {
  return begin_ + direction_;
}

double Ray::Angle() const {
  return angle_;
}

void Ray::SetBegin(const QPointF& point) {
  begin_ = point;
}

void Ray::SetDirection(const QPointF& point) {
  direction_ = point;
  angle_ = GetAngle(point);
}

void Ray::SetEnd(const QPointF& point) {
  direction_ = point - begin_;
  angle_ = GetAngle(direction_);
}

void Ray::SetAngle(double angle) {
  angle_ = angle;
  double length = std::sqrt(
      direction_.x() * direction_.x() + direction_.y() * direction_.y());
  direction_ = QPointF(std::cos(angle_), std::sin(angle_)) * length;
}

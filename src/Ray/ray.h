#pragma once

#include <QPointF>

class Ray {
 public:
  Ray() = default;
  Ray(const QPointF& begin, const QPointF& end);
  Ray(const QPointF& begin, double angle);

 private:
  static double GetAngle(const QPointF& point);

  QPointF begin_{0, 0};
  QPointF direction_{0, 0};
  double angle_{0};
};

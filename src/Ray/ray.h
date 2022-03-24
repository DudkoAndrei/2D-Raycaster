#pragma once

#include <compare>
#include <QPointF>

class Ray {
 public:
  Ray() = default;
  Ray(const QPointF& begin, const QPointF& end);
  Ray(const QPointF& begin, double angle);

  const QPointF& Begin() const;
  const QPointF& Direction() const;
  double Angle() const;

  void SetBegin(const QPointF& point);
  void SetDirection(const QPointF& point);
  void SetAngle(double angle);

  Ray Rotate(double angle) const;

  auto operator<=>(const Ray& rhs) const;

 private:
  static double GetAngle(const QPointF& point);
  static QPointF GetDirection(double angle);

  QPointF begin_{0, 0};
  QPointF direction_{0, 0};
  double angle_{0};
};

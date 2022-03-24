#pragma once

#include <vector>

#include "../Polygon/polygon.h"
#include "../Ray/ray.h"

class Controller {
 public:
  Controller() = default;

  const std::vector<Polygon>& Polygons() const;

  const QPointF& LightSource() const;
  void SetLightSource(const QPointF& light_source);

  void AddPolygon(Polygon polygon);
  void AddVertexToLastPolygon(const QPointF& vertex);
  void UpdateLastPolygon(const QPointF& vertex);

  Polygon CreateLightArea() const;

 private:
  std::vector<Ray> CastRays() const;
  std::vector<QPointF> IntersectRays(const std::vector<Ray>& rays) const;
  static void RemoveAdjacentPoints(std::vector<QPointF>* points);

  static double GetLineLength(const QPointF& a, const QPointF& b);

  std::vector<Polygon> polygons_;
  QPointF light_source_;
};

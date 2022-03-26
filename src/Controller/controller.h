#pragma once

#include <vector>

#include "../Polygon/polygon.h"
#include "../Ray/ray.h"

class Controller {
 public:
  Controller() = default;

  const std::vector<Polygon>& Polygons() const;

  const QPointF& LightSource() const;
  void SetLightSource(
      const QPointF& light_source,
      size_t count = 10,
      double light_radius = 1.0);

  void AddStaticLightSource(const QPointF& light_source);

  void AddPolygon(Polygon polygon);
  void AddVertexToLastPolygon(const QPointF& vertex);
  void UpdateLastPolygon(const QPointF& vertex);

  std::vector<Polygon> CreateLightAreas() const;

 private:
  std::vector<std::vector<Ray>> CastRays() const;
  std::vector<std::vector<QPointF>> IntersectRays(
      const std::vector<std::vector<Ray>>& rays) const;
  static void RemoveAdjacentPoints(std::vector<std::vector<QPointF>>* points);

  static double GetLineLength(const QPointF& a, const QPointF& b);

  std::vector<Polygon> polygons_;
  std::vector<QPointF> light_sources_;
  std::vector<QPointF> static_light_sources_;
};

#pragma once

#include <optional>
#include <vector>

#include "../Polygon/polygon.h"
#include "../Ray/ray.h"

class Controller {
 public:
  Controller() = default;

  const std::vector<Polygon>& Polygons() const;
  bool HasPolygons() const;

  const QPointF& LightSource() const;
  void SetLightSource(const QPointF& light_source);
  bool HasLightSource() const;

  void AddStaticLightSource(const QPointF& light_source);

  void AddPolygon(Polygon polygon);
  void AddVertexToLastPolygon(const QPointF& vertex);
  void UpdateLastPolygon(const QPointF& vertex);

  void UpdateLightAreas();

  const std::vector<Polygon>& LightAreas() const;

  size_t FuzzyPointsCount() const;
  void SetFuzzyPointsCount(size_t count);

  double LightSourceRadius() const;
  void SetLightSourceRadius(double radius);

  void SetBounds(double width, double height);

  const std::vector<QPointF> StaticLightSources() const;

 private:
  std::vector<std::vector<Ray>> CastRays() const;
  std::vector<std::vector<QPointF>> IntersectRays(
      const std::vector<std::vector<Ray>>& rays) const;
  static void RemoveAdjacentPoints(std::vector<std::vector<QPointF>>* points);

  void AddFuzzyLightSource(
      const QPointF& source);

  static double GetLineLength(const QPointF& a, const QPointF& b);

  std::optional<QPointF> light_source_;

  std::vector<Polygon> polygons_;
  std::vector<QPointF> fuzzy_light_sources_;
  std::vector<QPointF> static_light_sources_;

  std::vector<Polygon> light_areas_;

  size_t fuzzy_points_count_{10};
  double light_source_radius_{1};
};

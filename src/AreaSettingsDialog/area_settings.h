#pragma once

#include <QColor>

struct AreaSettings {
  QColor background_color{QColorConstants::Black};
  QColor polygons_color{QColorConstants::DarkBlue};
  QColor light_color{QColorConstants::White};
  QColor static_light_color{QColorConstants::DarkGray};

  int fuzzy_points_count{10};
  double light_source_radius{1};
};

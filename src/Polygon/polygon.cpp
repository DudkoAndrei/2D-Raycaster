#include "polygon.h"

Polygon::Polygon(std::vector<QPointF> vertices)
    : vertices_(std::move(vertices)) {}

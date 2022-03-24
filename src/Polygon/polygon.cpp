#include "polygon.h"

#include <utility>

Polygon::Polygon(std::vector<QPointF> vertices)
    : vertices_(std::move(vertices)) {}

const QPointF& Polygon::operator[](size_t idx) const {
  Q_ASSERT(0 <= idx && idx <= vertices_.size());

  if (idx == vertices_.size()) {
    return vertices_[0];
  }

  return vertices_[idx];
}

size_t Polygon::Size() const {
  return vertices_.size();
}

void Polygon::AddVertex(const QPointF& vertex) {
  vertices_.push_back(vertex);
}

void Polygon::UpdateLastVertex(const QPointF& vertex) {
  vertices_.back() = vertex;
}

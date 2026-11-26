#include "rubber.hpp"
#include <stdexcept>

Rubber::Rubber(double r1, double r2, point_t center, double dx, double dy):
  minR_((r1 > r2) ? r2 : r1),
  maxR_((r1 > r2) ? r1 : r2),
  center_(center),
  dx_(dx),
  dy_(dy)
{}

double Rubber::getArea() const
{
  const double pi = 3.1415;
  const double bigCircle = pi * maxR_ * maxR_;
  const double smallCircle = pi * minR_ * minR_;
  return bigCircle - smallCircle;
}

rectangle_t Rubber::getFrameRect() const
{
  const double diameterFactor = 2.0;
  point_t frameCenter = {center_.x + dx_, center_.y + dy_};
  return {diameterFactor * maxR_, diameterFactor * maxR_, frameCenter};
}

void Rubber::move(const point_t& newCenter)
{
  center_ = newCenter;
}

void Rubber::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rubber::scale(double factor)
{
  if (factor <= 0) {
    throw std::invalid_argument("ERROR: Incorrect factor!");
  }
  minR_ *= factor;
  maxR_ *= factor;
}

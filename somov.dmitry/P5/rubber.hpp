#ifndef RUBBER_HPP
#define RUBBER_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Rubber: public Shape {
public:
  Rubber(double r1, double r2, point_t center, double dx, double dy);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& newCenter) override;
  void move(double dx, double dy) override;
  void scale(double factor) override;

private:
  double minR_;
  double maxR_;
  point_t center_;
  double dx_;
  double dy_;
};

#endif

#ifndef SOMOV_HPP
#define SOMOV_HPP

#include "base-types.hpp"

class Shape;

namespace somov
{
  const int correctExit = 0;
  const int incorrectParam = 1;
  const int internalError = 2;

  const int width_r = 10.0;
  const int height_r = 20.0;
  const point_t center_r = {0.0, 0.0};

  const point_t a_t = {1.0, 0.0};
  const point_t b_t = {2.0, 0.0};
  const point_t c_t = {0.0, 4.0};

  const int r1 = 10.0;
  const int r2 = 5.0;
  const point_t center_rub = {3.0, 3.0};
  const int dx = 2.0;
  const int dy = 2.0;

  double findMin(double x1, double x2, double x3);
  double findMax(double x1, double x2, double x3);
  void printRectangle(const rectangle_t& rect);
  void scaleByDot(Shape& shape, const point_t& dot, double factor);
  rectangle_t getBigFrameRect(const Shape* s1, const Shape* s2, const Shape* s3);
}

#endif

#include "somov.hpp"
#include "shape.hpp"
#include <iostream>
#include <stdexcept>

double somov::findMin(double x1, double x2, double x3)
{
  double result = x1;
  if (x2 < result) {
    result = x2;
  }
  if (x3 < result) {
    result = x3;
  }
  return result;
}

double somov::findMax(double x1, double x2, double x3)
{
  double result = x1;
  if (x2 > result) {
    result = x2;
  }
  if (x3 > result) {
    result = x3;
  }
  return result;
}

void somov::printRectangle(const rectangle_t& rect)
{
  std::cout << rect.width << " ";
  std::cout << rect.height << " ";
  std::cout << rect.pos.x << " ";
  std::cout << rect.pos.y << "\n";
}

void somov::scaleByDot(Shape& shape, const point_t& dot, double factor)
{
  if (factor <= 0) {
    throw std::invalid_argument("ERROR: Incorrect factor!");
  }
  const point_t oldPos = shape.getFrameRect().pos;
  shape.move(dot);
  shape.scale(factor);

  const double dx = factor * (oldPos.x - dot.x);
  const double dy = factor * (oldPos.y - dot.y);
  shape.move(dx, dy);
}

rectangle_t somov::getBigFrameRect(const Shape* s1, const Shape* s2, const Shape* s3)
{
  const double half = 0.5;
  const rectangle_t f1 = s1->getFrameRect();
  const rectangle_t f2 = s2->getFrameRect();
  const rectangle_t f3 = s3->getFrameRect();

  const double minX = findMin(f1.pos.x - (f1.width * half),
      f2.pos.x - (f2.width * half),
      f3.pos.x - (f3.width * half));
  const double maxX = findMax(f1.pos.x + (f1.width * half),
      f2.pos.x + (f2.width * half),
      f3.pos.x + (f3.width * half));
  const double minY = findMin(f1.pos.y - (f1.height * half),
      f2.pos.y - (f2.height * half),
      f3.pos.y - (f3.height * half));
  const double maxY = findMax(f1.pos.y + (f1.height * half),
      f2.pos.y + (f2.height * half),
      f3.pos.y + (f3.height * half));

  const double width = maxX - minX;
  const double height = maxY - minY;
  return {width, height, {minX + (width * half), minY + (height * half)}};
}

#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "rectangle.hpp"
#include "rubber.hpp"
#include "somov.hpp"
#include "triangle.hpp"

static const std::size_t shapeCount = 3;

void printShapesInfo(const Shape* const* shapes)
{
  double fullArea = 0.0;
  for (std::size_t i = 0; i < shapeCount; ++i) {
    std::cout << "Shape " << (i + 1) << " area: " << shapes[i]->getArea() << "\n";
    std::cout << "Frame rectangle: ";
    somov::printRectangle(shapes[i]->getFrameRect());
    fullArea += shapes[i]->getArea();
  }
  std::cout << "Full area: " << fullArea << "\n";

  const rectangle_t bigFrame = somov::getBigFrameRect(shapes[0], shapes[1], shapes[2]);
  std::cout << "Big frame Rectangle: ";
  somov::printRectangle(bigFrame);
}

int main()
{
  point_t scaleDot{0.0, 0.0};
  double factor = 0.0;
  std::cin >> scaleDot.x >> scaleDot.y >> factor;
  if (!std::cin) {
    std::cerr << "ERROR: Incorrect input!\n";
    return somov::incorrectParam;
  }

  Shape* shapes[shapeCount] = {nullptr, nullptr, nullptr};

  try {
    shapes[0] = new Rectangle(10.0, 20.0, {1.0, 1.0});
    shapes[1] = new Triangle({1.0, 0.0}, {2.0, 0.0}, {0.0, 4.0});
    shapes[2] = new Rubber(10.0, 5.0, {0.0, 0.0}, 1.0, 1.0);

    printShapesInfo(shapes);
    for (std::size_t i = 0; i < shapeCount; ++i) {
      somov::scaleByDot(*shapes[i], scaleDot, factor);
    }
    std::cout << "\n";

    printShapesInfo(shapes);
    std::cout << "\n";
  
    for (std::size_t i = 0; i < shapeCount; i++) {
        delete shapes[i];
    }
  } 
  catch (const std::invalid_argument& e) {
    std::cerr << e.what() << "\n";
    for (std::size_t i = 0; i < shapeCount; i++) {
        delete shapes[i];
    }
    return somov::incorrectParam;
  }

  return somov::correctExit;
}

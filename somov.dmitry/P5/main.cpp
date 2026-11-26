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
  double full_area = 0.0;
  for (std::size_t i = 0; i < shapeCount; ++i){
    std::cout << "Shape " << (i + 1) << " area: " << shapes[i]->getArea() << "\n";
    std::cout << "Frame rectangle: ";
    somov::printRectangle(shapes[i]->getFrameRect());
    full_area += shapes[i]->getArea();
  }
  std::cout << "Full area: " << full_area << "\n";

  const rectangle_t bigFrame = somov::getBigFrameRect(shapes[0], shapes[1], shapes[2]);
  std::cout << "Big frame Rectangle: ";
  somov::printRectangle(bigFrame);
}

int main()
{
  point_t scale_dot{0.0, 0.0};
  double factor = 0.0;
  Shape* shapes[shapeCount] = {nullptr, nullptr, nullptr};
  Rectangle s1(10.0, 20.0, {0.0, 0.0});
  Triangle s2({1.0, 0.0}, {2.0, 0.0}, {0.0, 4.0});
  Rubber s3(10.0, 5.0, {0.0, 0.0}, 1.0, 1.0);

  std::cin >> scale_dot.x >> scale_dot.y >> factor;
  if (!std::cin){
    shapes[0] = new Rectangle(s1);
    shapes[1] = new Triangle(s2);
    shapes[2] = new Rubber(s3);

    printShapesInfo(shapes);
    std::cerr << "ERROR: Incorrect input!\n";
    return somov::incorrectParam;
  }

  try{
    shapes[0] = new Rectangle(s1);
    shapes[1] = new Triangle(s2);
    shapes[2] = new Rubber(s3);

    printShapesInfo(shapes);
    for (std::size_t i = 0; i < shapeCount; ++i){
      somov::scaleByDot(*shapes[i], scale_dot, factor);
    }
    std::cout << "\n";

    printShapesInfo(shapes);
    std::cout << "\n";

    for (std::size_t i = 0; i < shapeCount; i++){
      delete shapes[i];
    }
  }catch (const std::invalid_argument& e){
    std::cerr << e.what() << "\n";
    for (std::size_t i = 0; i < shapeCount; i++){
      delete shapes[i];
    }
    return somov::incorrectParam;
  }catch (const std::bad_alloc&){
    std::cerr << "ERROR: Bad alloc!";
    for (std::size_t i = 0; i < shapeCount; i++){
      delete shapes[i];
    }
    return somov::internalError;
  }

  return somov::correctExit;
}

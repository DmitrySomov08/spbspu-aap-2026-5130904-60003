#include <cstddef>
#include <iostream>

int main()
{
  std::size_t count = 0;
  std::size_t frag = 0;
  std::size_t max_frag = 0;
  std::size_t min = 0;
  int pred = 0;
  int pred_pred = 0;
  int value = 0;

  while ((std::cin >> value) && (value != 0)) {
    if ((count > 0) && (value <= pred)) {
      ++frag;
    } else {
      frag = 1;
    }
    if (frag > max_frag) {
      max_frag = frag;
    }
    if ((count > 1) && (pred < pred_pred) && (pred < value)) {
      ++min;
    }
    pred_pred = pred;
    pred = value;
    ++count;
  }

  if (!std::cin) {
    std::cerr << "Invalid input\n";
    return 1;
  }

  std::cout << max_frag << '\n';
  if (count == 0) {
    std::cerr << "Invalid arguments\n";
    return 2;
  }
  std::cout << min << '\n';
  return 0;
}

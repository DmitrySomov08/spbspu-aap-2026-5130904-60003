#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>

namespace somov {
  const std::size_t MAXSIZE = 10000;
  const int correct_exit = 0;
  const int incorrect_string = 1;
  const char * const suffix = "def_";
  const std::size_t suffix_len = std::strlen(suffix);

  char * convertToLowerCase(const char * str, char * lower_str, std::size_t len)
  {
    for (std::size_t i = 0; i < len; ++i) {
      lower_str[i] = static_cast< char >(std::tolower(static_cast< unsigned char >(str[i])));
    }
    lower_str[len] = '\0';
    return lower_str;
  }

  char * combineStrings(const char * str1, const char * str2, char * comb_str,
      std::size_t len1, std::size_t len2)
  {
    std::size_t i = 0;
    std::size_t j = 0;
    std::size_t k = 0;
    while (len1 > i || len2 > j) {
      if (len1 > i) {
        comb_str[k++] = str1[i++];
      }
      if (len2 > j) {
        comb_str[k++] = str2[j++];
      }
    }
    comb_str[k] = '\0';
    return comb_str;
  }
}

int main()
{
  char * str = new char[somov::MAXSIZE];
  std::size_t len = 0;
  char c = 0;

  while (std::cin.get(c) && c != '\n') {
    if (len + 1 >= somov::MAXSIZE) {
      std::cerr << "Sorry, your string is out of range!\n";
      delete[] str;
      return somov::incorrect_string;
    }
    str[len++] = c;
  }
  str[len] = '\0';

  char * lower_str = new char[somov::MAXSIZE];
  char * comb_str = new char[somov::MAXSIZE + somov::suffix_len];

  somov::convertToLowerCase(str, lower_str, len);
  std::cout << "String in lower case: " << lower_str << '\n';

  somov::combineStrings(str, somov::suffix, comb_str, len, somov::suffix_len);
  std::cout << "Combination of string1 and string2: " << comb_str << '\n';

  std::cout << str << '\n';

  delete[] str;
  delete[] lower_str;
  delete[] comb_str;
  return somov::correct_exit;
}
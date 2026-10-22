#include <iostream>
#include <fstream>
#include <string>

namespace somov {
  const char stack = '1';
  const char heap = '2';
  const int error_input_file = 2;
  const int error_input = 1;
  const int correct_out = 0;

  bool readMatrix(std::istream &input, int* matrix, size_t size);
  int maxSideDiag(const int* matrix, const int rows, const int cols);
}

bool somov::readMatrix(std::istream &input, int* matrix, size_t size) {
    for (size_t i = 0; i < size; i++) {          
        if (!(input >> matrix[i])) {
            return false;
        }
    }
    return true;
}

int somov::maxSideDiag(const int* matrix, const int rows, const int cols) {
    if (rows == 0 || cols == 0) {                
        return somov::correct_out;
    }

    int total_max = matrix[0];
    int total_current;

    for (int c = 0; c < rows + cols - 1; ++c) {
        if (c == cols - 1) {
            continue;
        }
        total_current = 0;
        for (int i = 0; i < rows; ++i) {
            int j = c - i;
            if (0 <= j && j < cols) {            
                total_current += matrix[i*cols + j];
            }
        }
        if (total_current > total_max) {
            total_max = total_current;
        }
    }

    return total_max;
}

const size_t MAXSIZE = 1000;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Not enough arguments";
        return somov::error_input;
    }

    if (argc > 4) {
        std::cerr << "Too many arguments";
        return somov::error_input;
    }

    if (*argv[1] != somov::stack && *argv[1] != somov::heap) {
         std::cerr << "First parameter must be 1 or 2 " << *argv[1];
         return somov::error_input;
    }

    std::ifstream in(argv[2]);
    std::ofstream out(argv[3]);
    if (!in) {                                   
        std::cerr << "Cannot open input file: " << argv[2];
        return somov::error_input_file;
    }
    if (!out) {
        std::cerr << "Cannot open output file: " << argv[3];
        return somov::error_input_file;
    }

    size_t n = 0, m = 0, size;
    bool mat_read = false;
    int result = 0;

    if (!(in >> n >> m) || n < 0 || m < 0) {   
        std::cerr << "Can`t read matrix size";
        return somov::error_input_file;
    }
    size = n * m;

    if (*argv[1] == somov::stack) {
         if (size > MAXSIZE) {                   
             std::cerr << "Matrix is too big for stack";
             return somov::error_input;
         }
         int matrix[MAXSIZE] = {};
         mat_read = somov::readMatrix(in, matrix, size);   
         if (mat_read) {
            result = somov::maxSideDiag(matrix, n, m);
         }
    }

    if (*argv[1] == somov::heap) {
        int* matrix = new int[size];
        mat_read = somov::readMatrix(in, matrix, size);
        if (mat_read) {
            result = somov::maxSideDiag(matrix, n, m);
        }
        delete[] matrix;
    }

    if (!mat_read) {
        std::cerr << "Matrix can`t be readen";
        return somov::error_input_file;
    }

    out << result << "\n";
    in.close();
    out.close();

    return somov::correct_out;
}
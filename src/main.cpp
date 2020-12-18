#include <iostream>
#include <matrix.hpp>

int main() {
    LinearAlgebra::Matrix<double> A(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A[i][j] = i + j;
        }
    }
    std::cout << "Let's start algebra project!" << std::endl;
    std::cout << A << std::endl;
}
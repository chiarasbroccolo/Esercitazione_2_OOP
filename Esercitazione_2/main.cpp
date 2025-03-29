#include <iostream>
#include "complex.hpp"

int main() {

    complex_number<double> c1(3.0, 4.0);

    complex_number<double> c2(1.0, -2.0);

    std::cout << "c1 = " << c1 << std::endl;

    std::cout << "c2 = " << c2 << std::endl;

    std::cout << "c1 + c2 = " << c1 + c2 << std::endl;

    std::cout << "c1 * c2 = " << c1 * c2 << std::endl;

    std::cout << "Il coniugato di c1 = " << c1.conjugate() << std::endl;

    std::cout << "c1 + 2 = " << c1 + 2.0 << std::endl;
	
	std::cout << "2 + c1 = " << 2.0 + c1 << std::endl;
	
	std::cout << "c1 * 2 = " << c1 * 2.0 << std::endl;

    std::cout << "2 * c1 = " << 2.0 * c1 << std::endl;
}


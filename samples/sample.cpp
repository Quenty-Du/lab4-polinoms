#include "../include/Polynomial.h"

#include <iostream>
#include <string>

int main() {
    Polynomial A, B;
    double k;
    
    std::cout << "=== Polynomial Calculator ===\n\n";
    std::cout << "Format: 3x^2y + 2z - 5\n";
    
    std::cout << "\nEnter first polynomial A: ";
    A = Polynomial::input("A");
    
    std::cout << "\nEnter second polynomial B: ";
    B = Polynomial::input("B");
    
    std::cout << "\nEnter constant: ";
    std::cin >> k;
    
    std::cout << "\n========== RESULTS ==========\n";
    
    std::cout << "A = "; A.print();
    std::cout << "B = "; B.print();
    
    std::cout << "\nA + B = "; Polynomial::add(A, B).print();
    std::cout << "A - B = "; Polynomial::subtract(A, B).print();
    std::cout << "A * B = "; 
    try {
        Polynomial::multiply(A, B).print();
    } catch (...) {
        std::cout << "Error: degree > 9\n";
    }
    
    std::cout << "\nA * " << k << " = "; Polynomial::multiplyByConst(A, k).print();
    std::cout << "B * " << k << " = "; Polynomial::multiplyByConst(B, k).print();
    
    return 0;
}
#include "../include/Polynomial.h"

#include <iostream>
#include<string>
#include <stdexcept>



void Polynomial::insertSorted(const Monom& m) {
    if (m.getCoeff() == 0.0) return;
    
    auto it = monoms.begin();
    while (it != monoms.end() && it->getKey() < m.getKey()) {
        ++it;
    }
    
    if (it != monoms.end() && it->getKey() == m.getKey()) {
        double newCoeff = it->getCoeff() + m.getCoeff();
        if (newCoeff == 0.0) {
            monoms.erase(it);
        } else {
            *it = Monom(newCoeff, it->getKey());
        }
    } else {
        monoms.insert(it, m);
    }
}



Polynomial::Polynomial() {}

void Polynomial::addMonom(const Monom& m) {
    insertSorted(m);
}



Polynomial Polynomial::add(const Polynomial& a, const Polynomial& b) {
    Polynomial result;
    auto itA = a.monoms.begin();
    auto itB = b.monoms.begin();
    
    while (itA != a.monoms.end() && itB != b.monoms.end()) {
        if (itA->getKey() < itB->getKey()) {
            result.addMonom(*itA);
            ++itA;
        } else if (itA->getKey() > itB->getKey()) {
            result.addMonom(*itB);
            ++itB;
        } else {
            double sumCoeff = itA->getCoeff() + itB->getCoeff();
            if (sumCoeff != 0.0) {
                result.addMonom(Monom(sumCoeff, itA->getKey()));
            }
            ++itA;
            ++itB;
        }
    }
    
    while (itA != a.monoms.end()) {
        result.addMonom(*itA);
        ++itA;
    }
    while (itB != b.monoms.end()) {
        result.addMonom(*itB);
        ++itB;
    }
    
    return result;
}

Polynomial Polynomial::subtract(const Polynomial& a, const Polynomial& b) {
    Polynomial negB = multiplyByConst(b, -1.0);
    return add(a, negB);
}

Polynomial Polynomial::multiplyByConst(const Polynomial& p, double c) {
    Polynomial result;
    if (c == 0.0) return result;
    
    for (auto it = p.monoms.begin(); it != p.monoms.end(); ++it) {
        double newCoeff = it->getCoeff() * c;
        if (newCoeff != 0.0) {
            result.addMonom(Monom(newCoeff, it->getKey()));
        }
    }
    return result;
}

Polynomial Polynomial::multiply(const Polynomial& a, const Polynomial& b) {
    Polynomial result;
    
    for (auto itA = a.monoms.begin(); itA != a.monoms.end(); ++itA) {
        for (auto itB = b.monoms.begin(); itB != b.monoms.end(); ++itB) {
            int newKey = itA->getKey() + itB->getKey();
            
            int degX = newKey / 100;
            int degY = (newKey / 10) % 10;
            int degZ = newKey % 10;
            if (degX > 9 || degY > 9 || degZ > 9) {
                throw std::overflow_error("Degree exceeds 9 in polynomial multiplication");
            }
            
            double newCoeff = itA->getCoeff() * itB->getCoeff();
            if (newCoeff != 0.0) {
                result.addMonom(Monom(newCoeff, newKey));
            }
        }
    }
    
    return result;
}



bool Polynomial::checkDegreeLimit() const {
    for (auto it = monoms.begin(); it != monoms.end(); ++it) {
        if (it->getDegX() > 9 || it->getDegY() > 9 || it->getDegZ() > 9) {
            return false;
        }
    }
    return true;
}

void Polynomial::print() const {
    if (monoms.empty()) {
        std::cout << "0";
        return;
    }
    
    bool first = true;
    for (auto it = monoms.begin(); it != monoms.end(); ++it) {
        double coeff = it->getCoeff();
        
        if (first) {
            if (coeff < 0) std::cout << "-";
            first = false;
        } else {
            std::cout << (coeff > 0 ? " + " : " - ");
        }
        
        double absCoeff = (coeff < 0) ? -coeff : coeff;
        if (absCoeff != 1.0 || (it->getDegX() == 0 && it->getDegY() == 0 && it->getDegZ() == 0)) {
            std::cout << absCoeff;
        }
        
        if (it->getDegX() > 0) std::cout << "x" << (it->getDegX() > 1 ? "^" + std::to_string(it->getDegX()) : "");
        if (it->getDegY() > 0) std::cout << "y" << (it->getDegY() > 1 ? "^" + std::to_string(it->getDegY()) : "");
        if (it->getDegZ() > 0) std::cout << "z" << (it->getDegZ() > 1 ? "^" + std::to_string(it->getDegZ()) : "");
    }
    std::cout << std::endl;
}
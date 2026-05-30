#include "../include/Monom.h"

#include <string>
#include <cctype>
#include <stdexcept>



Monom::Monom(double coeff, int deg_x, int deg_y, int deg_z) : coeff(coeff), key(deg_x * 100 + deg_y * 10 + deg_z) {}

Monom::Monom(double coeff, int key) : coeff(coeff), key(key) {}



Monom Monom::parse(const std::string& token) {
    if (token.empty()) {
        throw std::invalid_argument("Empty token");
    }
    
    double coeff = 1.0;
    int deg_x = 0, deg_y = 0, deg_z = 0;
    size_t i = 0;
    bool hasDigit = false;
    
    if (token[0] == '-') {
        coeff = -1.0;
        i = 1;
    }
    
    if (i < token.size() && isdigit(token[i])) {
        coeff = 0;
        while (i < token.size() && (isdigit(token[i]) || token[i] == '.')) {
            coeff = coeff * 10 + (token[i] - '0');
            i++;
            hasDigit = true;
        }
        if (token[0] == '-') coeff = -coeff;
    }
    
    bool hasVariable = false;
    while (i < token.size()) {
        char var = token[i];
        if (var != 'x' && var != 'y' && var != 'z') {
            throw std::invalid_argument("Invalid character in monom: " + std::string(1, var));
        }
        i++;
        int deg = 1;
        if (i < token.size() && token[i] == '^') {
            i++;
            if (i >= token.size() || !isdigit(token[i])) {
                throw std::invalid_argument("Expected digit after ^");
            }
            deg = token[i] - '0';
            i++;
        }
        if (var == 'x') deg_x = deg;
        else if (var == 'y') deg_y = deg;
        else if (var == 'z') deg_z = deg;
        hasVariable = true;
    }
    
    if (!hasDigit && !hasVariable) {
        throw std::invalid_argument("Invalid monom format: " + token);
    }
    
    return Monom(coeff, deg_x, deg_y, deg_z);
}



double Monom::getCoeff() const {
    return coeff;
}

int Monom::getKey() const {
    return key;
}

int Monom::getDegX() const {
    return key / 100;
}

int Monom::getDegY() const {
    return (key / 10) % 10;
}

int Monom::getDegZ() const {
    return key % 10;
}



void Monom::multiplyByConst(double c) {
    coeff *= c;
}

void Monom::addToCoeff(double c) {
    coeff += c;
}



bool Monom::operator==(const Monom& other) const {
    return key == other.key;
}

bool Monom::operator<(const Monom& other) const {
    return key < other.key;
}
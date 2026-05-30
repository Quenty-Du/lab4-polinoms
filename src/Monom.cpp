#include "../include/Monom.h"



Monom::Monom(double coeff, int deg_x, int deg_y, int deg_z) : coeff(coeff), key(deg_x * 100 + deg_y * 10 + deg_z) {}

Monom::Monom(double coeff, int key) : coeff(coeff), key(key) {}



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
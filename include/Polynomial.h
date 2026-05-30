#pragma once

#include "Monom.h"
#include "List.h"




class Polynomial {
private:
    List<Monom> monoms;

    void insertSorted(const Monom& m);

public:
    Polynomial();
    void addMonom(const Monom& m);

    static Polynomial add(const Polynomial& a, const Polynomial& b);
    static Polynomial subtract(const Polynomial& a, const Polynomial& b);
    static Polynomial multiplyByConst(const Polynomial& p, double c);
    static Polynomial multiply(const Polynomial& a, const Polynomial& b);

    bool checkDegreeLimit() const;
    void print() const;
};
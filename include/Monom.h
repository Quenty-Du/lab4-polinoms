#pragma once



class Monom {
private:
    double coeff;
    int key;

public:
    Monom(double coeff, int deg_x, int deg_y, int deg_z);
    Monom(double coeff, int key);

    static Monom parse(const std::string& token);

    double getCoeff() const;
    int getKey() const;
    int getDegX() const;
    int getDegY() const;
    int getDegZ() const;

    void multiplyByConst(double c);
    void addToCoeff(double c);

    bool operator==(const Monom& other) const;
    bool operator<(const Monom& other) const;
};
#ifndef UNTITLED1_LIBRARY_H
#define UNTITLED1_LIBRARY_H

class Number {
private:
    double number_;
public:
    Number() : number_(0) {};

    explicit Number(const double value) : number_(value) {};

    ~Number() = default;

    double getNumber() const;

    Number add(const Number other) const;

    Number subtract(const Number other) const;

    Number divide(const Number other) const;

    Number multiply(const Number other) const;

    void setValue(const Number other);
};

Number createNumber(const double value);

namespace constants {
    const Number null = Number(0);
    const Number one = Number(1);
}

#endif //UNTITLED1_LIBRARY_H

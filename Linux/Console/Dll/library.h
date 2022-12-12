#ifndef UNTITLED2_LIBRARY_H
#define UNTITLED2_LIBRARY_H

#pragma once

#include "library.h"
#include "/home/stanislave/CLionProjects/NumLib/library.h"

class Vector {
private:
    Number x_;
    Number y_;
public:

    Vector() : x_(constants::null), y_(constants::null) {};

    Vector(Number valueX, Number valueY) : x_(valueX), y_(valueY) {};

    ~Vector() = default;

    double getPolarRadius() const;

    double getPolarAngle() const;

    Vector add(Vector other) const;

    void setValue(Vector other);
};

namespace Constants {
    extern const Vector nullVector;
    extern const Vector defVector;
}

#endif //UNTITLED2_LIBRARY_H

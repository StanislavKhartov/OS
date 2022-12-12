#include "library.h"

#include <cmath>

double Vector::getPolarRadius() const {
    return sqrt(pow(x_.getNumber(), 2) + pow(y_.getNumber(), 2));
}

double Vector::getPolarAngle() const {
    if (x_.getNumber() == 0) {
        if (y_.getNumber() < 0) {
            return M_PI / -2;
        }
        else {
            return M_PI / 2;
        }
    }
    return atan(y_.getNumber() / x_.getNumber());
}

Vector Vector::add(Vector other) const{
    return Vector(x_.add(other.x_), y_.add(other.y_));
}

void Vector::setValue(Vector other)
{
    x_ = other.x_;
    y_ = other.y_;
}

namespace vectorConstants {
    const Vector nullVector = Vector(constants::null, constants::null);
    const Vector defVector = Vector(constants::one, constants::one);
}

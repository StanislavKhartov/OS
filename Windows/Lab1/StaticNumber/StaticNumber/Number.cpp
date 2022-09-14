#include "pch.h"
#include "Number.h"

double Number::getNumber() const{
	return number_;
}

Number Number::add(const Number other) const {
	return Number(getNumber() + other.getNumber());
}

Number Number::subtract(const Number other) const {
	return Number(getNumber() - other.getNumber());
}

Number Number::divide(const Number other) const {
	if (other.number_ == 0) {
		return constants::null;
	}
	return Number(getNumber() / other.getNumber());
}

Number Number::multiply(const Number other) const{
	return Number(getNumber() * other.getNumber());
}

void Number::setValue(const Number other)
{
	number_ = other.number_;
}

Number createNumber(const double value) {
	return Number(value);
}
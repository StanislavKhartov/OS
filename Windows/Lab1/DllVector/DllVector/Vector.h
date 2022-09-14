#pragma once

#ifdef VECTOR_API
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif

#pragma comment(lib, "C:\\Users\\Ideapad\\source\\repos\\StaticNumber\\x64\\Debug\\Number")

#include "C:\\Users\\Ideapad\\source\\repos\\StaticNumber\\StaticNumber\\Number.h"

class __declspec(dllexport) Vector
{
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
	extern const Vector __declspec(dllexport) nullVector;
	extern const Vector __declspec(dllexport) defVector;
}


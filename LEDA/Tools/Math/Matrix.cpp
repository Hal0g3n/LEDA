/**
 * @file        Matrix.cpp
 * @author      your name (you@domain.com)
 * @brief       Implementations for the Matrix class methods
 * @version     0.1
 * @date        15-08-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */
#define _USE_MATH_DEFINES

#include "LEDA_Math.h"
#include <cmath>

namespace LEDA {
	// constructors
	Mtx33::Mtx33() : m({ 0, 0, 0, 0, 0, 0, 0, 0, 0 }) {}
	Mtx33::Mtx33(const float* arr) : m(arr) {}
	Mtx33::Mtx33(double _00, double _01, double _02, double _10, double _11, double _12, double _20, double _21, double _22) : m00(_00), m01(_01), m02(_02), m10(_10), m11(_11), m12(_12), m20(_20), m21(_21), m22(_22) {}

	// assignment operators
	Mtx33& Mtx33::operator*=(Mtx33 const& other) {
		*this = *this * other;
		return *this;
	}

	// member functions
	Mtx33 Mtx33::transpose() const {
		return Mtx33{ m00, m10, m20, m01, m11, m21, m02, m12, m22 };
	}

	Mtx33 Mtx33::inverse() const {
		//TODO
	}

	// static methods
	static Mtx33 Mtx33::identity() {
		return Mtx33{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	}

	static Mtx33 Mtx33::translate(double x, double y) {
		return Mtx33{ 1, 0, x, 0, 1, y, 0, 0, 1 }
	}

	static Mtx33 Mtx33::scale(double x, double y) {
		return Mtx33{ x, 0, 0, 0, y, 0, 0, 0, 1 };
	}

	static Mtx33 Mtx33::rotateRad(double angle) {
		return Mtx33{ cos(angle), sin(angle), 0, -sin(angle), cos(angle), 0, 0, 0, 1 };
	}

	static Mtx33 Mtx33::rotateDeg(double angle) {
		return rotateRad(angle * M_PI / 180);
	}

	//binary operators
	Mtx33 operator*(Mtx33 const& lhs, Mtx33 const& rhs) {
		//TODO
	}

	Vec2D operator*(Mtx33 const& lhs, Mtx33 const& rhs) {
		//TODO
	}
}
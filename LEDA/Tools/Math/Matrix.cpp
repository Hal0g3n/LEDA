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
		double determinant = m00 * m11 * m22
			+ m01 * m12 * m20
			+ m02 * m10 * m21
			- m20 * m11 * m02
			- m21 * m12 * m00
			- m22 * m10 * m01;
		if (determinant != 0)
			return Mtx33{ (m11 * m22 - m21 * m12) / determinant,
							(m02 * m21 - m01 * m22) / determinant,
							(m01 * m12 - m02 * m11) / determinant,
							(m12 * m20 - m10 * m22) / determinant,
							(m00 * m22 - m02 * m20) / determinant,
							(m10 * m02 - m00 * m12) / determinant,
							(m10 * m21 - m20 * m11) / determinant,
							(m20 * m01 - m00 * m21) / determinant,
							(m00 * m11 - m10 * m01) / determinant }

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
		return Mtx33{ lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20,
					lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21,
					lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22,
					lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20,
					lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21,
					lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22,
					lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20,
					lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21,
					lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 }; // standard matrix multiplication
	,

	Vec2D operator*(Mtx33 const& lhs, Mtx33 const& rhs) {
		double w = lhs.m20 * rhs.x + lhs.m21 * rhs.y + lhs.m22;
		return Vec2D{ (lhs.m00 * rhs.x + lhs.m01 * rhs.y + lhs.m02) / w, (lhs.m10 * rhs.x + lhs.m11 * rhs.y + lhs.m12) / w };
	}
}
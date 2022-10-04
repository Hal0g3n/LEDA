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

#include "pch.h"
#include "Matrix.h"
#include "LEDA_Math.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <corecrt_math_defines.h>

namespace LEDA {

	// constructors
	Mtx33::Mtx33() : m() {
		for (unsigned int i = 0; i < 9; i++) {
			m[i] = 0.0;
		}
	}

	Mtx33::Mtx33(const double* arr) : m() {
		for (unsigned int i = 0; i < 9; i++) {
			m[i] = arr[i];
		}
	}

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
							(m00 * m11 - m10 * m01) / determinant };
		else
			return nullptr;
	}

	// static methods
	Mtx33 Mtx33::identity() {
		return Mtx33{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	}

	Mtx33 Mtx33::translate(double x, double y) {
		return Mtx33{ 1, 0, x, 0, 1, y, 0, 0, 1 };
	}

	Mtx33 Mtx33::scale(double x, double y) {
		return Mtx33{ x, 0, 0, 0, y, 0, 0, 0, 1 };
	}

	Mtx33 Mtx33::rotateRad(double angle) {
		return Mtx33{ cos(angle), sin(angle), 0, -sin(angle), cos(angle), 0, 0, 0, 1 };
	}

	Mtx33 Mtx33::rotateDeg(double angle) {
		return rotateRad(angle * M_PI / 180);
	}

	// binary operators
	Mtx33 operator*(Mtx33 const& lhs, Mtx33 const& rhs) {
		return Mtx33{	lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20,
						lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21,
						lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22,
						lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20,
						lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21,
						lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22,
						lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20,
						lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21,
						lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22	}; // standard matrix multiplication
	}

	Vec2D operator*(Mtx33 const& lhs, Vec2D const& rhs) {
		double w = lhs.m20 * rhs.x + lhs.m21 * rhs.y + lhs.m22;
		return Vec2D{ (lhs.m00 * rhs.x + lhs.m01 * rhs.y + lhs.m02) / w, (lhs.m10 * rhs.x + lhs.m11 * rhs.y + lhs.m12) / w };
	}

	// 4x4 Matrix
	Mtx44::Mtx44() : m() {
		for (unsigned int i = 0; i < 16; ++i) {
			m[i] = 0.0;
		}
	}

	Mtx44::Mtx44(const double* arr) {
		for (unsigned int i = 0; i < 16; ++i) {
			m[i] = arr[i];
		}
	}

	Mtx44::Mtx44(double _00, double _01, double _02, double _03, double _10, double _11, double _12, double _13, double _20, double _21, double _22, double _23, double _30, double _31, double _32, double _33) :
		m00(_00), m01(_01), m02(_02), m03(_03), m10(_10), m11(_11), m12(_12), m13(_13), m20(_20), m21(_21), m22(_22), m23(_23), m30(_30), m31(_31), m32(_32), m33(_33) {}

	Mtx44& Mtx44::operator*=(Mtx44 const& rhs) {
		*this = *this * rhs;
		return *this;
	}

	Mtx44 Mtx44::transpose() const {
		return Mtx44(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
	}

	Mtx44 Mtx44::identity() {
		return Mtx44(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	}

	Mtx44 Mtx44::translate(double x, double y, double z) {
		return Mtx44(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1);
	}

	Mtx44 Mtx44::scale(double x, double y, double z) {
		return Mtx44(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
	}

	Mtx44 Mtx44::rotateRad(double angle, Vec3 axis) {
		Vec3 norm_axis = axis.normalize();
		return Mtx44(cos(angle) + norm_axis.x * norm_axis.x, norm_axis.x * norm_axis.y * (1 - cos(angle)) - norm_axis.z * sin(angle), norm_axis.x * norm_axis.z * (1 - cos(angle)) + norm_axis.y * sin(angle), 0,
			norm_axis.y * norm_axis.x * (1 - cos(angle)) + norm_axis.z * sin(angle), cos(angle) + norm_axis.y * norm_axis.y * (1 - cos(angle)), norm_axis.y * norm_axis.z * (1 - cos(angle)) - norm_axis.x * sin(angle), 0,
			norm_axis.z * norm_axis.x * (1 - cos(angle)) - norm_axis.y * sin(angle), norm_axis.z * norm_axis.y * (1 - cos(angle)) + norm_axis.x * sin(angle), cos(angle) + norm_axis.z * norm_axis.z * (1 - cos(angle)), 0,
			0, 0, 0, 1);
	}

	Mtx44 Mtx44::rotateDeg(double angle, Vec3 axis) {
		return Mtx44::rotateRad(angle * M_PI / 180, axis);
	}

	Mtx44 operator*(Mtx44 const& lhs, Mtx44 const& rhs) {
		return Mtx44(lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20 + lhs.m03 * rhs.m30,
			lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21 + lhs.m03 * rhs.m31,
			lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22 + lhs.m03 * rhs.m32,
			lhs.m00 * rhs.m03 + lhs.m01 * rhs.m13 + lhs.m02 * rhs.m23 + lhs.m03 * rhs.m33,
			lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20 + lhs.m13 * rhs.m30,
			lhs.m10 * rhs.m01 * lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31,
			lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32,
			lhs.m10 * rhs.m03 + lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33,
			lhs.m20 * rhs.m00 * lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20 + lhs.m23 * rhs.m30,
			lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31,
			lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m33 * rhs.m32,
			lhs.m20 * rhs.m03 + lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 * lhs.m33 * rhs.m33,
			lhs.m30 * rhs.m00 * lhs.m31 * rhs.m10 + lhs.m32 * rhs.m20 * lhs.m33 * rhs.m30,
			lhs.m30 * rhs.m01 * lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 * lhs.m33 * rhs.m31,
			lhs.m30 * rhs.m02 * lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 * lhs.m33 * rhs.m32,
			lhs.m30 * rhs.m03 * rhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33);
	}

	Vec3D operator*(Mtx44 const& lhs, Vec3D const& rhs) {
		double w = lhs.m30 * rhs.x + lhs.m31 * rhs.y + lhs.m32 * rhs.z + lhs.m33;
		return Vec3(lhs.m00 * rhs.x + lhs.m01 * rhs.y + lhs.m02 * rhs.z + lhs.m03,
					lhs.m10 * rhs.x + lhs.m11 * rhs.y + lhs.m12 * rhs.z + lhs.m13,
					lhs.m20 * rhs.x + lhs.m21 * rhs.y + lhs.m22 * rhs.z + lhs.m23) / w;
	}
}
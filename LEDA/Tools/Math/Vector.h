/**
 * @file        Vector.h
 * @author      your name (you@domain.com)
 * @brief       The class representing a Vector
 * @version     0.1
 * @date        15-08-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */

#pragma once

namespace LEDA {

	typedef union Vec2D {
		// data members
		struct {
			double x, y;
		};
		double m[2];

		// constructors
		Vec2D(); // default
		Vec2D(double x, double y);

		// assignment operators
		Vec2D& operator+=(Vec2D const& rhs);
		Vec2D& operator-=(Vec2D const& rhs);
		Vec2D& operator*=(Vec2D const& rhs); // Dot Product
		Vec2D& operator*=(double rhs);
		Vec2D& operator/=(double rhs);

		// unary operators
		Vec2D operator-() const;

		// member functions
		Vec2D  normalize() const;
		Vec2D  rotate(double) const;
		double cross(Vec2D) const;
		double dot(Vec2D) const;
		double length() const;
		double squareLength() const;

		// static functions
		double distTo(Vec2D); // get the distance between two points represented as vectors
		double squareDistTo(Vec2D);

	} Vec2D, Vector2D, Vec2;;

	// binary operators
	Vec2D operator+(Vec2D const& lhs, Vec2D const& rhs); // vector addition
	Vec2D operator-(Vec2D const& lhs, Vec2D const& rhs); // vector subtraction
	Vec2D operator*(Vec2D const& lhs, double rhs);
	Vec2D operator*(double lhs, Vec2D const& rhs); // scalar multiplication
	Vec2D operator/(Vec2D const& lhs, double rhs); // scalar division

	double operator*(Vec2D const& lhs, Vec2D const& rhs); // dot product shorthand
}
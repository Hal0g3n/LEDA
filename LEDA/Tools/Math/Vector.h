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

#ifndef LEDA_VECTOR_H_
#define LEDA_VECTOR_H_

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
		Vec2D& operator+=(Vec2D const&);
		Vec2D& operator-=(Vec2D const&);
		// Vec2D& operator*=(Vec2D const&); // Dot Product
		Vec2D& operator*=(double);
		Vec2D& operator/=(double);

		// unary operators
		Vec2D operator-() const;

		// member functions
		Vec2D  normalize() const;
		Vec2D  rotateDeg(double) const;
		Vec2D  rotateRad(double) const;
		Vec2D  rotateOutward() const;
		double dot(Vec2D const&) const;
		double cross(Vec2D const&) const;
		double length() const;
		double squareLength() const;
		double distTo(Vec2D const&); // get the distance between two points represented as vectors
		double squareDistTo(Vec2D const&);

	} Vec2D, Vector2D, Vec2;

	// binary operators
	Vec2D operator+(Vec2D const&, Vec2D const&); // vector addition
	Vec2D operator-(Vec2D const&, Vec2D const&); // vector subtraction
	Vec2D operator*(Vec2D const&, double);
	Vec2D operator*(double, Vec2D const&); // scalar multiplication
	Vec2D operator/(Vec2D const&, double); // scalar division

	double operator*(Vec2D const&, Vec2D const&); // dot product shorthand
}

#endif // LEDA_VECTOR_H_
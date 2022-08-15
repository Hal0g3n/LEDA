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

	typedef union {
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
		Vec2D& operator*=(double rhs);
		Vec2D& operator/=(double rhs);

		// unary operators
		Vec2D operator-() const;

		// member functions
		Vec2D normalize() const;
		Vec2D outward_normal() const;
		double length() const;
		double squareLength() const;

		// static functions
		static distance(Vec2D vec0, Vec2D vec1); // get the distance between two points represented as vectors
		static squareDistance(Vec2D vec0, Vec2D vec1);
		static dotProduct(Vec2D vec0, Vec2D vec1);
		static crossProductMagnitude(Vec2D vec0, Vec2D vec1);

	} Vec2D, Vector2D, Vec2;;

	// binary operators
	Vec2D operator+(Vec2D const& lhs, Vec2D const& rhs); // vector addition
	Vec2D operator-(Vec2D const& lhs, Vec2D const& rhs); // vector subtraction
	Vec2D operator*(Vec2D const& lhs, double rhs);
	Vec2D operator*(double lhs, Vec2D const& rhs); // scalar multiplication
	Vec2D operator/(Vec2D const& lhs, double rhs); // scalar division

	// 
}
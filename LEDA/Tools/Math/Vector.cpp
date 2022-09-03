/**
 * @file        Vector.cpp
 * @author      your name (you@domain.com)
 * @brief       Implementations for the Vector class methods
 * @version     0.1
 * @date        15-08-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */
#include "pch.h"
#include "LEDA_Math.h"
#include <cmath>

namespace LEDA {

	// constructors
	// default constructor: initialize to 0, 0
	Vec2D::Vec2D() : x(0), y(0) {}

	// constructor that initializes with specified values
	Vec2D::Vec2D(double _x, double _y) : x(_x), y(_y) {}

	// assignment operators
	Vec2D& Vec2D::operator+=(Vec2D const& rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	Vec2D& Vec2D::operator-=(Vec2D const& rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	Vec2D& Vec2D::operator*=(double rhs) {
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}

	Vec2D& Vec2D::operator/=(double rhs) {
		this->x /= rhs;
		this->y /= rhs;
		return *this;
	}

	// unary operators
	Vec2D Vec2D::operator-() const { 
		return Vec2D(-this->x, -this->y);
	}

	// binary operators
	Vec2D operator+(Vec2D const& lhs, Vec2D const& rhs) {
		return Vec2D(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	Vec2D operator-(Vec2D const& lhs, Vec2D const& rhs) {
		return Vec2D(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	Vec2D operator*(Vec2D const& lhs, double rhs) {
		return Vec2D(lhs.x * rhs, lhs.y * rhs);
	}

	Vec2D operator*(double lhs, Vec2D const& rhs) {
		return rhs * lhs;
	}

	// dot product binary operator
	double operator*(Vec2D const& lhs, Vec2D const& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	// member functions
	Vec2D Vec2D::normalize() const {
		return *this / this->length();
	}

	Vec2D Vec2D::rotateDeg(double angle) const {
		return Mtx33::rotateDeg(angle) * *this;
	}

	Vec2D Vec2D::rotateRad(double angle) const {
		return Mtx33::rotateRad(angle) * *this;
	}

	Vec2D Vec2D::rotateOutward() const {
		// special function to rotate by -pi/2, avoiding the trigo step and saving some computation
		return Vec2D(this->y, -this->x);
	}

	double Vec2D::dot(Vec2D const& other) const {
		return *this * other;
	}

	double Vec2D::cross(Vec2D const& other) const {
		return this->x * other.y - other.x * this->y;
	}

	double Vec2D::length() const {
		return sqrt(this->squareLength());
	}

	double Vec2D::squareLength() const {
		return this->x * this->x + this->y * this->y;
	}

	double Vec2D::distTo(Vec2D const& other) {
		return sqrt(this->squareDistTo(other));
	}

	double Vec2D::squareDistTo(Vec2D const& other) {
		return (other - *this).squareLength();
	}

}
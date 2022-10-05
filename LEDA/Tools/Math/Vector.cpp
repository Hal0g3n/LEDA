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

	Vec2D operator/(Vec2D const& lhs, double rhs) {
		return lhs * (1.0 / rhs);
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


	// 3D Vector
	// constructors
	// default constructor: initialize to 0, 0
	Vec3D::Vec3D() : x(0), y(0), z(0) {}

	// constructor that initializes with specified values
	Vec3D::Vec3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

	// assignment operators
	Vec3D& Vec3D::operator+=(Vec3D const& rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}

	Vec3D& Vec3D::operator-=(Vec3D const& rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		return *this;
	}

	Vec3D& Vec3D::operator*=(double rhs) {
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		return *this;
	}

	Vec3D& Vec3D::operator/=(double rhs) {
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		return *this;
	}

	// unary operators
	Vec3D Vec3D::operator-() const {
		return Vec3D(-this->x, -this->y, -this->z);
	}

	// binary operators
	Vec3D operator+(Vec3D const& lhs, Vec3D const& rhs) {
		return Vec3D(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	Vec3D operator-(Vec3D const& lhs, Vec3D const& rhs) {
		return Vec3D(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	Vec3D operator*(Vec3D const& lhs, double rhs) {
		return Vec3D(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
	}

	Vec3D operator*(double lhs, Vec3D const& rhs) {
		return rhs * lhs;
	}

	Vec3D operator/(Vec3D const& lhs, double rhs) {
		return lhs * (1.0 / rhs);
	}

	// dot product binary operator
	double operator*(Vec3D const& lhs, Vec3D const& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	// member functions
	Vec3D Vec3D::normalize() const {
		return *this / this->length();
	}

	Vec3D Vec3D::rotateDeg(double angle, Vec3D from) const {
		return Mtx44::rotateDeg(angle, from) * *this;
	}

	Vec3D Vec3D::rotateRad(double angle, Vec3D from) const {
		return Mtx44::rotateRad(angle, from) * *this;
	}

	// implement rotateOutward

	double Vec3D::dot(Vec3D const& other) const {
		return *this * other;
	}

	double Vec3D::cross(Vec3D const& other) const {
		return sqrt((this->x * other.y - other.x * this->y) * (this->x * other.y - other.x * this->y) + (this->y * other.z - other.y * this->z) * (this->y * other.z - other.y * this->z) + (this->z * other.x - other.z * this->x) * (this->z * other.x - other.z * this->x));
	}

	double Vec3D::length() const {
		return sqrt(this->squareLength());
	}

	double Vec3D::squareLength() const {
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	double Vec3D::distTo(Vec3D const& other) {
		return sqrt(this->squareDistTo(other));
	}

	double Vec3D::squareDistTo(Vec3D const& other) {
		return (other - *this).squareLength();
	}
}
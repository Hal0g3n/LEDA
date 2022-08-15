#pragma once
namespace LEDA {

	union Vec2D {
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
		double magnitude() const;

	};
}
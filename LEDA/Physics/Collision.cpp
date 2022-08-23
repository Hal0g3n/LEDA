/******************************************************************************/
/*!
\file		Collision.cpp
\author 	Yap Yuan Xi
\par    	email: yuanxi.yap@digipen.edu
\date   	August 1, 2022
\brief		Implementation of Collision functions

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/
#include "pch.h"

using namespace LEDA;

/******************************************************************************/
/*!
Builds a line segment with the given center, scale dir
 */
/******************************************************************************/
void BuildLineSegment(LineSegment &lineSegment,
	                  const CSD1130::Vector2D &pos,
	                  float scale,
	                  float dir) {
	lineSegment = LineSegment{};

	// Calculate pt0, pt1
	lineSegment.m_pt0 = pos + scale / 2 * Vec2{ cos(dir), sin(dir) };
	lineSegment.m_pt1 = pos + scale / 2 * Vec2{ -cos(dir), -sin(dir) };

	// m_normal = (y, -x)
	lineSegment.m_normal = lineSegment.m_pt1 - lineSegment.m_pt0;
	lineSegment.m_normal.x = -lineSegment.m_normal.x;		   // Negate x
	std::swap(lineSegment.m_normal.x, lineSegment.m_normal.y); // Swap (-x) and y

	// Normalise the normal
	Vector2DNormalize(lineSegment.m_normal, lineSegment.m_normal);
}

/******************************************************************************/
/*!
Checks for collision between circle and line
 */
/******************************************************************************/
int CollisionIntersection_CircleLineSegment(const Circle &circle,
											const CSD1130::Vector2D &ptEnd,
											const LineSegment &lineSeg,
											CSD1130::Vector2D &interPt,
											CSD1130::Vector2D &normalAtCollision,
											float &interTime,
											bool & checkLineEdges) {

	// d indicates signed distance from line
	float d = Vector2DDotProduct(lineSeg.m_normal, circle.m_center - lineSeg.m_pt0);

	// Calculates the location of collision (neg/pos half plane)
	d = (d >= circle.m_radius) ? 1.0f : (d <= -circle.m_radius) ? -1.0f : 0.0f;

	// Check for edge collision if starting inbetween lines
	if (!d)
		return checkLineEdges ? CheckMovingCircleToLineEdge(true, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime) : 0;

	// Calculate v
	Vec2 v = ptEnd - circle.m_center;

	// Normal (m) of Bs -> Be
	Vec2 m{v.y, -v.x};
	// Save normalise computation as m only used to determine dir

	// Project Line towards circle by R (point vs line collision)
	Vec2 p0 = lineSeg.m_pt0 + d * circle.m_radius * lineSeg.m_normal, p1 = lineSeg.m_pt1 + d * circle.m_radius * lineSeg.m_normal;

	// Check for edge collision if line does not pass through path (P0, P1 on same side of path)
	if (Vector2DDotProduct(m, p0 - circle.m_center) * Vector2DDotProduct(m, p1 - circle.m_center) >= 0)
		return checkLineEdges ? CheckMovingCircleToLineEdge(false, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime) : 0;

	// Calculate Time of Intersection
	interTime = Vector2DDotProduct(lineSeg.m_normal, lineSeg.m_pt0 - circle.m_center) + d * circle.m_radius;
	interTime /= Vector2DDotProduct(lineSeg.m_normal, v);

	// Ignore if intersection does not happen this loop
	if (interTime < 0 || interTime > 1) return 0;

	// Calculate Intersection Point
	interPt = circle.m_center + v * interTime;

	// Calculate Normal at collision
	normalAtCollision = lineSeg.m_normal * d;

	// Collision Detected
	return 1;
}

/******************************************************************************/
/*!
Checks specifically for line edges
(Extra Credit)
*/
/******************************************************************************/
int CheckMovingCircleToLineEdge(bool withinBothLines,
								const Circle &circle,
								const CSD1130::Vector2D &ptEnd,
								const LineSegment &lineSeg,
								CSD1130::Vector2D &interPt,
								CSD1130::Vector2D &normalAtCollision,
								float &interTime) {
	// Calculate Velocity Vector v
	Vec2 v = ptEnd - circle.m_center;

	// Compute Normal to v
	Vec2 M{ v.y, -v.x }; Vector2DNormalize(M, M);
		
	// m is distance from circle to closest point
	float m;

	// s is shortast distance from closest point in circle's path
	float s;

	// To indicate if P0 or P1 is closer
	bool P0Side = false;
	
	if (withinBothLines) {
		// Checks the Collision Point
		P0Side = (Vector2DDotProduct(lineSeg.m_pt0 - circle.m_center, lineSeg.m_pt1 - lineSeg.m_pt0) > 0);

		// Computes the values
		m = Vector2DDotProduct((P0Side ? lineSeg.m_pt0 : lineSeg.m_pt1) - circle.m_center, v) / Vector2DLength(v);
		s = fabs(Vector2DDotProduct((P0Side ? lineSeg.m_pt0 : lineSeg.m_pt1) - circle.m_center, M));

		// Checks if circle is actually facing P0
		if (m < 0) return 0;

		// Checks if circle actually comes close enough to touch
		if (s > circle.m_radius) return 0;
	}
	else { // Circle not within both lines

		// Does circle path touch P0 or P1
		bool touch0 = (fabs(Vector2DDotProduct(lineSeg.m_pt0 - circle.m_center, M)) <= circle.m_radius);
		bool touch1 = (fabs(Vector2DDotProduct(lineSeg.m_pt1 - circle.m_center, M)) <= circle.m_radius);

		// Is it clear which is touched
		if (touch0 != touch1) P0Side = touch0;
		else if (!touch0 && !touch1) return 0; // Both are untouched

		// Calculate Distance along path till collision
		float m0 = Vector2DDotProduct(lineSeg.m_pt0 - circle.m_center, v) / Vector2DLength(v);
		float m1 = Vector2DDotProduct(lineSeg.m_pt1 - circle.m_center, v) / Vector2DLength(v);

		// Only case for this to be true is if both are true
		if (touch0 == touch1) P0Side = fabs(m0) < fabs(m1);

		if (P0Side) // P0 Collision
			if (m0 < 0) return 0; // Moving away lol
			else s = Vector2DDotProduct(lineSeg.m_pt0 - circle.m_center, M);
		else // P1 Collision
			if (m1 < 0) return 0; // Moving away lol
			else s = Vector2DDotProduct(lineSeg.m_pt1 - circle.m_center, M);

		// Assign the relevant m
		if (P0Side) m = m0;
		else m = m1;
	}
	
	// Passed all rejection tests

	// Now compute the actual s defined in notes
	s = sqrt(circle.m_radius * circle.m_radius - s * s);

	// Compute collision Time based on m and s
	interTime = (m - s) / Vector2DLength(v);

	if (interTime > 1) return 0;

	// Compute Collision Point and indicate there is collision
	interPt = circle.m_center + v * interTime;
	
	// Compute Normal
	normalAtCollision = P0Side ? lineSeg.m_pt0 : lineSeg.m_pt1;
	Vector2DNormalize(normalAtCollision, normalAtCollision - circle.m_center);
	return 1;
}

/******************************************************************************/
/*!
Checks for Collision between 2 circles
 */
/******************************************************************************/
int CollisionIntersection_CircleCircle(const Circle &circleA,
									   const CSD1130::Vector2D &velA,
									   const Circle &circleB,
									   const CSD1130::Vector2D &velB,
									   CSD1130::Vector2D &interPtA,
									   CSD1130::Vector2D &interPtB,
									   float &interTime) {
	// Compute Relative Velocity
	Vec2 v_rel = velA - velB;
	float rad_sum = circleA.m_radius + circleB.m_radius;

	// m is distance from circle to closest point
	float m = Vector2DDotProduct(circleB.m_center - circleA.m_center, v_rel) / Vector2DLength(v_rel);

	// s is shortast distance from closest point in circle's path
	float s = fabs(Vector2DDotProduct(circleB.m_center - circleA.m_center, { v_rel.y, -v_rel.x })) / Vector2DLength(v_rel);

	if (m < 0) return 0; // A moving away from circle
	if (s > rad_sum) return 0; // Line does not intersect circle

	// Compute s as defined in notes
	s = sqrt(rad_sum * rad_sum - s * s);
	interTime = (m - s) / Vector2DLength(v_rel);

	// Checks that it is not extension of v_rel that intersects circle
	if (interTime > 1 || interTime < 0) return 0;

	// Calculate Collision Points
	interPtA = circleA.m_center + velA * interTime;
	interPtB = circleB.m_center + velB * interTime;

	return 1;
}


/******************************************************************************/
/*!
	Calculates end point after circle collides with line
 */
/******************************************************************************/
void CollisionResponse_CircleLineSegment(const CSD1130::Vector2D &ptInter,
										 const CSD1130::Vector2D &normal,
										 CSD1130::Vector2D &ptEnd,
										 CSD1130::Vector2D &reflected) {
	// Calculate End using formula
	ptEnd = ptEnd - 2 * Vector2DDotProduct(ptEnd - ptInter, normal) * normal;

	// Normalise reflected displacement vector
	Vector2DNormalize(reflected, ptEnd - ptInter);
}

/******************************************************************************/
/*!
	Calculates end point for dynamic circles when collided with static circle
 */
/******************************************************************************/
void CollisionResponse_CirclePillar(const CSD1130::Vector2D &normal,
	const float &interTime,
	const CSD1130::Vector2D &ptStart,
	const CSD1130::Vector2D &ptInter,
	CSD1130::Vector2D &ptEnd,
	CSD1130::Vector2D &reflected) {

	UNREFERENCED_PARAMETER(interTime);
	UNREFERENCED_PARAMETER(ptStart);

	ptEnd = ptEnd - 2 * Vector2DDotProduct(ptEnd - ptInter, normal) * normal;

	// Normalise reflected displacement vector
	Vector2DNormalize(reflected, ptEnd - ptInter);
}

/******************************************************************************/
/*!
	Extra credits (Circle Collision with COM and COE)
 */
/******************************************************************************/
void CollisionResponse_CircleCircle(CSD1130::Vector2D &normal,
									const float interTime,
									CSD1130::Vector2D &velA,
									const float &massA,
									CSD1130::Vector2D &interPtA,
									CSD1130::Vector2D &velB,
									const float &massB,
									CSD1130::Vector2D &interPtB,
									CSD1130::Vector2D &reflectedVectorA,
									CSD1130::Vector2D &ptEndA,
									CSD1130::Vector2D &reflectedVectorB,
									CSD1130::Vector2D &ptEndB) {

	// Calculate P defined in notes (Scaled down by mA * mB to reduce computations)
	float P = 2.0f * (Vector2DDotProduct(velA, normal) - Vector2DDotProduct(velB, normal)) / (massA + massB);

	// Calculate Reflection Vectors
	reflectedVectorA = (velA - P * massB * normal);
	reflectedVectorB = (velB + P * massA * normal);

	// Calculate End Points
	ptEndA = interPtA + reflectedVectorA * (1.0f - interTime);
	ptEndB = interPtB + reflectedVectorB * (1.0f - interTime);
}

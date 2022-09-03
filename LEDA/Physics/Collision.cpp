/******************************************************************************/
/*!
\file		Collision.cpp
\author 	Yap Yuan Xi
\par    	email: yuanxi.yap@digipen.edu
\date   	August 1, 2022
\brief		Implementation of collision functions

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "pch.h"
#include "Collision.h"

using namespace LEDA;

/******************************************************************************/
/*!
	Builds a line segment with the given center, scale dir
 */
/******************************************************************************/
void LEDA::BuildLineSegment(LEDA::LineSegment &lineSegment,
	                  const LEDA::Vec2D &pos,
	                  double scale,
	                  double dir) {
	
	lineSegment = LEDA::LineSegment{};

	// Calculate pt0, pt1
	lineSegment.m_pt0 = pos + scale / 2 * Vec2{ cos(dir), sin(dir) };
	lineSegment.m_pt1 = pos + scale / 2 * Vec2{ -cos(dir), -sin(dir) };

	// m_normal = (y, -x)
	lineSegment.m_normal = lineSegment.m_pt1 - lineSegment.m_pt0;
	lineSegment.m_normal.x = -lineSegment.m_normal.x;		   // Negate x
	std::swap(lineSegment.m_normal.x, lineSegment.m_normal.y); // Swap (-x) and y

	// Normalise the normal
	lineSegment.m_normal = lineSegment.m_normal.normalize();

}

/******************************************************************************/
/*!
	Checks for collision between circle and line
 */
/******************************************************************************/
int LEDA::CollisionIntersection_CircleLineSegment(const Circle &circle,
											const LEDA::Vec2D &ptEnd,
											const LineSegment &lineSeg,
											LEDA::Vec2D &interPt,
											LEDA::Vec2D &normalAtCollision,
											double &interTime,
											bool & checkLineEdges) {

	// d indicates signed distance from line
	float d = lineSeg.m_normal * (circle.m_center - lineSeg.m_pt0);

	// Calculates the location of collision (neg/pos half plane)
	d = (d >= circle.m_radius) ? 1.0f : (d <= -circle.m_radius) ? -1.0f : 0.0f;

	// Check for edge collision if starting inbetween lines
	if (!d)
		return checkLineEdges ? LEDA::CheckMovingCircleToLineEdge(true, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime) : 0;

	// Calculate v
	Vec2D v = ptEnd - circle.m_center;

	// Normal (m) of Bs -> Be
	Vec2D m{v.y, -v.x};
	// Save normalise computation as m only used to determine dir

	// Project Line towards circle by R (point vs line collision)
	Vec2D p0 = lineSeg.m_pt0 + d * circle.m_radius * lineSeg.m_normal, p1 = lineSeg.m_pt1 + d * circle.m_radius * lineSeg.m_normal;

	// Check for edge collision if line does not pass through path (P0, P1 on same side of path)
	if ((m * (p0 - circle.m_center)) * (m * (p1 - circle.m_center)) >= 0)
		return checkLineEdges ? LEDA::CheckMovingCircleToLineEdge(false, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime) : 0;

	// Calculate Time of Intersection
	interTime = (lineSeg.m_normal * (lineSeg.m_pt0 - circle.m_center)) + d * circle.m_radius;
	interTime /= lineSeg.m_normal * v;

	// Ignore if intersection does not happen this loop
	if (interTime < 0 || interTime > 1) return 0;

	// Calculate Intersection Point
	interPt = circle.m_center + v * interTime;

	// Calculate Normal at collision
	normalAtCollision = lineSeg.m_normal * d;

	// Collision detected
	return 1;

}

/******************************************************************************/
/*!
	Checks for collision between circle and line edges (specifically)
*/
/******************************************************************************/
int LEDA::CheckMovingCircleToLineEdge(bool withinBothLines,
								const Circle &circle,
								const LEDA::Vec2D &ptEnd,
								const LineSegment &lineSeg,
								LEDA::Vec2D &interPt,
								LEDA::Vec2D &normalAtCollision,
								double &interTime) {
	// Calculate velocity vector v
	Vec2D v = ptEnd - circle.m_center;

	// Compute Normal to v
	Vec2D M { v.y, -v.x };
	M = M.normalize();
		
	// m is distance from circle to closest point
	float m;

	// s is shortast distance from closest point in circle's path
	float s;

	// To indicate if P0 or P1 is closer
	bool P0Side = false;
	
	if (withinBothLines) {
		// Checks the Collision Point
		P0Side = ((lineSeg.m_pt0 - circle.m_center) * (lineSeg.m_pt1 - lineSeg.m_pt0) > 0);

		// Computes the values
		m = (((P0Side ? lineSeg.m_pt0 : lineSeg.m_pt1) - circle.m_center) * v) / v.length();
		s = fabs(((P0Side ? lineSeg.m_pt0 : lineSeg.m_pt1) - circle.m_center) * M);

		// Checks if circle is actually facing P0
		if (m < 0) return 0;

		// Checks if circle actually comes close enough to touch
		if (s > circle.m_radius) return 0;
	}
	else { // Circle not within both lines

		// Does circle path touch P0 or P1
		bool touch0 = (fabs((lineSeg.m_pt0 - circle.m_center) * M)) <= circle.m_radius;
		bool touch1 = (fabs((lineSeg.m_pt1 - circle.m_center) * M)) <= circle.m_radius;

		// Is it clear which is touched
		if (touch0 != touch1) P0Side = touch0;
		else if (!touch0 && !touch1) return 0; // Both are untouched

		// Calculate Distance along path till collision
		float m0 = ((lineSeg.m_pt0 - circle.m_center) * v) / v.length();
		float m1 = ((lineSeg.m_pt1 - circle.m_center) * v) / v.length();

		// Only case for this to be true is if both are true
		if (touch0 == touch1) P0Side = fabs(m0) < fabs(m1);

		if (P0Side) // P0 Collision
			if (m0 < 0) return 0; // Moving away lol
			else s = (lineSeg.m_pt0 - circle.m_center) * M;
		else // P1 Collision
			if (m1 < 0) return 0; // Moving away lol
			else s = (lineSeg.m_pt1 - circle.m_center) * M;

		// Assign the relevant m
		if (P0Side) m = m0;
		else m = m1;
	}
	
	// Passed all rejection tests

	// Now compute the actual s defined in notes
	s = sqrt(circle.m_radius * circle.m_radius - s * s);

	// Compute collision time based on m and s
	interTime = (m - s) / v.length();

	if (interTime > 1) return 0;

	// Compute Collision Point and indicate there is collision
	interPt = circle.m_center + v * interTime;
	
	// Compute Normal
	normalAtCollision = P0Side ? lineSeg.m_pt0 : lineSeg.m_pt1;
	normalAtCollision = (normalAtCollision - circle.m_center).normalize();
	return 1;
}

/******************************************************************************/
/*!
	Checks for collision between 2 circles
 */
/******************************************************************************/
int LEDA::CollisionIntersection_CircleCircle(const Circle &circleA,
									   const LEDA::Vec2D &velA,
									   const Circle &circleB,
									   const LEDA::Vec2D &velB,
									   LEDA::Vec2D &interPtA,
									   LEDA::Vec2D &interPtB,
									   double &interTime) {
	// Compute Relative Velocity
	LEDA::Vec2D v_rel = velA - velB;
	LEDA::Vec2D v_rel_normal = { v_rel.y, -v_rel.x };
	double rad_sum = circleA.m_radius + circleB.m_radius;

	// m is distance from circle to closest point
	double m = ((circleB.m_center - circleA.m_center) * v_rel) / v_rel.length();

	// s is shortast distance from closest point in circle's path
	double s = (fabs((circleB.m_center - circleA.m_center) * v_rel_normal)) / v_rel.length();

	if (m < 0) return 0; // A moving away from circle
	if (s > rad_sum) return 0; // Line does not intersect circle

	// Compute s as defined in notes
	s = sqrt(rad_sum * rad_sum - s * s);
	interTime = (m - s) / v_rel.length();

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
void LEDA::CollisionResponse_CircleLineSegment(const LEDA::Vec2D &ptInter,
										 const LEDA::Vec2D &normal,
										 LEDA::Vec2D &ptEnd,
										 LEDA::Vec2D &reflected) {
	// Calculate end using formula
	ptEnd = ptEnd - 2 * ((ptEnd - ptInter) * normal) * normal;

	// Normalise reflected displacement vector
	reflected = (ptEnd - ptInter).normalize();

}

/******************************************************************************/
/*!
	Calculates end point for dynamic circles when collided with static circle
 */
/******************************************************************************/
void LEDA::CollisionResponse_CirclePillar(const LEDA::Vec2D &normal,
	const double &interTime,
	const LEDA::Vec2D &ptStart,
	const LEDA::Vec2D &ptInter,
	LEDA::Vec2D &ptEnd,
	LEDA::Vec2D &reflected) {

	UNREFERENCED_PARAMETER(interTime);
	UNREFERENCED_PARAMETER(ptStart);

	ptEnd = ptEnd - 2 * ((ptEnd - ptInter) * normal) * normal;

	// Normalise reflected displacement vector
	reflected = (ptEnd - ptInter).normalize();

}

/******************************************************************************/
/*!
	Calculates end points for both circles when colliding
 */
/******************************************************************************/
void LEDA::CollisionResponse_CircleCircle(LEDA::Vec2D &normal,
									const double interTime,
									LEDA::Vec2D &velA,
									const double &massA,
									LEDA::Vec2D &interPtA,
									LEDA::Vec2D &velB,
									const double &massB,
									LEDA::Vec2D &interPtB,
									LEDA::Vec2D &reflectedVectorA,
									LEDA::Vec2D &ptEndA,
									LEDA::Vec2D &reflectedVectorB,
									LEDA::Vec2D &ptEndB) {

	// Calculate P defined in notes (Scaled down by mA * mB to reduce computations)
	float P = 2.0f * (float) (velA * normal - velB * normal) / (massA + massB);

	// Calculate Reflection Vectors
	reflectedVectorA = (velA - P * massB * normal);
	reflectedVectorB = (velB + P * massA * normal);

	// Calculate end points
	ptEndA = interPtA + reflectedVectorA * (1.0f - interTime);
	ptEndB = interPtB + reflectedVectorB * (1.0f - interTime);

}


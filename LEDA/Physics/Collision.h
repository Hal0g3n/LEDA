/**
 * @file        Collision.h
 * @author      your name (you@domain.com)
 * @brief       The collision function definitions
 * @version     0.1
 * @date        15-08-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */

#ifndef LEDA_COLLISION_H_
#define LEDA_COLLISION_H_

namespace LEDA { // LEDA Namespace

	/******************************************************************************/
	/*!
	 */
	 /******************************************************************************/
	void BuildLineSegment(LineSegment& lineSegment,			//Line segment reference - input
		const LEDA::Vector2D& pos,							//position - input
		float scale,										//scale - input
		float dir);											//direction - input

	/******************************************************************************/
	/*!
	 */
	 /******************************************************************************/
	struct Circle
	{
		LEDA::Vector2D  m_center;
		float	m_radius;

		// Extra credits
		float   m_mass{ 1.0f };
	};

	struct Ray
	{
		LEDA::Vector2D	m_pt0;
		LEDA::Vector2D	m_dir;
	};


	// INTERSECTION FUNCTIONS
	int CollisionIntersection_CircleLineSegment(const Circle& circle,			//Circle data - input
		const LEDA::Vector2D& ptEnd,											//End circle position - input
		const LineSegment& lineSeg,												//Line segment - input
		LEDA::Vector2D& interPt,												//Intersection point - output
		LEDA::Vector2D& normalAtCollision,										//Normal vector at collision time - output
		float& interTime,														//Intersection time ti - output
		bool& checkLineEdges);													//The last parameter is new - for Extra Credits: true = check collision with line segment edges

	// Extra credits
	int CheckMovingCircleToLineEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
		const Circle& circle,													//Circle data - input
		const LEDA::Vector2D& ptEnd,											//End circle position - input
		const LineSegment& lineSeg,												//Line segment - input
		LEDA::Vector2D& interPt,												//Intersection point - output
		LEDA::Vector2D& normalAtCollision,										//Normal vector at collision time - output
		float& interTime);														//Intersection time ti - output


	// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
	// In the case of "dynamic circle vs static pillar", velB will be 0.0f
	int CollisionIntersection_CircleCircle(const Circle& circleA,				//CircleA data - input
		const LEDA::Vector2D& velA,												//CircleA velocity - input
		const Circle& circleB,													//CircleB data - input
		const LEDA::Vector2D& velB,												//CircleA velocity - input
		LEDA::Vector2D& interPtA,												//Intersection point of CircleA at collision time - output
		LEDA::Vector2D& interPtB,												//Intersection point of CircleB at collision time - output
		float& interTime);														//intersection time - output






	// RESPONSE FUNCTIONS
	void CollisionResponse_CircleLineSegment(const LEDA::Vector2D& ptInter,		//Intersection position of the circle - input
		const LEDA::Vector2D& normal,											//Normal vector of reflection on collision time - input
		LEDA::Vector2D& ptEnd,													//Final position of the circle after reflection - output
		LEDA::Vector2D& reflected);												//Normalized reflection vector direction - output

	void CollisionResponse_CirclePillar(const LEDA::Vector2D& normal,			//Normal vector of reflection on collision time - input
		const float& interTime,													//Intersection time - input
		const LEDA::Vector2D& ptStart,											//Starting position of the circle - input
		const LEDA::Vector2D& ptInter,											//Intersection position of the circle - input
		LEDA::Vector2D& ptEnd,													//Final position of the circle after reflection - output
		LEDA::Vector2D& reflectedVectorNormalized);								//Normalized reflection vector - output

	void CollisionResponse_CircleCircle(LEDA::Vector2D& normal,					//Normal vector of reflection on collision time - input
		const float interTime,													//Intersection time - input
		LEDA::Vector2D& velA,													//Velocity of CircleA - input
		const float& massA,														//Mass of CircleA - input
		LEDA::Vector2D& interPtA,												//Intersection position of circle A at collision time - input
		LEDA::Vector2D& velB,													//Velocity of CircleB - input
		const float& massB,														//Mass of CircleB - input
		LEDA::Vector2D& interPtB,												//Intersection position of circle B at collision time - input
		LEDA::Vector2D& reflectedVectorA,										//Non-Normalized reflected vector of Circle A - output
		LEDA::Vector2D& ptEndA,													//Final position of the circle A after reflection - output
		LEDA::Vector2D& reflectedVectorB,										//Non-Normalized reflected vector of Circle B - output
		LEDA::Vector2D& ptEndB);												//Final position of the circle B after reflection - output

} // Namespace LEDA end

#endif // LEDA_COLLISION_H_
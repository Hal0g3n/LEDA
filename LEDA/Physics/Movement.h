/******************************************************************************/
/*!
\file		Collision.h
\author 	DigiPen
\par    	email: digipen\@digipen.edu
\date   	January 01, 20xx
\brief

Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#ifndef CSD1130_COLLISION_H_
#define CSD1130_COLLISION_H_


/******************************************************************************/
/*!
 */
/******************************************************************************/
struct LineSegment
{
	CSD1130::Vector2D	m_pt0;
	CSD1130::Vector2D	m_pt1;
	CSD1130::Vector2D	m_normal;
};

void BuildLineSegment(LineSegment &lineSegment,								//Line segment reference - input
					  const CSD1130::Vector2D &pos,									//position - input
					  float scale,											//scale - input
					  float dir);											//direction - input

/******************************************************************************/
/*!
 */
/******************************************************************************/
struct Circle
{
	CSD1130::Vector2D  m_center;
	float	m_radius;

	// Extra credits
	float   m_mass{ 1.0f };
};

struct Ray
{
	CSD1130::Vector2D	m_pt0;
	CSD1130::Vector2D	m_dir;
};


// INTERSECTION FUNCTIONS
int CollisionIntersection_CircleLineSegment(const Circle &circle,			//Circle data - input
	const CSD1130::Vector2D &ptEnd,													//End circle position - input
	const LineSegment &lineSeg,												//Line segment - input
	CSD1130::Vector2D &interPt,														//Intersection point - output
	CSD1130::Vector2D &normalAtCollision,												//Normal vector at collision time - output
	float &interTime,														//Intersection time ti - output
	bool & checkLineEdges);													//The last parameter is new - for Extra Credits: true = check collision with line segment edges

// Extra credits
int CheckMovingCircleToLineEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
	const Circle &circle,													//Circle data - input
	const CSD1130::Vector2D &ptEnd,													//End circle position - input
	const LineSegment &lineSeg,												//Line segment - input
	CSD1130::Vector2D &interPt,														//Intersection point - output
	CSD1130::Vector2D &normalAtCollision,												//Normal vector at collision time - output
	float &interTime);														//Intersection time ti - output


// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
// In the case of "dynamic circle vs static pillar", velB will be 0.0f
int CollisionIntersection_CircleCircle(const Circle &circleA,				//CircleA data - input
	const CSD1130::Vector2D &velA,														//CircleA velocity - input
	const Circle &circleB,													//CircleB data - input
	const CSD1130::Vector2D &velB,														//CircleA velocity - input
	CSD1130::Vector2D &interPtA,														//Intersection point of CircleA at collision time - output
	CSD1130::Vector2D &interPtB,														//Intersection point of CircleB at collision time - output
	float &interTime);														//intersection time - output






// RESPONSE FUNCTIONS
void CollisionResponse_CircleLineSegment(const CSD1130::Vector2D &ptInter,				//Intersection position of the circle - input
	const CSD1130::Vector2D &normal,													//Normal vector of reflection on collision time - input
	CSD1130::Vector2D &ptEnd,															//Final position of the circle after reflection - output
	CSD1130::Vector2D &reflected);														//Normalized reflection vector direction - output

void CollisionResponse_CirclePillar(const CSD1130::Vector2D &normal,					//Normal vector of reflection on collision time - input
	const float &interTime,													//Intersection time - input
	const CSD1130::Vector2D &ptStart,													//Starting position of the circle - input
	const CSD1130::Vector2D &ptInter,													//Intersection position of the circle - input
	CSD1130::Vector2D &ptEnd,															//Final position of the circle after reflection - output
	CSD1130::Vector2D &reflectedVectorNormalized);										//Normalized reflection vector - output

// Extra credits
void CollisionResponse_CircleCircle(CSD1130::Vector2D &normal,							//Normal vector of reflection on collision time - input
	const float interTime,													//Intersection time - input
	CSD1130::Vector2D &velA,															//Velocity of CircleA - input
	const float &massA,														//Mass of CircleA - input
	CSD1130::Vector2D &interPtA,														//Intersection position of circle A at collision time - input
	CSD1130::Vector2D &velB,															//Velocity of CircleB - input
	const float &massB,														//Mass of CircleB - input
	CSD1130::Vector2D &interPtB,														//Intersection position of circle B at collision time - input
	CSD1130::Vector2D &reflectedVectorA,												//Non-Normalized reflected vector of Circle A - output
	CSD1130::Vector2D &ptEndA,															//Final position of the circle A after reflection - output
	CSD1130::Vector2D &reflectedVectorB,												//Non-Normalized reflected vector of Circle B - output
	CSD1130::Vector2D &ptEndB);														//Final position of the circle B after reflection - output



#endif // CSD1130_COLLISION_H_
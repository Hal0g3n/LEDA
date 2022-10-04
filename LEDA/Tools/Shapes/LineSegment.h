/**
 * @file        LineSegment.h
 * @author      your name (you@domain.com)
 * @brief       The class representing a line segment
 * @version     0.1
 * @date        15-08-2022
 * 
 * @copyright   Copyright (c) 2022
 * 
 */

#pragma once
#include <LEDA_Math.h>

namespace LEDA {
    class LineSegment {
        Vec2 m_pt0, m_pt1, m_normal;
    };
}
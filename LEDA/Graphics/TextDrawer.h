/**
 * @file        TextDrawer.h
 * @author      your name (you@domain.com)
 * @brief       A drawer with text in it.
 * @version     0.1
 * @date        16-02-2023
 *
 * @copyright   Copyright (c) 2023
 */

#pragma once

#ifndef LEDA_TEXT_DRAWER_H_
#define LEDA_TEXT_DRAWER_H_

#include "pch.h"

#include "LEDA_Graphics.h"
#include "LEDA_Math.h"
#include "LEDA_System.h"
#include "LEDA_Components.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace LEDA {

	void initializeTextDrawer();

	void LEDA_API drawText(std::string string);

	void freeTextDrawer();

}


#endif // LEDA_TEXT_DRAWER_H_
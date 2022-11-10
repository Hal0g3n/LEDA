/**
 * @file        FrameRateController.h
 * @author      your name (you@domain.com)
 * @brief       Header for Frame Rate Manager
 * @version     0.1
 * @date        06-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#include "pch.h"

namespace LEDA {
	class FrameRateController {
		// things to track
		int frameCount;
		double frameStartTime;
		double lastFrameTime;

	public:
		// functions for frame rate controller
		void frameStart(); // starts the frame
		void frameEnd(); // ends the frame and updates the last frame time
		double getFrameTime(); // gets the frame time
		int getFrameCount(); // gets total frame count
	};
}
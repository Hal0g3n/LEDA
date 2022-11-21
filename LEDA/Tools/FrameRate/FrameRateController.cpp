/**
 * @file        FrameRateController.cpp
 * @author      your name (you@domain.com)
 * @brief       Source for Frame Rate Manager
 * @version     0.1
 * @date        06-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#include "pch.h"
#include "FrameRateController.h"

namespace LEDA {
	FrameRateController::FrameRateController() : frameCount(0), frameStartTime(std::chrono::system_clock::now()), lastFrameTime(0), inFrame(false) {}

	void FrameRateController::frameStart() {
		if (inFrame) return;
		// starts the frame by logging the start time of the new frame
		inFrame = true;
		frameStartTime = std::chrono::system_clock::now();
	}

	void FrameRateController::frameEnd() {
		if (!inFrame) return;
		// update frame duration
		lastFrameTime = (std::chrono::system_clock::now() - frameStartTime).count();
		inFrame = false;

		// increment frames
		++frameCount;
	}

	double FrameRateController::getFrameTime() {
		return lastFrameTime;
	}

	int FrameRateController::getFrameCount() {
		return frameCount;
	}
}
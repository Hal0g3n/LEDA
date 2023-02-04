/**
 * @file        LEDA_Input.h
 * @author      your name (you@domain.com)
 * @brief       Defines some input functions and constants
 * @version     0.1
 * @date        06-09-2022
 * 
 * @copyright   Copyright (c) 2022
 * 
 */

#pragma once

#ifndef LEDA_INPUT_H_
#define LEDA_INPUT_H_

#include "pch.h"

#include "InputSystem.h"

#include "LEDA_Graphics.h"
#include <GLFW/glfw3.h>

using emptyFunction = void(*)();
// using emptyFunction = std::function<void(void)>; // don't know why this doesn't work
using callbackMap = std::map<int, std::vector<emptyFunction>>;

namespace LEDA {

	enum LEDA_API INPUT_KEY {

		KEY_UNKNOWN = -1,
		KEY_SPACE = 32,
		KEY_APOSTROPHE = 39, // '
		KEY_COMMA = 44, // ,
		KEY_MINUS, // -
		KEY_PERIOD, // .
		KEY_SLASH, //
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_SEMICOLON = 59,
		KEY_EQUAL = 61,
		KEY_A = 65,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_LEFT_BRACKET, // [
		KEY_BACKSLASH, // '\'
		KEY_RIGHT_BRACKET, // ]
		KEY_GRAVE_ACCENT = 96, // `
		KEY_WORLD_1 = 161,
		KEY_WORLD_2,
		KEY_ESCAPE = 256,
		KEY_ENTER,
		KEY_TAB,
		KEY_BACKSPACE,
		KEY_INSERT,
		KEY_DELETE,
		KEY_RIGHT,
		KEY_LEFT,
		KEY_DOWN,
		KEY_UP,
		KEY_PAGE_UP,
		KEY_PAGE_DOWN,
		KEY_HOME,
		KEY_END,
		KEY_CAPS_LOCK = 280,
		KEY_SCROLL_LOCK,
		KEY_NUM_LOCK,
		KEY_PRINT_SCREEN,
		KEY_PAUSE,
		KEY_F1 = 290,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_F13,
		KEY_F14,
		KEY_F15,
		KEY_F16,
		KEY_F17,
		KEY_F18,
		KEY_F19,
		KEY_F20,
		KEY_F21,
		KEY_F22,
		KEY_F23,
		KEY_F24,
		KEY_F25,
		KEY_KP_0 = 320,
		KEY_KP_1,
		KEY_KP_2,
		KEY_KP_3,
		KEY_KP_4,
		KEY_KP_5,
		KEY_KP_6,
		KEY_KP_7,
		KEY_KP_8,
		KEY_KP_9,
		KEY_KP_DECIMAL,
		KEY_KP_DIVIDE,
		KEY_KP_MULTIPLY,
		KEY_KP_SUBTRACT,
		KEY_KP_ADD,
		KEY_KP_ENTER,
		KEY_KP_EQUAL,
		KEY_LEFT_SHIFT = 340,
		KEY_LEFT_CONTROL,
		KEY_LEFT_ALT,
		KEY_LEFT_SUPER,
		KEY_RIGHT_SHIFT,
		KEY_RIGHT_CONTROL,
		KEY_RIGHT_ALT,
		KEY_RIGHT_SUPER,
		KEY_MENU,

		// other names (for convenience)
		KEY_LAST = KEY_MENU,

	};

	void LEDA_API initializeInput(bool stickyKeys = false);

	void LEDA_API doInput();

	bool LEDA_API keyPressed(INPUT_KEY key);
	bool LEDA_API keyRepeated(INPUT_KEY key);

	// use event listeners instead
	/*
	bool LEDA_API keyTriggered(LEDA::KEY key);
	bool LEDA_API keyReleased(LEDA::KEY key);
	*/

	// how to store key trigger/release callback functions:
	// the 3 callback maps
	callbackMap triggerCallbacks;
	callbackMap releaseCallbacks;
	callbackMap repeatCallbacks;

	// functions for adding and removing event callbacks
	void LEDA_API addKeyTriggerCallback(INPUT_KEY key, emptyFunction function);
	void LEDA_API addKeyReleaseCallback(INPUT_KEY key, emptyFunction function);
	void LEDA_API addKeyRepeatCallback(INPUT_KEY key, emptyFunction function);

	void LEDA_API addKeyTriggerCallback(std::vector<INPUT_KEY> keys, emptyFunction function);
	void LEDA_API addKeyReleaseCallback(std::vector<INPUT_KEY> keys, emptyFunction function);
	void LEDA_API addKeyRepeatCallback(std::vector<INPUT_KEY> keys, emptyFunction function);

	void LEDA_API removeKeyTriggerCallback(INPUT_KEY key, emptyFunction function);
	void LEDA_API removeKeyReleaseCallback(INPUT_KEY key, emptyFunction function);
	void LEDA_API removeKeyRepeatCallback(INPUT_KEY key, emptyFunction function);

}

#endif // LEDA_INPUT_H_
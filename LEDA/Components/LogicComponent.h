/**
 * @file        LogicComponent.h
 * @author      your name (you@domain.com)
 * @brief       Stores logic information
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LOGIC_COMPONENTS_H_
#define LOGIC_COMPONENTS_H_

#include "pch.h"

#include "IComponent.h"

#include <functional>

namespace LEDA {

	// Example Creation (With lambdas)
	// new LogicComponent([] {}, [] {}, [] {});
	//
	// Example Creation (Without lambdas)
	// new LogicComponent(fname, fname, fname);

	struct LEDA_API LogicComponent : IComponent {
		std::function<void(void)> init = []() {}, update = []() {}, free = []() {}; // [](){}[](){}[](){} might as well set default lambdas for fun [](){}[](){}[](){}
		
		LogicComponent(std::function<void(void)> i, std::function<void(void)> u, std::function<void(void)> f):
			init{ i }, update{ u }, free{ f } {}
	};

}

#endif // LOGIC_COMPONENTS_H_
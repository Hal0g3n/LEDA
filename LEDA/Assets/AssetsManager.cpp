/**
 * @file        AssetsManager.cpp
 * @author      your name (you@domain.com)
 * @brief       ...
 * @version     0.1
 * @date        21-11-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"

#include "AssetsManager.h"

#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

using namespace LEDA;

bool AssetsManager::load(std::string filename) {

	std::ifstream filestream(filename);
	// should work?
	json data = json::parse(filestream);
	// testing
	std::cout << data.dump(4) << '\n';
	return true;

}

bool AssetsManager::loadNext(std::ifstream stream) { // note: ifstream does not have copy constructor, so it cannot be passed as a parameter i think
	return true; // successfully loaded
}

void* AssetsManager::getAsset(std::string assetName) {
	return nullptr; // temp
}
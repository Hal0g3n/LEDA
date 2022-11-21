/**
 * @file        SceneManager.cpp
 * @author      your name (you@domain.com)
 * @brief       ...
 * @version     0.1
 * @date        21-11-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"

#include <fstream>
#include "json.hpp"

#include "SceneManager.h"
#include "LEDA_Components.h"

using json = nlohmann::json;
using namespace LEDA;

void SceneManager::load(std::string filename) {
	// Check for file existance and open stream
	std::ifstream stream(filename);
	if (!stream.good()) throw std::runtime_error("Could not open file");

	// Getting the data to record
	json data = json::parse(stream);

	if (!data["assets"].is_null()) { // If additional assets exist
		for (auto &asset : data["assets"].items())
			if ("fonts" == asset.key())
				for (auto &s : asset.value()) ; // TODO: Figure out loading the asset from file name
			else if ("images" == asset.key())
				for (auto &s : asset.value()) ; // TODO: Figure out loading the asset from file name
	}

	if (!data["objects"].is_null()) { // If the game objects actually exist
		for (auto &obj : data["objects"].items()) {

			GameObject* cur = new GameObject();

			// For each obj component
			for (auto &comp : data["objects"].items())
				if ("position" == comp.key()) addComponent(*cur, new LogicComponent()); // Add component

			// Register the game object for retreival later
			registerGameObject(obj.key(), cur);
		}
	}
}

Asset* SceneManager::getAsset(std::string assetName) {
	return this->assets.find(assetName)->second;
}
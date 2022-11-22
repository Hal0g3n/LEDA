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

	// Check for file existence and open stream
	std::ifstream stream(filename);

	if (!stream.good()) {
		std::cout << "Could not open file: " << filename << std::endl;
		throw std::runtime_error("Could not open file");
	}

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

			// for each object component
			for (auto& comp : obj.value().items()) {
				std::string componentType = comp.key();
				auto& value = comp.value();
				if (componentType == "id") {
					// set id (will pull...)
				}
				else if (componentType == "transform") {
					TransformComponent* tc = new TransformComponent();
					// temporary attribute names (scalex and scaley are a bit weird (and scaly))
					if (!value["x"].is_null()) tc->position.x = value["x"];
					if (!value["y"].is_null()) tc->position.y = value["y"];
					if (!value["scale"].is_null()) {
						tc->scale.x = value["scale"];
						tc->scale.y = value["scale"];
					}
					if (!value["scalex"].is_null()) tc->scale.x = value["scalex"];
					if (!value["scaley"].is_null()) tc->scale.y = value["scaley"];
					if (!value["rotation"].is_null()) tc->rotation = value["rotation"];
					addComponent(*cur, new TransformComponent());
				}
				else if (componentType == "graphics") {
					GraphicsComponent* gc = new GraphicsComponent();
					if (!value["material"].is_null()) gc->material = value["material"];
					if (!value["shape"].is_null()) gc->shape = value["shape"];
					addComponent(*cur, gc);
				}
			}

			// Register the game object for retrieval later
			registerGameObject(obj.key(), cur);
		}
	}

}

Asset* SceneManager::getAsset(std::string assetName) {
	return this->assets.find(assetName)->second;
}
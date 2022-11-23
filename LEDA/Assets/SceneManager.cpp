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

#include <cstdio>
#include <fstream>
#include "json.hpp"

#include "SceneManager.h"
#include "LEDA_Components.h"

using json = nlohmann::json;
using namespace LEDA;

// some funny util function... move somewhere else?
std::vector<double> string2rgba(std::string hex) {
	int r, g, b, a;
	double w;
	if (hex.length() == 4) {
		sscanf_s(hex.c_str(), "#%01x%01x%01x", &r, &g, &b);
		a = 15;
		w = 15.0;
	}
	else if (hex.length() == 5) {
		sscanf_s(hex.c_str(), "#%01x%01x%01x%01x", &r, &g, &b, &a);
		w = 15.0;
	}
	else if (hex.length() == 7) {
		sscanf_s(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
		a = 255;
		w = 255.0;
	}
	else if (hex.length() == 9) {
		sscanf_s(hex.c_str(), "#%02x%02x%02x%02x", &r, &g, &b, &a);
		w = 255.0;
	}
	else {
		LOG_WARNING(std::string("hex string ") + hex + " is not properly formatted!");
	}
	return { r / w, g / w, b / w, a / w };
}

void SceneManager::load(std::string filename) {

	// Check for file existence and open stream
	std::ifstream stream(filename);

	if (!stream.good()) {
		std::cout << "Could not open file: " << filename << std::endl;
		throw std::runtime_error("Could not open file");
	}

	// read and parse scene data
	// also ignore comments because... yes
	json data = json::parse(stream, nullptr, true, true);

	if (!data["assets"].is_null()) { // If additional assets exist
		for (auto &asset : data["assets"].items())
			if ("fonts" == asset.key())
				for (auto &s : asset.value()) ; // TODO: Figure out loading the asset from file name
			else if ("images" == asset.key())
				for (auto &s : asset.value()) ; // TODO: Figure out loading the asset from file name
	}

	if (!data["objects"].is_null()) { // If the game object list actually exists

		unsigned int objectCount = 0;

		for (auto &entry : data["objects"].items()) {
			objectCount++;
			std::string id = "";
			auto& objectData = entry.value();
			if (objectData["id"].is_null()) {
				id = "entity #" + objectCount;
			}
			else {
				id = objectData["id"];
			}

			GameObject* obj = new GameObject(id);
			std::cout << "test" << std::endl;

			// for each object component
			for (auto& comp : objectData.items()) {
				std::string componentType = comp.key();
				auto& value = comp.value();
				if (componentType == "id") {
					// already used above
					continue;
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
					addComponent(obj, tc);
				}
				else if (componentType == "graphics") {
					GraphicsComponent* gc = new GraphicsComponent();
					if (!value["material"].is_null()) gc->material = value["material"];
					if (!value["shape"].is_null()) gc->shape = value["shape"];
					if (!value["color"].is_null()) {
						auto & objectColor = value["color"];
						if (objectColor.is_array()) {
							if (objectColor.size() > 0) {
								if (objectColor[0].is_number()) {
									gc->color.clear();
									for (auto& i : objectColor) {
										gc->color.push_back((double)i);
									}
								}
								else if (objectColor[0].is_string()) {
									gc->color.clear();
									for (auto& color : objectColor.items()) {
										for (double& i : string2rgba(color.value())) {
											gc->color.push_back(i);
										}
									}
								}
							}
							else {
								LOG_WARNING(std::string("color array empty! object id: ") + id);
							}
						}
						else if (objectColor.is_string()) {
							gc->color = string2rgba(objectColor);
						}
						gc->shape = value["shape"];
					}
					addComponent(obj, gc);
					if (getComponent<GraphicsComponent>(obj) == nullptr) {
						LOG_WARNING("skill issue: graphics component not existing despite being so a nanosecond ago");
					}
				}
				else if (componentType == "kinematics") {
					// TODO: kinematics component
				}
			}

			// Register the game object for retrieval later
			registerGameObject(obj->getId(), obj);

			// print game object for debugging TODO: remove
			std::cout << printGameObject(obj) << std::flush;
		}

	}

}

Asset* SceneManager::getAsset(std::string assetName) {
	return this->assets.find(assetName)->second;
}
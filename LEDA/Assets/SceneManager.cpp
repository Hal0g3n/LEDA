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

#define _USE_MATH_DEFINES
#include <cmath>
#include <corecrt_math_defines.h>

#include "SceneManager.h"
#include "LEDA_Components.h"

using json = nlohmann::json;
using namespace LEDA;

// some funny util function... move somewhere else?
std::vector<double> string2rgba(std::string hex) {
	int r = 0, g = 0, b = 0, a = 0;
	double w = 255.0;
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
	}
	else if (hex.length() == 9) {
		sscanf_s(hex.c_str(), "#%02x%02x%02x%02x", &r, &g, &b, &a);
	}
	else {
		LOG_WARNING(std::string("hex string ") + hex + " is not properly formatted!");
		return {};
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
	json data = json::parse(stream, nullptr, false, true);

	if (!data["assets"].is_null()) { // If additional assets exist

		// TODO: Find assets set difference
		// Load/Unload the diff
		for (auto &asset : data["assets"].items())
			if ("fonts" == asset.key())
				for (auto &s : asset.value().items()) ; // TODO: Figure out loading the asset from file name
			else if ("images" == asset.key())
				for (auto &s : asset.value().items()) ; // TODO: Figure out loading the asset from file name


	}

	if (!data["objects"].is_null()) { // If the game object list actually exists

		unsigned int objectCount = 0;

		for (auto &entry : data["objects"].items()) {
			auto& objectData = entry.value();

			// get the id and init game object
			// the id will be "unnamed entity #0" if an id is not provided
			GameObject* obj = new GameObject(
				objectData["id"].is_null() ?
				"unnamed entity #" + ++objectCount :
				objectData["id"]
			);

			// for each object component
			for (auto& comp : objectData.items()) {

				// Get the component type and values
				std::string componentType = comp.key();
				auto& value = comp.value();

				// Ignore the ID component
				if (componentType == "id") continue;

				else if (componentType == "transform") {
					TransformComponent* tc = new TransformComponent();

					// set values if they exist
					if (!value["x"].is_null()) tc->position.x = value["x"];
					if (!value["y"].is_null()) tc->position.y = value["y"];

					if (!value["scale"].is_null()) {
						if (value["scale"].is_number()) {
							tc->scale.x = value["scale"];
							tc->scale.y = value["scale"];
						}
						else {
							if (!value["scale"]["x"].is_null()) tc->scale.x = value["scale"]["x"];
							if (!value["scale"]["y"].is_null()) tc->scale.y = value["scale"]["y"];
						}
					}

					// scalex and scaley are a bit weird (and scaly)
					if (!value["scalex"].is_null()) tc->scale.x = value["scalex"];
					if (!value["scaley"].is_null()) tc->scale.y = value["scaley"];
					
					if (!value["rotation"].is_null()) tc->rotation = value["rotation"];
					if (!value["rotation_degrees"].is_null()) tc->rotation = value["rotation_degrees"] * M_PI / 180;

					addComponent(obj, tc);
				}

				else if (componentType == "graphics") {
					GraphicsComponent* gc = new GraphicsComponent();

					// set values if they exist
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
								LOG_WARNING(std::string("color array empty! object id: ") + obj->getId());
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
					KinematicsComponent* kc = new KinematicsComponent();

					// set values if they exist
					if (!value["vel"].is_null()) {
						if (!value["vel"]["x"].is_null()) kc->vel.x = value["vel"]["x"];
						if (!value["vel"]["y"].is_null()) kc->vel.y = value["vel"]["y"];
					}
					if (!value["velocity"].is_null()) {
						if (!value["velocity"]["x"].is_null()) kc->vel.x = value["velocity"]["x"];
						if (!value["velocity"]["y"].is_null()) kc->vel.y = value["velocity"]["y"];
					}
					if (!value["acc"].is_null()) {
						if (!value["acc"]["x"].is_null()) kc->acc.x = value["acc"]["x"];
						if (!value["acc"]["y"].is_null()) kc->acc.y = value["acc"]["y"];
					}
					if (!value["acceleration"].is_null()) {
						if (!value["acceleration"]["x"].is_null()) kc->acc.x = value["acceleration"]["x"];
						if (!value["acceleration"]["y"].is_null()) kc->acc.y = value["acceleration"]["y"];
					}
					if (!value["rot_vel"].is_null()) {
						kc->rot_vel = value["rot_vel"];
					}
					if (!value["rot_acc"].is_null()) {
						kc->rot_acc = value["rot_acc"];
					}
					if (!value["rot_vel_degrees"].is_null()) {
						kc->rot_vel = value["rot_vel_degrees"] * M_PI / 180;
					}
					if (!value["rot_acc_degrees"].is_null()) {
						kc->rot_acc = value["rot_acc_degrees"] * M_PI / 180;
					}

					// Add the component to the game object
					addComponent(obj, kc);
				}
			}

			// it always has a logic component
			LogicComponent* lc = new LogicComponent([] {}, [] {}, [] {});
			addComponent(obj, lc);
	
			// Register the game object to the system
			registerGameObject(obj->getId(), obj);

			// print game object for debugging TODO: remove
			std::cout << printGameObject(obj) << std::flush;
		}

	}
	else {
		LOG_WARNING(std::string("no game objects found in ") + filename);
	}

}

Asset* SceneManager::getAsset(std::string assetName) {
	return this->assets.find(assetName)->second;
}
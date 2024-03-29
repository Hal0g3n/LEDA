/**
 * @file        SceneManager.cpp
 * @author      your name (you@domain.com)
 * @brief       Not to be confused with SceneBuilder.
 * @version     0.1
 * @date        21-11-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"

#include <cstdio>
#include <fstream>
#include <filesystem>
#include <set>
#include "json.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <corecrt_math_defines.h>

#include "SceneManager.h"
#include "LEDA_Components.h"

using json = nlohmann::json;
using object = const nlohmann::json_abi_v3_11_2::detail::iteration_proxy_value<nlohmann::json_abi_v3_11_2::detail::iter_impl<nlohmann::json_abi_v3_11_2::json>>;
using namespace LEDA;

// File Scope Variables
unsigned int objectCount = 0;

// some funny utility function... move this somewhere else?
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

void LEDA::makeSegment(TransformComponent* tc, double x1, double y1, double x2, double y2, double thickness) {

	double x = (x1 + x2) / 2.0;
	tc->position.x = x;
	double y = (y1 + y2) / 2.0;
	tc->position.y = y;

	double r = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	tc->scale.x = r + thickness;
	tc->scale.y = thickness;

	tc->rotation = std::atan2(y2 - y1, x2 - x1);

	return;

}

void LEDA::setColor(GraphicsComponent* gc, std::string hex) {
	gc->color = string2rgba(hex);
}

GameObject* loadObject(object* entry, std::string objectId = "") {

	json& objectData = entry->value();

	// get the id and init game object
	// the id will be "unnamed entity #n" (where n is a non-negative integer) if an id is not provided anywhere
	if (objectData["id"].is_string()) {
		objectId = objectData["id"];
	}
	GameObject* obj = new GameObject(
		objectId != "" ?
		objectId.c_str() :
		"unnamed entity #" + ++objectCount
	);

	// for each object component
	for (auto& comp : objectData.items()) {

		// get the component type and values
		std::string componentType = comp.key();
		auto& value = comp.value();

		// ignore the ID component
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

			// scalex and scaley are a bit weird (and scaly/scaley)
			if (!value["scalex"].is_null()) tc->scale.x = value["scalex"];
			if (!value["scaley"].is_null()) tc->scale.y = value["scaley"];

			if (!value["rotation"].is_null()) tc->rotation = value["rotation"];
			if (!value["rotation_degrees"].is_null()) tc->rotation = value["rotation_degrees"] * M_PI / 180;

			if (!value["x1"].is_null() && !value["y1"].is_null() && !value["x2"].is_null() && !value["y2"].is_null()) {
				double x1 = value["x1"];
				double y1 = value["y1"];
				double x2 = value["x2"];
				double y2 = value["y2"];
				double thickness = value["thickness"];
				makeSegment(tc, x1, y1, x2, y2, thickness);
			}

			// add the transform component to the game object
			addComponent(obj, tc);
		}

		else if (componentType == "graphics") {
			GraphicsComponent* gc = new GraphicsComponent();

			// set values if they exist
			if (!value["material"].is_null()) gc->material = value["material"];
			if (!value["shape"].is_null()) gc->shape = value["shape"];
			if (!value["color"].is_null()) {
				auto& objectColor = value["color"];
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

			// add the graphics component to the game object
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

			// add the kinematics component to the game object
			addComponent(obj, kc);
		}

		else if (componentType == "collision") {
			CollisionComponent* cc = new CollisionComponent();

			// set values if they exist
			std::string shapeType = "rectangle";
			if (!value["type"].is_null() && value["type"].is_string()) {
				shapeType = value["type"];
			}
			if (shapeType == "rectangle") {
				cc->shape = new AABB();
			}
			else if (shapeType == "circle") {
				cc->shape = new Circle();
			}
			else if (shapeType == "line" || shapeType == "segment") {
				cc->shape = new LineSegment();
			}
			else {
				LOG_WARNING(std::string("funny/invalid collision shape: ") + shapeType);
			}
			if (!value["mass"].is_null()) {
				cc->m_mass = value["mass"];
			}
			if (!value["reflect"].is_null()) {
				cc->reflect = !(!value["reflect"]);
			}

			// add the collision component to the game object
			addComponent(obj, cc);
		}
	}

	// it always has a logic component
	LogicComponent* lc = new LogicComponent([] {}, [] {}, [] {});
	addComponent(obj, lc);

	// register the game object to the systems
	registerGameObject(obj->getId(), obj);

	// print game object for debugging (TODO: remove)
	std::cout << printGameObject(obj) << std::flush;

	return obj;
}

SceneManager::SceneManager() {

}

SceneManager::~SceneManager() {
	for (auto& it : this->objects) {
		delete it.second;
	}
}

void SceneManager::clear() {
	if (!this->assets.empty()) {
		this->assets.clear();
	}
	if (!this->objects.empty()) {
		this->objects.clear();
	}
}

void SceneManager::load(std::string filename) {

	// check for file existence and open stream
	std::ifstream stream(filename);

	if (!stream.good()) {
		LOG_WARNING(std::string("couldn't open file: ") + filename);
		throw std::runtime_error("Could not open file");
	}

	this->clear();

	// read and parse scene data
	// also ignore comments because... yes
	json data = json::parse(stream, nullptr, false, true);

	this->_json = data;

	// Will contain all unused paths at the end of asset loading
	std::set<std::filesystem::path> unused;
	for (std::pair<std::filesystem::path, Asset*> asset : assets)
		unused.insert(asset.first);

	// Clear out aliases
	alias.clear();

	if (!_json["assets"].is_null()) { // if additional assets exist

		for (auto& asset : _json["assets"].items()) { // For each asset type
			for (auto& s : asset.value().items()) { // For each asset

				// Load the canonical path of the item (unique path basically)
				std::filesystem::path p = s.value();
				p = std::filesystem::canonical(p);


				// Warning moment
				if (alias.find(s.key()) != alias.end())
					LOG_WARNING("Asset name conflict, overwriting asset with name " + s.key());


				// Insert into alias
				alias[s.key()] = p;

				// If asset is found
				if (assets.find(p) != assets.end()) {
					unused.erase(p);
					continue;
				}

				// Generate the asset (depending on type)
				if (asset.key() == "fonts") assets[p] = new Font(p.u8string());
				if (asset.key() == "images") assets[p] = new Image(p.u8string());
			}
		}
	}

	// If after loading assets it is unused
	// Delete them all
	for (std::filesystem::path k : unused) {
		delete assets[k];
		assets.erase(k);
	}


	if (!_json["objects"].is_null()) { // if the game object list exists
		objectCount = 0;
		for (auto &entry : _json["objects"].items()) {
			loadObject(&entry);
		}
	}
	else {
		LOG_WARNING(std::string("no game objects found in ") + filename);
	}

	if (!_json["templates"].is_null()) { // if the object template object exists
		for (object& entry : _json["templates"].items()) {
			object* entry_pointer = new object(entry);
			this->objects.emplace(std::make_pair(std::string(entry.key().c_str()), entry_pointer));
		}
	}
	else {
		// no warning...
		// LOG_WARNING(std::string("no game objects found in ") + filename);
	}

}

inline Asset* SceneManager::getAsset(std::string assetName) {
	return assets[alias[assetName]];
}

GameObject* SceneManager::createObject(std::string templateName, std::string objectId = "") {

	const std::unordered_map<std::string, object*>::iterator& it = this->objects.find(templateName);
	if (it == this->objects.end()) {
		LOG_WARNING(std::string("bad object template string: ") + templateName);
		return nullptr;
	}

	GameObject* result = loadObject(it->second, objectId);
	return result;

}
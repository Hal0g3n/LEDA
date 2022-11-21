/**
 * @file        Drawer.cpp
 * @author      your name (you@domain.com)
 * @brief       Game object drawing implementation. Not related to a piece of furniture.
 * @version     0.1
 * @date        07-09-2022
 *
 * @copyright   Copyright (c) 2022
 */


#include "pch.h"

#include "LEDA_Graphics.h"
#include "TransformComponent.h"
#include "GraphicsComponent.h"
#include "Drawer.h"

#include <GLFW/glfw3.h>

void LEDA::drawObject(GameObject& object) {

	/*
	TransformComponent* transformComponent = getComponent<TransformComponent>(object);
	GraphicsComponent* graphicsComponent = getComponent<GraphicsComponent>(object);

	glm::f32 * mat = transformMatrix(*transformComponent);

	// based on material
	std::string material = graphicsComponent->material;
	*/

}


void LEDA::drawObjects(std::vector<GameObject*> objects) {

	// get a list of materials
	std::unordered_map<std::string, std::vector<GameObject*>> materials = {};

	for (GameObject* object : objects) {
		GraphicsComponent* graphicsComponent = getComponent<GraphicsComponent>(*object);
		std::string material = graphicsComponent->material;
		if (materials.find(material) == materials.end()) {
			materials.emplace(material, std::initializer_list<GameObject*>{ object });
		}
		else {
			materials.at(material).push_back(object);
		}
	}

	for (std::pair<const std::string, std::vector<GameObject*>> &it : materials) {
		const std::string material = it.first;
		for (GameObject* object : it.second) {

			// get transform data
			TransformComponent* transformComponent = getComponent<TransformComponent>(*object);
			glm::f32* mat = transformMatrix(*transformComponent);

			if (material == "triangle") {

			}
			else if (material == "sus") {
				// todo: draw an amogus
			}

		}
	}

}
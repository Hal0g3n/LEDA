/**
 * @file        SceneManager.h
 * @author      your name (you@domain.com)
 * @brief       Not to be confused with SceneBuilder.
 * @version     0.1
 * @date        21-11-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_SCENE_MANAGER_H_
#define LEDA_SCENE_MANAGER_H_

#include "pch.h"

#include "LEDA_System.h"
#include "GameObject.h"
#include "IComponent.h"
#include "ISystem.h"
#include "IGameState.h"
#include "Asset.h"

#include <map>
#include <unordered_map>
#include <filesystem>
#include "json.hpp"

using json = nlohmann::json;
using object = const nlohmann::json_abi_v3_11_2::detail::iteration_proxy_value<nlohmann::json_abi_v3_11_2::detail::iter_impl<nlohmann::json_abi_v3_11_2::json>>; // a very very long comment just to make this line even longer!

namespace LEDA {

	void LEDA_API setColor(GraphicsComponent* gc, std::string hex);
	void LEDA_API makeSegment(TransformComponent* tc, double x1, double y1, double x2, double y2, double thickness);

	class LEDA_API SceneManager {
		// Json of the current level
		json _json;

		// For all assets used here, load name to alias (for better variable naming)
		std::unordered_map<std::string, std::filesystem::path> alias{};
		std::map<std::filesystem::path, Asset*> assets{};

		// List of all game objects
		std::unordered_map<std::string, object*> objects{};

	public:
		SceneManager();
		~SceneManager();
		void clear();
		void load(std::string);
		inline Asset* getAsset(std::string assetName);
		GameObject* createObject(std::string templateName, std::string objectId);
	};

}

#endif // LEDA_SCENE_MANAGER_H_
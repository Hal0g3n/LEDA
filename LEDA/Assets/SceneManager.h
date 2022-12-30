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

#include "GameObject.h"
#include "IComponent.h"
#include "ISystem.h"
#include "IGameState.h"
#include "Asset.h"

#include <map>
#include <unordered_map>

#include "json.hpp"

using json = nlohmann::json;
using object = const nlohmann::json_abi_v3_11_2::detail::iteration_proxy_value<nlohmann::json_abi_v3_11_2::detail::iter_impl<nlohmann::json_abi_v3_11_2::json>>;

namespace LEDA {

	class LEDA_API SceneManager {
		json _json;
		std::unordered_map<std::string, Asset*> assets{};
		std::unordered_map<std::string, object*> objects{};

	public:
		SceneManager();
		~SceneManager();
		void clear();
		void load(std::string);
		Asset* getAsset(std::string assetName);
		GameObject* createObject(std::string templateName, std::string objectId);

	};

}

#endif // LEDA_SCENE_MANAGER_H_
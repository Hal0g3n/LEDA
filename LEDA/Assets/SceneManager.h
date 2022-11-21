/**
 * @file        AssetsManager.h
 * @author      your name (you@domain.com)
 * @brief       ...
 * @version     0.1
 * @date        21-11-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

#ifndef LEDA_ASSETS_MANAGER_H_
#define LEDA_ASSETS_MANAGER_H_

#include "pch.h"

#include "GameObject.h"
#include "IComponent.h"
#include "ISystem.h"
#include "IGameState.h"
#include "Asset.h"


namespace LEDA {

	class LEDA_API SceneManager {
		std::map<std::string, Asset*> assets;

	public:
		void  load(std::string);
		Asset* getAsset(std::string);

	};

}

#endif // LEDA_ASSETS_MANAGER_H_
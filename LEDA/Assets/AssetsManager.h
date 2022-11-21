#ifndef ASSET_MANAGER_H_
#define ASSET_MANAGER_H_

#include "pch.h"

#include "GameObject.h"
#include "IComponent.h"
#include "ISystem.h"
#include "IGameState.h"


namespace LEDA {

	class AssetsManager {

	public:
		bool loadNext(std::ifstream);
		void* getAsset(std::string);
	};

}

#endif // ASSET_MANAGER_H_
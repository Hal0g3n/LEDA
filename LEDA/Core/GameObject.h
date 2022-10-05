/**
 * @file        GameObject.h
 * @author      your name (you@domain.com)
 * @brief       Game Object
 * @version     0.1
 * @date        04-10-2022
 *
 * @copyright   Copyright (c) 2022
 */

#ifndef LEDA_GAME_OBJECT_H_
#define LEDA_GAME_OBJECT_H_

#include "LEDA_System.h"

namespace LEDA {

	class GameObject : public IGameObject {

		GameObject();

	};

	void addComponent(GameObject& obj, IComponent component);
	IComponent getComponent(IGameObject& obj, std::string string);
}

#endif // LEDA_GAME_OBJECT_H_
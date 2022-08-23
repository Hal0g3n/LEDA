/**
 * @file        IGameState.h
 * @author      your name (you@domain.com)
 * @brief       Interface of for creating a GameState
 * @version     0.1
 * @date        22-08-2022
 *
 * @copyright   Copyright (c) 2022
 */

#pragma once

/**
 * @brief GameState Interface to inherit
 * 
 * load() => Called at first
 * init() => Called when (re)starting current state
 * update() => Called every frame
 * draw() => Called every frame (For Graphical Things)
 * free() => Called when ending current state (called before restart too)
 * unload() => Called when exiting current state
*/
__interface IGameState {
	virtual void load() = 0;
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void free() = 0;
	virtual void unload() = 0;
};
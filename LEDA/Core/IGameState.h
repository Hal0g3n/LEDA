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

namespace LEDA {
	/**
	 * @brief GameState Interface to inherit
	 *
	 * load() => Called at first
	 * unload() => Called when exiting current state
	*/
	__interface IGameState {
		virtual void load() const = 0;
		virtual void unload() const = 0;
	};


	// Setting Reserved Pointers QUIT and RESTART
	// These addresses are protected by system, so they are impossible values
	IGameState *Quit_GameState		= (IGameState *) 1;
	IGameState *Restart_GameState	= (IGameState *) 2;
}
/**
 * @file        Snake.cpp
 * @author      your name (you@domain.com)
 * @brief       ssssssssssssssssssssssssss
 * @version     0.1
 * @date        22-08-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"
#include <iostream>
#include <fstream>
#include "LEDA_Graphics.h"

using namespace LEDA;

void background_update() {
    GameObject* sus = retrieveGameObject("sus");

}

void sus_update() {
    GameObject* sus = retrieveGameObject("sus");
    TransformComponent* tc = getComponent<TransformComponent>(sus);
    tc->position.x = sin(LEDA::appTime * 5) * 100;
}

void snakey_wow() {

    GameObject* sus = retrieveGameObject("sus");
    LEDA::printGameObject(sus);
    LogicComponent* lc = getComponent<LogicComponent>(sus);
    lc->update = sus_update;

    std::cout << "yes" << std::endl;
    GameObject* among = sceneManager->createObject("among", "among us");
    std::cout << among << std::endl;
    TransformComponent* tc = getComponent<TransformComponent>(among);
    tc->position.x = 0;
    tc->position.y = 0;

    std::cout << "wow this works!" << std::endl;

}

int main() {

    std::cout << "ok time to make snake!" << std::endl;
    
    // return LEDA::test();

    LEDA::LEDA_INIT("snakey", snakey_wow);

    LEDA::LEDA_START(true, 60.0, "sneak", "snakey"); // initial state - change this to json filename

    std::cout << "Hello World!" << std::endl;
    return 0;

}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

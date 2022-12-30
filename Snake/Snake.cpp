/**
 * @file        Snake.cpp
 * @author      your name (you@domain.com)
 * @brief       ssssssssssssssssssssssssss (nake)
 * @version     0.1
 * @date        22-08-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"
#include <iostream>
#include <fstream>
#include "LEDA_Graphics.h"
#include "LEDA_Input.h"

using namespace LEDA;

#include <vector>
#include <random>
#include <queue>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

// apples
std::vector<std::pair<int, int>> apples;
std::vector<GameObject*> game_apples;

// snake
std::vector<std::pair<int, int>> snake_bodies;
std::vector<GameObject*> game_bodies;
std::deque<int> snake_directions;

int current_direction = 0; // up
                   // = 1; // down
                   // = 2; // right
                   // = 3; // left

bool apples_changed = false;

// randomness
std::random_device random_device;
std::mt19937 mt{ random_device() };
std::uniform_int_distribution<> random_x, random_y;

// main update function
void background_update() {

    // [only one update function for now...]
    GameObject* background = retrieveGameObject("background");

    // apple stuff
    if (apples.empty()) {
        apples.push_back(std::make_pair<int, int>(random_x(mt), random_y(mt)));
        apples_changed = true;
    }
    while (apples.size() > game_apples.size()) {
        game_apples.push_back(sceneManager->createObject("apple", std::string("apple") + std::to_string(game_apples.size())));
    }
    if (apples_changed) {
        for (size_t i = 0; i < apples.size(); ++i) {
            std::pair<int, int>& apple = apples[i];
            GameObject* o = game_apples[i];
            TransformComponent* tc = getComponent<TransformComponent>(o);
            tc->position.x = apple.first;
            tc->position.y = apple.second;
        }
    }

    // snakey stuff
    while (snake_bodies.size() > game_bodies.size()) {
        game_bodies.push_back(sceneManager->createObject("body", std::string("body") + std::to_string(game_bodies.size())));
    }
    for (size_t i = 0; i < snake_bodies.size(); ++i) {
        std::pair<int, int>& body = snake_bodies[i];
        GameObject* o = game_bodies[i];
        // special head things
        if (i == 0) {

        }
        // special body things
        else {

        }
        TransformComponent* tc = getComponent<TransformComponent>(o);
        tc->position.x = body.first;
        tc->position.y = body.second;
    }

    // more snakey stuff (but not LEDA related this time)
    snake_directions.push_front(current_direction);
    if (snake_directions.size() > snake_bodies.size()) {
        snake_directions.pop_back();
    }
    for (size_t i = 0; i < snake_directions.size(); ++i) {
        int delta_x = (current_direction >= 2) ? current_direction * 2 - 5 : 0;
        int delta_y = (current_direction >= 2) ? 0 : current_direction * 2 - 1;
        GameObject* o = game_bodies[i];
        KinematicsComponent* kc = getComponent<KinematicsComponent>(o);
        kc->vel.x = delta_x * 300;
        kc->vel.y = delta_y * 300;
        // std::cout << o->getId() << " " << kc->vel.x << " " << kc->vel.y << std::endl;
    }

}

void sus_update() {
    GameObject* sus = retrieveGameObject("sus");
    TransformComponent* tc = getComponent<TransformComponent>(sus);
    tc->position.x = sin(LEDA::appTime * 5) * 100;
}

void snakey_init() {

    int halfwidth = WINDOW_WIDTH / 2 - 50;
    int halfheight = WINDOW_HEIGHT / 2 - 50;

    random_x = std::uniform_int_distribution<>{ -halfwidth, halfwidth };
    random_y = std::uniform_int_distribution<>{ -halfheight, halfheight };

    // put initial snake "head"
    snake_bodies.push_back(std::make_pair<int, int>(123, 321));

    // keyboard input (snake control)
    addKeyTriggerCallback(INPUT_KEY::KEY_UP, []() {
        current_direction = 0;
    });
    addKeyTriggerCallback(INPUT_KEY::KEY_DOWN, []() {
        current_direction = 1;
    });
    addKeyTriggerCallback(INPUT_KEY::KEY_RIGHT, []() {
        current_direction = 2;
    });
    addKeyTriggerCallback(INPUT_KEY::KEY_LEFT, []() {
        current_direction = 3;
    });

    GameObject* background = retrieveGameObject("background");
    LogicComponent* lc = getComponent<LogicComponent>(background);
    lc->update = background_update;

    GameObject* sus = retrieveGameObject("sus");
    lc = getComponent<LogicComponent>(sus);
    lc->update = sus_update;

    GameObject* among = sceneManager->createObject("among", "amongst");
    TransformComponent* tc = getComponent<TransformComponent>(among);
    tc->position.x = 100;
    tc->position.y = 100;

    GameObject* among2 = sceneManager->createObject("among", "amongst us");
    tc = getComponent<TransformComponent>(among2);
    tc->position.x = -100;
    tc->position.y = -100;

}

void snakey_free() {

    for (GameObject* o : game_apples) {
        removeGameObject(o);
    }
    for (GameObject* o : game_bodies) {
        removeGameObject(o);
    }

}

int main() {

    std::cout << "ok, time to make snake!" << std::endl;
    
    // return LEDA::test();

    LEDA::LEDA_INIT("snakey", snakey_init, snakey_free);

    LEDA::LEDA_START(true, 60.0, "sneaky", "snakey"); // initial state - change this to json filename

    std::cout << "goodbye world!" << std::endl;
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

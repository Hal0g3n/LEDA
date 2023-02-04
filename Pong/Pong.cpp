/**
 * @file        Pong.cpp
 * @author      your name (you@domain.com)
 * @brief       ball goes boing, hopefully
 * @version     0.1
 * @date        01-01-2023
 *
 * @copyright   Copyright (c) 2023
 */

#include "pch.h"
#include <iostream>
#include <fstream>
#include "LEDA_Graphics.h"
#include "LEDA_Input.h"

using namespace LEDA;

#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

double paddle_vx = 0.0;
double paddle_size = 100.0;

void background_update() {

    GameObject* paddle = retrieveGameObject("paddle");
    TransformComponent* p_tc = getComponent<TransformComponent>(paddle);
    KinematicsComponent* p_kc = getComponent<KinematicsComponent>(paddle);

    p_tc->scale.x = paddle_size;
    p_kc->vel.x = paddle_vx;

}

void _init() {

    addKeyTriggerCallback(INPUT_KEY::KEY_UP, []() {
        // nothing (for now)
    });
    addKeyTriggerCallback(INPUT_KEY::KEY_RIGHT, []() {
        paddle_vx += 200;
    });
    addKeyTriggerCallback(INPUT_KEY::KEY_LEFT, []() {
        paddle_vx -= 200;
    });
    addKeyReleaseCallback(INPUT_KEY::KEY_RIGHT, []() {
        paddle_vx -= 200;
    });
    addKeyReleaseCallback(INPUT_KEY::KEY_LEFT, []() {
        paddle_vx += 200;
    });

    GameObject* background = retrieveGameObject("background");
    LogicComponent* lc = getComponent<LogicComponent>(background);
    lc->update = background_update;

}

void _free() {

}

int main() {

    std::cout << "note: this doesn't work yet." << std::endl;

    LEDA::LEDA_INIT("pong", _init, _free);

    LEDA::LEDA_START(true, 60.0, "pong", "pong");

    return 0;

}
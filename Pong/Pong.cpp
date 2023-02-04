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
#include <algorithm>
#include "LEDA_Graphics.h"
#include "LEDA_Input.h"

using namespace LEDA;

#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

const double PADDLE_SPEED = 200.0;

double paddle_vx = 0.0;
double paddle_size = 100.0;

template<typename T>
T bound(T number, T min, T max) {
    return std::max(std::min(number, max), min);
}

void background_update() {

    GameObject* paddle = retrieveGameObject("paddle");
    TransformComponent* p_tc = getComponent<TransformComponent>(paddle);
    KinematicsComponent* p_kc = getComponent<KinematicsComponent>(paddle);

    p_tc->scale.x = paddle_size;
    p_kc->vel.x = bound(paddle_vx, -PADDLE_SPEED, PADDLE_SPEED);

}

void _init() {

    addKeyTriggerCallback({ INPUT_KEY::KEY_UP, INPUT_KEY::KEY_W }, []() {
        // nothing (for now)
    });
    addKeyTriggerCallback({ INPUT_KEY::KEY_RIGHT, INPUT_KEY::KEY_D }, []() {
        paddle_vx += PADDLE_SPEED;
    });
    addKeyTriggerCallback({ INPUT_KEY::KEY_LEFT, INPUT_KEY::KEY_A }, []() {
        paddle_vx -= PADDLE_SPEED;
    });
    addKeyReleaseCallback({ INPUT_KEY::KEY_RIGHT, INPUT_KEY::KEY_D }, []() {
        paddle_vx -= PADDLE_SPEED;
    });
    addKeyReleaseCallback({ INPUT_KEY::KEY_LEFT, INPUT_KEY::KEY_A }, []() {
        paddle_vx += PADDLE_SPEED;
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
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
const int WALL_X = 350;
const int WALL_Y = 350;

const double PADDLE_SPEED = 200.0;
const unsigned int BALLS = 1;

double paddle_vx = 0.0;
double paddle_size = 100.0;

bool started = false;

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

void start() {
    if (started) return;
    started = true;

    // start the ball
    GameObject* ball = retrieveGameObject("ball1"); // this looks like balll
    KinematicsComponent* kc = getComponent<KinematicsComponent>(ball);
    kc->vel.x = paddle_vx;
    kc->vel.y = -200.0;

}

unsigned int number_of_walls = 0;
void add_wall(double x1, double y1, double x2, double y2) {
    GameObject* wall = sceneManager->createObject("wall", std::string("wall") + std::to_string(++number_of_walls));
    TransformComponent* tc = getComponent<TransformComponent>(wall);
    makeSegment(tc, x1 * WALL_X, y1 * WALL_Y, x2 * WALL_X, y2 * WALL_Y);
}

void _init() {

    addKeyTriggerCallback({ INPUT_KEY::KEY_UP, INPUT_KEY::KEY_W }, []() {
        // nothing (for now)
    });
    addKeyTriggerCallback({ INPUT_KEY::KEY_RIGHT, INPUT_KEY::KEY_D }, []() {
        paddle_vx += PADDLE_SPEED;
        start();
    });
    addKeyTriggerCallback({ INPUT_KEY::KEY_LEFT, INPUT_KEY::KEY_A }, []() {
        paddle_vx -= PADDLE_SPEED;
        start();
    });
    addKeyReleaseCallback({ INPUT_KEY::KEY_RIGHT, INPUT_KEY::KEY_D }, []() {
        paddle_vx -= PADDLE_SPEED;
        start();
    });
    addKeyReleaseCallback({ INPUT_KEY::KEY_LEFT, INPUT_KEY::KEY_A }, []() {
        paddle_vx += PADDLE_SPEED;
        start();
    });

    GameObject* background = retrieveGameObject("background");
    LogicComponent* lc = getComponent<LogicComponent>(background);
    lc->update = background_update;

    // add balls

    for (int i = 0; i < BALLS; i++) {
        GameObject* ball = sceneManager->createObject("ball", std::string("ball") + std::to_string(i + 1));
        TransformComponent* tc = getComponent<TransformComponent>(ball);
        tc->position.x = 0;
        tc->position.y = -280;
    }

    // add walls

    add_wall(1, 1, 1, -1);
    add_wall(1, -1, -1, -1);
    add_wall(-1, -1, -1, 1);
    add_wall(-1, 1, 1, 1);

}

void _free() {

}

int main() {

    std::cout << "note: this doesn't work yet." << std::endl;

    LEDA::LEDA_INIT("pong", _init, _free);

    LEDA::LEDA_START(true, 60.0, "pong", "pong");

    return 0;

}
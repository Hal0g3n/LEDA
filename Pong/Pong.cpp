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
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
#include <queue>

// randomness
std::random_device random_device;
std::mt19937 mt{ random_device() };
std::uniform_int_distribution<> random_x, random_y;
std::uniform_real_distribution<> random_angle;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int WALL_X = 350;
const int WALL_Y = 350;
const double WALL_THICKNESS = 5.0;

const double PADDLE_UP_SPEED = 300.0;
const double PADDLE_ACCELERATION = 4000.0;
const double BALL_X_SPEED = 300.0;
const double BALL_Y_SPEED = 400.0;
const unsigned int BALLS = 1;
const unsigned int BLOCKS = 10;

double paddle_ax = 0.0;
double paddle_ay = 0.0;
const double paddle_w_mult = 1.0;
double paddle_size = 100.0;

bool started = false;

std::vector<GameObject*> blocks;
std::deque<std::pair<Vec2, double>> shadows; // pair<position, time>

template<typename T>
T bound(T number, T min, T max) {
    return std::max(std::min(number, max), min);
}

template<typename T>
T bound(T number, T a) {
    return bound(number, -a, a);
}

bool starts_with(std::string s, std::string with) {
    return s.rfind(with, 0) == 0;
}

void background_update() {

    GameObject* paddle = retrieveGameObject("paddle");
    TransformComponent* p_tc = getComponent<TransformComponent>(paddle);
    KinematicsComponent* p_kc = getComponent<KinematicsComponent>(paddle);

    p_tc->position.x = bound(p_tc->position.x, WALL_X - paddle_size / 2);
    p_tc->scale.x = paddle_size;

    if (started) p_kc->acc.y = bound(paddle_ay, PADDLE_ACCELERATION);
    p_kc->vel.y *= 0.90;
    p_tc->position.y = (p_tc->position.y + 300) * 0.90 - 300;
    
    p_kc->acc.x = bound(paddle_ax, -PADDLE_ACCELERATION, PADDLE_ACCELERATION);
    p_kc->vel.x *= 0.90;
    
    p_kc->rot_vel = paddle_ax / PADDLE_ACCELERATION * paddle_w_mult;
    p_tc->rotation *= 0.90;

    GameObject* ball = retrieveGameObject("ball1"); // this looks like balll
    TransformComponent* tc = getComponent<TransformComponent>(ball);

    if (!started) {
        tc->position.x = p_tc->position.x;
    }
    else {
        shadows.push_front(std::make_pair(tc->position, appTime));
        while (shadows.back().second < appTime - 1) {
            shadows.pop_back();
        }
    }

}

void start() {

    if (started) return;
    started = true;

    // start the ball
    GameObject* ball = retrieveGameObject("ball1"); // this looks like balll
    KinematicsComponent* kc = getComponent<KinematicsComponent>(ball);
    kc->vel.x = BALL_X_SPEED;
    kc->vel.y = BALL_Y_SPEED;

}

void stop() {

    if (!started) return;
    started = false;

    // reset the paddle
    GameObject* paddle = retrieveGameObject("paddle");
    TransformComponent* p_tc = getComponent<TransformComponent>(paddle);
    p_tc->position = Vec2{ 0, -300.0 };
    p_tc->rotation = 0;
    KinematicsComponent* p_kc = getComponent<KinematicsComponent>(paddle);
    p_kc->acc = Vec2{ 0, 0 };
    p_kc->vel = Vec2{ 0, 0 };
    p_kc->rot_vel = 0;

    // reset the ball
    GameObject* ball = retrieveGameObject("ball1"); // this looks like balll
    TransformComponent* b_tc = getComponent<TransformComponent>(ball);
    b_tc->position.x = 0.0;
    b_tc->position.y = -280.0;
    KinematicsComponent* b_kc = getComponent<KinematicsComponent>(ball);
    b_kc->vel = Vec2{ 0, 0 };

}

void wall_touch(GameObject* wall, GameObject* ball) {
    std::string id = ball->getId();
    if (starts_with(id, "ball")) {
        stop();
    }
}

unsigned int number_of_walls = 0;
void add_wall(double x1, double y1, double x2, double y2, bool death = false) {
    GameObject* wall = sceneManager->createObject("wall", std::string("wall") + std::to_string(++number_of_walls));
    TransformComponent* tc = getComponent<TransformComponent>(wall);
    makeSegment(tc, x1 * WALL_X, y1 * WALL_Y, x2 * WALL_X, y2 * WALL_Y, WALL_THICKNESS);
    if (death) {
        GraphicsComponent* gc = getComponent<GraphicsComponent>(wall);
        setColor(gc, "#c00c0c");
        CollisionComponent* cc = getComponent<CollisionComponent>(wall);
        cc->collisionResponse = wall_touch;
    }
}

bool inside_play_area(double x, double y) {
    return bound(x, WALL_X + 0.0) == x && bound(y, 0.0, WALL_Y + 0.0) == y;
}

void block_touch(GameObject* block, GameObject* ball) {
    std::string id = ball->getId();
    std::cout << block->getId() << " " << id << std::endl;
    if (starts_with(id, "ball")) {
        //removeGameObject(block);
    }
}

unsigned int number_of_blocks = 0;
void add_block() {
    GameObject* block = sceneManager->createObject("block", std::string("block") + std::to_string(++number_of_blocks));
    TransformComponent* tc = getComponent<TransformComponent>(block);
    double x = -WINDOW_WIDTH;
    double y = -WINDOW_HEIGHT;
    double a = 0;
    double r = 40;
    while (!inside_play_area(x, y) || !inside_play_area(x + r * cos(a), y + r * sin(a))) {
        x = random_x(mt);
        y = random_y(mt);
        a = random_angle(mt);
    }
    makeSegment(tc, x, y, x + r * cos(a), y + r * sin(a), WALL_THICKNESS);
    CollisionComponent* cc = getComponent<CollisionComponent>(block);
    cc->collisionResponse = block_touch;
    blocks.push_back(block);
}

void _init() {

    random_x = std::uniform_int_distribution<>{ -WALL_X, WALL_X };
    random_y = std::uniform_int_distribution<>{ -WALL_Y, WALL_Y };
    random_angle = std::uniform_real_distribution<>{ -M_PI, M_PI };

    addKeyTriggerCallback({ INPUT_KEY::KEY_UP, INPUT_KEY::KEY_W }, []() {
        paddle_ay += PADDLE_ACCELERATION;
        start();
    });
    addKeyReleaseCallback({ INPUT_KEY::KEY_UP, INPUT_KEY::KEY_W }, []() {
        paddle_ay -= PADDLE_ACCELERATION;
    });
    addKeyTriggerCallback({ INPUT_KEY::KEY_RIGHT, INPUT_KEY::KEY_D }, []() {
        paddle_ax += PADDLE_ACCELERATION;
    });
    addKeyTriggerCallback({ INPUT_KEY::KEY_LEFT, INPUT_KEY::KEY_A }, []() {
        paddle_ax -= PADDLE_ACCELERATION;
    });
    addKeyReleaseCallback({ INPUT_KEY::KEY_RIGHT, INPUT_KEY::KEY_D }, []() {
        paddle_ax -= PADDLE_ACCELERATION;
    });
    addKeyReleaseCallback({ INPUT_KEY::KEY_LEFT, INPUT_KEY::KEY_A }, []() {
        paddle_ax += PADDLE_ACCELERATION;
    });

    GameObject* background = retrieveGameObject("background");
    LogicComponent* lc = getComponent<LogicComponent>(background);
    lc->update = background_update;

    // add balls

    for (unsigned int i = 0; i < BALLS; i++) {
        GameObject* ball = sceneManager->createObject("ball", std::string("ball") + std::to_string(i + 1));
        TransformComponent* tc = getComponent<TransformComponent>(ball);
        tc->position.x = 0.0;
        tc->position.y = -280.0;
    }

    // add walls

    add_wall(1, 1, 1, -1);
    add_wall(1, -1, -1, -1, true);
    add_wall(-1, -1, -1, 1);
    add_wall(-1, 1, 1, 1);
    //add_wall(0.1, -0.2, 0.5, -0.4);
    //add_wall(-0.2, -0.2, -0.3, 0.4);
    //add_wall(0.5, 0.5, 1, 1);

    // add blocks

    for (unsigned int i = 0; i < BLOCKS; i++) {
        add_block();
    }

    std::cout << "1";

}

void _free() {

}

int main() {

    std::cout << "note: this doesn't work yet." << std::endl;

    LEDA::LEDA_INIT("pong", _init, _free);

    LEDA::LEDA_START(true, 60.0, "pong", "pong");

    return 0;

}
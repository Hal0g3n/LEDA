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

int SNAKE_SPEED = 200;
int SNAKE_SIZE = 30;
int STARTING_SNAKE = 500;
int APPLE_SIZE = 30;
int MAX_APPLES = 10;
double SNAKE_TIME = (double) SNAKE_SIZE / SNAKE_SPEED;
double SNAKE_MAX_TIME = 180; // seconds

// apples
std::vector<std::pair<int, int>> apples;
std::vector<GameObject*> game_apples;

// snake
std::vector<std::pair<int, int>> snake_bodies;
std::vector<GameObject*> game_bodies;
std::deque<std::pair<std::pair<int, int>, double>> head_positions; // pair<position, time>

int current_direction = 1; // up
                   // = 0; // down
                   // = 3; // right
                   // = 2; // left

// randomness
std::random_device random_device;
std::mt19937 mt{ random_device() };
std::uniform_int_distribution<> random_x, random_y;

void background_update();
void snakey_init();
void snakey_free();
void apple_collide(GameObject*, GameObject*);

// 2 helper functions which could be included in LEDA

double lerp(double a, double b, double t) {
    return a * (1 - t) + b * t;
}

bool very_simple_rect_rect(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2) {
    return abs(x1 - x2) < (w1 + w2) / 2 && abs(y1 - y2) < (h1 + h2) / 2;
}

void add_snake_body() {
    std::pair<int, int> last_body = snake_bodies.empty() ? std::make_pair<int, int>(0, 0) : snake_bodies[snake_bodies.size() - 1];
    snake_bodies.push_back(std::make_pair(last_body.first, last_body.second));
}

void add_apple() {
    GameObject* o = sceneManager->createObject("apple", std::string("apple") + std::to_string(game_apples.size()));
    game_apples.push_back(o);
    TransformComponent* tc = getComponent<TransformComponent>(o);
    tc->position.x = 0.0 + random_x(mt);
    tc->position.y = 0.0 + random_y(mt);
    CollisionComponent* cc = getComponent<CollisionComponent>(o);
    cc->collisionResponse = apple_collide;
}

void apple_collide(GameObject* apple, GameObject* head) {
    // check if apple is collected by the head (and not another apple)
    if (head->getId() == "head") {
        // find this apple
        std::vector<GameObject *>::iterator found = std::find(game_apples.begin(), game_apples.end(), apple);
        // delete apple
        if (found != game_apples.end()) {
            game_apples.erase(found);
            removeGameObject(apple);
        }
        // increase snake size by 1
        add_snake_body();
    }
    else {
        return;
    }
}

// main update function
void background_update() {

    // [only one update function for now...]
    GameObject* background = retrieveGameObject("background");

    // apple stuff
    while (game_apples.size() < MAX_APPLES) {
        add_apple();
    }
    /*
    while (apples.size() < MAX_APPLES) {
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
            // check if apple is collected
            if (very_simple_rect_rect(apple.first, apple.second, APPLE_SIZE, APPLE_SIZE, snake_bodies[0].first, snake_bodies[0].second, SNAKE_SIZE, SNAKE_SIZE)) {
                // delete apple
                apples.erase(std::next(apples.begin(), i));
                // increase snake size by 1
                add_snake_body();
            }
        }
    }
    */

    // snakey stuff
    while (snake_bodies.size() > game_bodies.size()) {
        GameObject* o;
        if (game_bodies.empty()) {
            o = sceneManager->createObject("head", "head");
        }
        else {
            o = sceneManager->createObject("body", std::string("body") + std::to_string(game_bodies.size()));
        }
        game_bodies.push_back(o);
        TransformComponent* tc = getComponent<TransformComponent>(o);
        tc->position.x = snake_bodies[game_bodies.size() - 1].first;
        tc->position.y = snake_bodies[game_bodies.size() - 1].second;
    }
    for (size_t i = 0; i < snake_bodies.size(); ++i) {
        std::pair<int, int>& body = snake_bodies[i];
        GameObject* o = game_bodies[i];
        TransformComponent* tc = getComponent<TransformComponent>(o);
        // special head things
        if (i == 0) {
            body.first = tc->position.x;
            body.second = tc->position.y;
        }
        // special body things
        else {
            tc->position.x = body.first;
            tc->position.y = body.second;
        }
    }

    // more snakey stuff (but not LEDA related this time)

    head_positions.push_front(std::make_pair(snake_bodies[0], appTime));
    while (head_positions.back().second < appTime - SNAKE_MAX_TIME) {
        head_positions.pop_back();
    }

    int dir = current_direction;
    int delta_x = (dir >= 2) ? dir * 2 - 5 : 0;
    int delta_y = (dir >= 2) ? 0 : dir * 2 - 1;
    GameObject* o = game_bodies[0];
    KinematicsComponent* kc = getComponent<KinematicsComponent>(o);
    kc->vel.x = delta_x * SNAKE_SPEED;
    kc->vel.y = delta_y * SNAKE_SPEED;

    int j = 1;
    std::pair<std::pair<int, int>, double> old_position = std::make_pair(snake_bodies[0], appTime);
    for (size_t i = 0; i < head_positions.size(); ++i) {
        if (j >= snake_bodies.size()) {
            break;
        }
        const std::pair<std::pair<int, int>, double> position = head_positions[i];
        if (position.second < appTime - SNAKE_TIME * j) {
            double t = (appTime - SNAKE_TIME * j - position.second) / (old_position.second - position.second);
            snake_bodies[j].first = lerp(position.first.first, old_position.first.first, t);
            snake_bodies[j].second = lerp(position.first.second, old_position.first.second, t);
            j++;
        }
        old_position = position;
    }

    // make sure the snake is still on the screen!
    int head_x = snake_bodies[0].first;
    int head_y = snake_bodies[0].second;
    int halfwidth = WINDOW_WIDTH / 2;
    int halfheight = WINDOW_HEIGHT / 2;
    if (head_x < -halfwidth) {
        current_direction = 3;
    }
    else if (head_x > halfwidth) {
        current_direction = 2;
    }
    else if (head_y < -halfheight) {
        current_direction = 1;
    }
    else if (head_y > halfheight) {
        current_direction = 0;
    }

}

void snakey_init() {

    int halfwidth = WINDOW_WIDTH / 2 - 50;
    int halfheight = WINDOW_HEIGHT / 2 - 50;

    random_x = std::uniform_int_distribution<>{ -halfwidth, halfwidth };
    random_y = std::uniform_int_distribution<>{ -halfheight, halfheight };

    // put initial snake "head"
    for (int i = 0; i < STARTING_SNAKE; i++) {
        add_snake_body();
    }

    // keyboard input (snake control)
    addKeyTriggerCallback({ INPUT_KEY::KEY_UP, INPUT_KEY::KEY_W }, []() {
        current_direction = 1;
    });
    addKeyTriggerCallback({ INPUT_KEY::KEY_DOWN, INPUT_KEY::KEY_S }, []() {
        current_direction = 0;
    });
    addKeyTriggerCallback({ INPUT_KEY::KEY_RIGHT, INPUT_KEY::KEY_D }, []() {
        current_direction = 3;
    });
    addKeyTriggerCallback({ INPUT_KEY::KEY_LEFT, INPUT_KEY::KEY_A }, []() {
        current_direction = 2;
    });

    GameObject* background = retrieveGameObject("background");
    LogicComponent* lc = getComponent<LogicComponent>(background);
    lc->update = background_update;

    /*
    GameObject* among = sceneManager->createObject("among", "amongst");
    TransformComponent* tc = getComponent<TransformComponent>(among);
    tc->position.x = -100;
    tc->position.y = -100;

    GameObject* among2 = sceneManager->createObject("among", "amongst us");
    tc = getComponent<TransformComponent>(among2);
    tc->position.x = 100;
    tc->position.y = 100;
    */

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

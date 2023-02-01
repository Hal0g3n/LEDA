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

void _init() {

}

void _free() {

}

int main() {

    std::cout << "note: this doesn't work yet." << std::endl;

    LEDA::LEDA_INIT("pong", _init, _free);

    LEDA::LEDA_START(true, 60.0, "pong", "pong");

    return 0;

}
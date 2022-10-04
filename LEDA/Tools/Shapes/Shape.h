/**
 * @file        Shape.h
 * @author      your name (you@domain.com)
 * @brief       Header File of the generic Shape Class
 * @version     0.1
 * @date        15-08-2022
 * 
 * @copyright   Copyright (c) 2022
 * 
 */

#pragma once
#include <IComponent.h>
namespace LEDA {

    class Shape : IComponent { // The generic shape class
        Mesh pMesh;
    }

}
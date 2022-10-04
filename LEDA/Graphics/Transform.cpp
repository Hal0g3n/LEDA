/**
 * @file        Transform.cpp
 * @author      your name (you@domain.com)
 * @brief       Some transformation functions (implementations).
 * @version     0.1
 * @date        07-09-2022
 *
 * @copyright   Copyright (c) 2022
 */


#include "pch.h"

#include "Transform.h"

#include <GLFW/glfw3.h>

using namespace LEDA;

/*
// todo make transform component
glm::f32* LEDA::transformMatrix(TransformComponent transformComponent) {
    
}
*/

glm::f32* LEDA::transformMatrix(Vector2D translation, Vector2D scale, double rotation) {

    // initialize transformation matrix to the identity matrix
    glm::mat4 transform = glm::mat4(1.0f);
    // translate by [position]
    transform = glm::translate(transform, glm::vec3(translation.x, translation.y, 0.0f));
    // rotate by [rotation]
    transform = glm::rotate(transform, (float)rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    // scale by [scale]
    transform = glm::scale(transform, glm::vec3(scale.x, scale.y, 1.0f));
    // return a pointer, can be put into the glUniformMatrix4fv function (in this case)
    return glm::value_ptr(transform);

}
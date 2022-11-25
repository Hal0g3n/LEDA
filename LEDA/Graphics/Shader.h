/**
 * @file        Shader.h
 * @author      your name (you@domain.com)
 * @brief       Wow, a shader class definition
 * @version     0.1
 * @date        04-09-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */

// credit to https://learnopengl.com/ for the main idea and base code
// but i changed quite a lot?

#pragma once

#ifndef LEDA_SHADER_H_
#define LEDA_SHADER_H_

#include "pch.h"

#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LEDA {

    class LEDA_API Shader {

    public:
        // the shader program's ID
        unsigned int id;

        // constructors

        // this constructor just makes a default shader
        Shader();
        // this constructor is the most useful one... perhaps
        Shader(std::string shaderType);
        // this constructor makes the shader from 2 shader code strings
        Shader(std::string vertexCode, std::string fragmentCode);
        // this constructor makes the shader from 2 file paths (dynamically)
        Shader(const char* vertexPath, const char* fragmentPath);

        // use/activate the shader!
        void use();

        // utility uniform functions
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setFloat4(const std::string& name, float* value) const;
        void setFloat4(const std::string& name, double* value) const;
        void setFloat4(const std::string& name, float f1, float f2, float f3, float f4) const;
        void setFloat4(const std::string& name, double d1, double d2, double d3, double d4) const;
        void setFloat4(const std::string& name, std::vector<float> floats) const;
        void setFloat4(const std::string& name, std::vector<double> doubles) const;
        void setMatrix4(const std::string& name, glm::f32 * value) const;

    private:

        // for all the /set.*/ functions
        unsigned int getUniformLocation(const std::string& name) const;

        // checks for errors (used in the second most basic constructor (which one is that again))
        void checkForErrors(unsigned int shader, std::string type) const;

    };

}

#endif // LEDA_SHADER_H_
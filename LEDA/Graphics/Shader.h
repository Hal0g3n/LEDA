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

#ifndef LEDA_SHADER_H_
#define LEDA_SHADER_H_

#include "pch.h"
#include <glad/glad.h>

namespace LEDA {

    class LEDA_API Shader {

    public:
        // the shader program's ID
        unsigned int id;

        // constructors

        // this constructor just makes a default shader
        Shader();
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

    private:

        // checks for errors (used in the second most basic constructor (which one is that again))
        void checkForErrors(unsigned int shader, std::string type);

    };

}

#endif // LEDA_SHADER_H_
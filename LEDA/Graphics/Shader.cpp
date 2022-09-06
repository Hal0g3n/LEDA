/**
 * @file        Shader.cpp
 * @author      your name (you@domain.com)
 * @brief       Wow, an actual shader class
 * @version     0.1
 * @date        04-09-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */

#include "pch.h"
#include "Shader.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>


namespace LEDA {


    // public:

	// constructors

	Shader::Shader() {

        // hmmm blank shaders? not a thing
        Shader("", "");
        
	}

    Shader::Shader(std::string vertexString, std::string fragmentString) {

        const char* vertexCharArray = vertexString.c_str();
        const char* fragmentCharArray = fragmentString.c_str();

        // compile the shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexCharArray, NULL);
        glCompileShader(vertex);
        checkForErrors(vertex, "Vertex");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentCharArray, NULL);
        glCompileShader(fragment);
        checkForErrors(fragment, "Fragment");
        // shader program
        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        checkForErrors(id, "Program");
        // delete the shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }

	Shader::Shader(const char* vertexPath, const char* fragmentPath) {

        // retrieve the vertex/fragment source code from filePath
        std::string vertexString;
        std::string fragmentString;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexString = vShaderStream.str();
            fragmentString = fShaderStream.str();
        } catch (std::ifstream::failure& error) {
            std::cout << "Error: Shader file not read successfully! " << error.what() << std::endl;
        }

        Shader(vertexString, fragmentString);

    }

    // actually use the shader!

    void Shader::use()
    {
        glUseProgram(id);
    }

    // functions to set values (uniform) in the shader

    void Shader::setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void Shader::setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }


    // private:

    void Shader::checkForErrors(unsigned int shader, std::string type)
    {
        int success;
        char errorLog[1024];
        if (type != "Program")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, errorLog);
                std::cout << "Error: Shader program compile error of type '" << type << "'\n" << errorLog << "\n" << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, errorLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << errorLog << "\n" << std::endl;
            }
        }
    }

}
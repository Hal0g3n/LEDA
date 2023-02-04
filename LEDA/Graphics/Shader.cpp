/**
 * @file        Shader.cpp
 * @author      your name (you@domain.com)
 * @brief       wow, an actual shader class
 * @version     0.1
 * @date        04-09-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */

#include "pch.h"

#include "Shader.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// should only be for this class (for now), so it's just here
#include <fstream>
#include <sstream>


namespace LEDA {
    
    // public:

	// constructors

	Shader::Shader() {

        // hmmm blank shaders? not a thing
        id = 123456789;
        
	}

    Shader::Shader(std::string shaderType) {
        
        // set id here to prevent warning...
        id = 123456789;

        std::string vertexShaderCode, fragmentShaderCode;

        // WARNING: use of very funny-looking raw strings here

        if (shaderType == "solid") {

            vertexShaderCode = R"SHADER(

                #version 330 core
                layout (location = 0) in vec3 position;
                out vec4 vertexColor;
                uniform mat4 projection;
                uniform mat4 transform;
                uniform vec4 color;
                void main() {
                    gl_Position = projection * transform * vec4(position, 1.0);
                    vertexColor = color;
                }

            )SHADER";
            
            fragmentShaderCode = R"SHADER(

                #version 330 core
                layout (location = 0) out vec4 FragColor;
                in vec4 vertexColor;
                void main() {
                    FragColor = vertexColor;
                }

            )SHADER";

        }
        else if (shaderType == "solid_circle") {

            vertexShaderCode = R"SHADER(

                #version 330 core
                layout (location = 0) in vec3 position;
                out vec4 vertexColor;
                uniform mat4 projection;
                uniform mat4 transform;
                uniform vec4 color;
                varying vec2 v;
                void main() {
                    gl_Position = projection * transform * vec4(position, 1.0);
                    v = vec2(position) * vec2(2.0, 2.0);
                    vertexColor = color;
                }

            )SHADER";

            fragmentShaderCode = R"SHADER(

                #version 330 core
                layout (location = 0) out vec4 FragColor;
                in vec4 vertexColor;
                varying vec2 v;
                void main() {
                    float r = 1.0;
                    float dist = sqrt(dot(v, v));
                    if (dist >= r) {
                        discard;
                    }
                    float a = smoothstep(r, r - 0.01, dist);
                    FragColor = vertexColor * vec4(1.0, 1.0, 1.0, a);
                }

            )SHADER";

        }
        else if (shaderType == "transparent") {

            vertexShaderCode = R"SHADER(

                #version 330 core
                layout (location = 0) in vec3 aPos;
                uniform mat4 projection;
                uniform mat4 transform;
                uniform vec4 color;
                void main() {
                    gl_Position = vec4(0.0, 0.0, 0.0, 0.0);
                }

            )SHADER";

            fragmentShaderCode = R"SHADER(

                #version 330 core
                layout (location = 0) out vec4 FragColor;
                void main() {
                    FragColor = vec4(0.0, 0.0, 0.0, 0.0);
                }

            )SHADER";

        }
        else if (shaderType == "rainbow") {

            vertexShaderCode = "#version 460 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "layout (location = 1) in vec3 aColor;\n"
                "out vec3 color;\n"
                "uniform mat4 transform;\n"
                "uniform mat4 projection;\n"
                "void main() {\n"
                "   gl_Position = projection * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                "   color = aColor;\n"
                "}\n\0";
            fragmentShaderCode = "#version 460 core\n"
                "out vec4 FragColor;\n"
                "in vec3 color;\n"
                "void main() {\n"
                "   FragColor = vec4(color, 1.0f);\n"
                "}\n\0";
        }
        else {

        }

        const char* vertexCharArray = vertexShaderCode.c_str();
        const char* fragmentCharArray = fragmentShaderCode.c_str();

        // compile the shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexCharArray, NULL);
        glCompileShader(vertex);
        checkForErrors(vertex, "Vertex");
        // fragment shader
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
        // fragment shader
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
        glUniform1i(getUniformLocation(name), (int)value);
    }

    void Shader::setInt(const std::string& name, int value) const
    {
        glUniform1i(getUniformLocation(name), value);
    }

    void Shader::setFloat(const std::string& name, float value) const
    {
        glUniform1f(getUniformLocation(name), value);
    }

    void Shader::setFloat4(const std::string& name, float* value) const
    {
        glUniform4fv(getUniformLocation(name), 4, value);
    }

    void Shader::setFloat4(const std::string& name, double* value) const
    {
        this->setFloat4(name, value[0], value[1], value[2], value[3]);
    }

    void Shader::setFloat4(const std::string& name, float f1, float f2, float f3, float f4) const
    {
        glUniform4f(getUniformLocation(name), f1, f2, f3, f4);
    }

    void Shader::setFloat4(const std::string& name, double d1, double d2, double d3, double d4) const
    {
        this->setFloat4(name, (float)d1, (float)d2, (float)d3, (float)d4);
    }

    void Shader::setFloat4(const std::string& name, std::vector<float> floats) const
    {
        this->setFloat4(name, floats[0], floats[1], floats[2], floats[3]);
    }

    void Shader::setFloat4(const std::string& name, std::vector<double> doubles) const
    {
        this->setFloat4(name, doubles[0], doubles[1], doubles[2], doubles[3]);
    }

    void Shader::setMatrix4(const std::string& name, glm::f32 * value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, value);
    }


    // private:

    unsigned int Shader::getUniformLocation(const std::string& name) const
    {
        return glGetUniformLocation(id, name.c_str());
    }

    void Shader::checkForErrors(unsigned int shader, std::string type) const
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
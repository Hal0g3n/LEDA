/**
 * @file        Drawer.cpp
 * @author      your name (you@domain.com)
 * @brief       Game object drawing implementation. Not related to a piece of furniture.
 * @version     0.1
 * @date        07-09-2022
 *
 * @copyright   Copyright (c) 2022
 */


#include "pch.h"

#include "LEDA_Graphics.h"
#include "TransformComponent.h"
#include "GraphicsComponent.h"
#include "Drawer.h"

#include <GLFW/glfw3.h>

#include <iterator>
#include <unordered_map>

#include <ft2build.h>
#include FT_FREETYPE_H


// WINDOW_STUFF
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 800;
const char * WINDOW_NAME = "ok"; // not used
void WINDOW_RESIZE(GLFWwindow* window, int width, int height) {
	glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
}

std::unordered_map<std::string, LEDA::Shader> shaders;
std::unordered_map<std::string, std::tuple<unsigned int, unsigned int, unsigned int, unsigned int>> meshes;

// shapes
float triangle[] = {
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f,
};
unsigned int triangle_[] = {
	0, 1, 2,
};
// rectangle, circle, and line are all the same! wow!
float rectangle[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
};
unsigned int rectangle_[] = {
	0, 1, 3,
	1, 2, 3,
};
float circle[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
};
unsigned int circle_[] = {
	0, 1, 3,
	1, 2, 3,
};
float line[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
};
unsigned int line_[] = {
	0, 1, 3,
	1, 2, 3,
};
/*
float line[] = {
	0.501f, 0.001f, 0.0f,
	0.501f, -0.001f, 0.0f,
	-0.501f, -0.001f, 0.0f,
	-0.501f, 0.001f, 0.0f,
};
unsigned int line_[] = {
	0, 1, 3,
	1, 2, 3,
};
*/
float pentagon[] = {
	0.0f, 0.5f, 0.0f,
	0.4755f, 0.1545f, 0.0f,
	0.2939f, -0.4045f, 0.0f,
	-0.2939f, -0.4045f, 0.0f,
	-0.4755f, 0.1545f, 0.0f,
};
unsigned int pentagon_[] = {
	0, 1, 2,
	0, 2, 3,
	0, 3, 4,
};
float amogus[] = {
	// TODO: amogus vertices
	0.0f, 0.0f, 0.0f,
};

void LEDA::initializeDrawer() {

	std::cout << "initializing drawer... :)" << std::endl;

	glfwInit();

	// OpenGL version 4.6, but use 3.3 (what did I mean when I wrote this)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for os x and ios
	#endif

	// create GLFW window (global)
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, LEDA::windowTitle.c_str(), NULL, NULL);
	if (window == NULL) {
		std::cout << "error: failed to create GLFWindow\n";
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// be glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "error: failed to initialize GLAD! [>:( <-- not glad]\n";
		return;
	}

	// set resize window callback
	glfwSetFramebufferSizeCallback(window, WINDOW_RESIZE);

	// load default shaders here
	for (std::string shaderType : { "solid", "transparent", "solid_circle" }) {
		Shader shader{ shaderType };
		shaders.emplace(shaderType, shader);
	}

	// load default meshes here
	unsigned int VAO = 0, VBO = 0, EBO = 0;
	unsigned int numberOfVertices = 0;

	for (std::string meshType : { "triangle", "rectangle", "pentagon", "circle", "line" }) {

		float* vertices = nullptr;
		unsigned int* indices = nullptr;
		size_t sizeof_vertices = 0;
		size_t sizeof_indices = 0;
		if (meshType == "triangle") {
			vertices = triangle;
			indices = triangle_;
			sizeof_vertices = sizeof(triangle);
			sizeof_indices = sizeof(triangle_);
			numberOfVertices = std::size(triangle_);
		}
		else if (meshType == "rectangle") {
			vertices = rectangle;
			indices = rectangle_;
			sizeof_vertices = sizeof(rectangle);
			sizeof_indices = sizeof(rectangle_);
			numberOfVertices = std::size(rectangle_);
		}
		else if (meshType == "pentagon") {
			vertices = pentagon;
			indices = pentagon_;
			sizeof_vertices = sizeof(pentagon);
			sizeof_indices = sizeof(pentagon_);
			numberOfVertices = std::size(pentagon_);
		}
		else if (meshType == "circle") {
			vertices = circle;
			indices = circle_;
			sizeof_vertices = sizeof(circle);
			sizeof_indices = sizeof(circle_);
			numberOfVertices = std::size(circle_);
		}
		else if (meshType == "line") {
			vertices = line;
			indices = line_;
			sizeof_vertices = sizeof(line);
			sizeof_indices = sizeof(line_);
			numberOfVertices = std::size(line_);
		}
		else {
			LOG_WARNING(std::string("skill issue! unknown mesh type: '") + meshType + "'");
		}

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof_vertices, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof_indices, indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);

		meshes.emplace(meshType, std::make_tuple(VAO, VBO, EBO, numberOfVertices));

	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void LEDA::drawObjects(std::vector<GameObject*> objects) {

	// get a nice map of objects categorised by shapes
	std::unordered_map<std::string, std::vector<GameObject*>> shapes = {};

	for (GameObject* object : objects) {
		GraphicsComponent* graphicsComponent = getComponent<GraphicsComponent>(object);
		if (graphicsComponent == nullptr) continue;
		std::string shape = graphicsComponent->shape;
		if (meshes.find(shape) == meshes.end()) {
			LOG_WARNING(std::string("unknown game object shape: ") + shape);
			continue;
		}
		if (shapes.find(shape) == shapes.end()) {
			shapes.emplace(shape, std::initializer_list<GameObject*>{ object });
		}
		else {
			shapes.at(shape).push_back(object);
		}
	}

	// camera projection somethings
	glm::f32* projectionMatrix = transformMatrix(Vector2D(0.0, 0.0), Vector2D(2.0 / WINDOW_WIDTH, 2.0 / WINDOW_HEIGHT), 0.0);

	// actually draw the objects in this loop
	for (std::pair<const std::string, std::vector<GameObject*>> &it : shapes) {

		const std::string shape = it.first;

		unsigned int VAO = std::get<0>(meshes.at(shape));
		unsigned int VBO = std::get<1>(meshes.at(shape));
		unsigned int EBO = std::get<2>(meshes.at(shape));
		unsigned int numberOfVertices = std::get<3>(meshes.at(shape));

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		for (GameObject* object : it.second) {

			// get transform data
			TransformComponent* transformComponent = getComponent<TransformComponent>(object);
			//glm::f32* objectMatrix = transformMatrix(*transformComponent);
			
			// get graphics data
			GraphicsComponent* graphicsComponent = getComponent<GraphicsComponent>(object);
			// get material from graphics data
			std::string material = graphicsComponent->material;
			if (shape == "circle") {
				material += "_circle";
			}
			// get shader too, initialize it with shader type (material)
			Shader shader = shaders.at(material);

			// USE THE SHADER BEFORE SETTING UNIFORMS!!! a mistake was made
			shader.use();

			// set shader uniforms

			glm::f32* projectionMatrix = transformMatrix(Vector2D(0.0, 0.0), Vector2D(2.0 / WINDOW_WIDTH, 2.0 / WINDOW_HEIGHT), 0.0);
			//shader.setMatrix4("projection", projectionMatrix);
			unsigned int a_temp = glGetUniformLocation(shader.id, "projection");
			glUniformMatrix4fv(a_temp, 1, GL_FALSE, projectionMatrix);

			glm::f32* objectMatrix = transformMatrix(*transformComponent);
			//shader.setMatrix4("transform", objectMatrix);
			unsigned int b_temp = glGetUniformLocation(shader.id, "transform");
			glUniformMatrix4fv(b_temp, 1, GL_FALSE, objectMatrix);

			//shader.setFloat4("color", graphicsComponent->color);
			unsigned int c_temp = glGetUniformLocation(shader.id, "color");
			std::vector<double> cv_temp = graphicsComponent->color;
			glUniform4f(c_temp, (float)cv_temp[0], (float)cv_temp[1], (float)cv_temp[2], (float)cv_temp[3]);

			glDrawElements(GL_TRIANGLES, numberOfVertices, GL_UNSIGNED_INT, 0);

		}

		glBindVertexArray(0);

		/*
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		*/

	}

}

void LEDA::updateDrawer(std::vector<GameObject*> objects) {

	// draw background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // around #1f74c9 (no, it's just #000000 now)
	glClear(GL_COLOR_BUFFER_BIT);

	drawObjects(objects);

	// last thing to do
	glfwSwapBuffers(window);

}

void LEDA::freeDrawer() {

	std::cout << "killing drawer... :(" << std::endl;

	glfwTerminate();

}
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
#include "LEDA_Input.h"

#include <GLFW/glfw3.h>

#include <iterator>
#include <unordered_map>


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
float amogus[] = {
	// TODO: amogus vertices
	0.0f, 0.0f, 0.0f,
};

void LEDA::initializeDrawer() {

	std::cout << "initializing drawer..." << std::endl;

	glfwInit();

	// OpenGL version 4.6, but use 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for os x and ios
	#endif

	// create GLFW window (global)
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, LEDA::windowTitle.c_str(), NULL, NULL);
	if (window == NULL) {
		std::cout << "Error: failed to create GLFWindow\n";
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// be glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Error: failed to initialize GLAD! [>:( <-- not glad]\n";
		return;
	}

	// set resize window callback
	glfwSetFramebufferSizeCallback(window, WINDOW_RESIZE);


	// TODO: remove input functions from here

	Input::initializeInput();

	Input::addKeyTriggerCallback(Input::KEY::KEY_ESCAPE, []() {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	});

	// load default shaders here
	for (std::string shaderType : { "solid", "transparent" }) {
		Shader shader{ shaderType };
		shaders.emplace(shaderType, shader);
	}

	// load default meshes here
	unsigned int VAO = 0, VBO = 0, EBO = 0;
	unsigned int numberOfVertices = 0;

	for (std::string meshType : { "triangle", "rectangle" }) {

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

}

void LEDA::drawObjects(std::vector<GameObject*> objects) {

	// get a nice map of objects categorised by shapes
	std::unordered_map<std::string, std::vector<GameObject*>> shapes = {};

	for (GameObject* object : objects) {
		GraphicsComponent* graphicsComponent = getComponent<GraphicsComponent>(object);
		if (graphicsComponent == nullptr) continue;
		std::string shape = graphicsComponent->shape;
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

		/*
		const std::string shape = it.first;
		
		// bind the shape before drawing all objects with the same shape

		unsigned int numberOfVertices = 0;

		if (shape == "triangle") {
		}
		else if (shape == "rectangle" || shape == "square") {
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangle_), rectangle_, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);

			numberOfVertices = std::size(rectangle_);
		}
		else if (shape == "sus") {
			// TODO: draw an amogus (coming soon)
		}
		*/

		const std::string shape = it.first;

		unsigned int VAO = std::get<0>(meshes.at(shape));
		unsigned int VBO = std::get<1>(meshes.at(shape));
		unsigned int EBO = std::get<2>(meshes.at(shape));
		unsigned int numberOfVertices = std::get<3>(meshes.at(shape));

		for (GameObject* object : it.second) {

			// get transform data
			TransformComponent* transformComponent = getComponent<TransformComponent>(object);
			//glm::f32* objectMatrix = transformMatrix(*transformComponent);
			
			// get graphics data
			GraphicsComponent* graphicsComponent = getComponent<GraphicsComponent>(object);
			// get shader too, initialize it with shader type (material)
			Shader shader = shaders.at(graphicsComponent->material);

			// set shader uniforms

			glm::f32* projectionMatrix = transformMatrix(Vector2D(0.0, 0.0), Vector2D(2.0 / WINDOW_WIDTH, 2.0 / WINDOW_HEIGHT), 0.0);
			//shader.setMatrix4("projection", projectionMatrix);
			unsigned int a = glGetUniformLocation(shader.id, "projection");
			glUniformMatrix4fv(a, 1, GL_FALSE, projectionMatrix);

			glm::f32* objectMatrix = transformMatrix(*transformComponent);
			//shader.setMatrix4("transform", objectMatrix);
			unsigned int b = glGetUniformLocation(shader.id, "transform");
			glUniformMatrix4fv(b, 1, GL_FALSE, objectMatrix);

			//shader.setFloat4("color", graphicsComponent->color);

			shader.use();

			glBindVertexArray(VAO);
			// glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glDrawElements(GL_TRIANGLES, numberOfVertices, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

		}

		/*
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		*/

	}

}

void LEDA::updateDrawer(std::vector<GameObject*> objects) {

	glfwPollEvents();

	// draw background colour
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // around #1f74c9
	glClear(GL_COLOR_BUFFER_BIT);

	drawObjects(objects);

	glfwSwapBuffers(window);

}

void LEDA::freeDrawer() {

	std::cout << "killing drawer..." << std::endl;

	glfwTerminate();

}
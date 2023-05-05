#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"
#include "ObjectReader.hpp"
#include "Shader.hpp"

using namespace std;



class SceneManager {
public:
	static const GLuint WIDTH = 1000;
	static const GLuint HEIGHT = 1000;

	GLFWwindow* window;
	ObjectReader* reader;
	Object** objects;

	void initialize();
	int run();
	void updateCamera();
	void updateObjects();
	void doTransformation(Object* object);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	
};


#endif
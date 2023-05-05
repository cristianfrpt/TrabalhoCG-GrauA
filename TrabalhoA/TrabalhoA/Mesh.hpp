#ifndef MESH_H
#define MESH_H

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"


class Mesh {
public:
	Mesh(Shader* shader, GLuint VAO) {
		this->shader = shader;
		this->VAO = VAO;

	}

	Shader* shader;
	glm::mat4 transform;
	GLuint texID;
	GLuint VAO;


	Shader* getShader();
	glm::mat4 getTransform();
	GLuint getTexID();
	GLuint getVAO();

	void setShader(Shader*);
	void setTransform(glm::mat4);
	void setTexID(GLuint);
	void setVAO(GLuint);
};

#endif

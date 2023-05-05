#include "Mesh.hpp"


Shader* Mesh::getShader() {
	return shader;
}
glm::mat4 Mesh::getTransform() {
	return transform;
}
GLuint Mesh::getTexID() {
	return texID;
}
GLuint Mesh::getVAO() {
	return VAO;
}

void Mesh::setShader(Shader* newShader) {
	shader = newShader;
}
void Mesh::setTransform(glm::mat4 newTransform) {
	transform = newTransform;
}
void Mesh::setTexID(GLuint newTexID) {
	texID = newTexID;
}
void Mesh::setVAO(GLuint newVAO) {
	VAO = newVAO;
}
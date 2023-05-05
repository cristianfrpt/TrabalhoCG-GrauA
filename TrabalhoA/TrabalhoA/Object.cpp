#include "Object.hpp"


void Object::update()
{
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(angle), axis);
	model = glm::scale(model, scale);
	shader->setMat4("model", glm::value_ptr(model));
}

void Object::draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices);
	glBindVertexArray(0);
}


Shader* Object::getShader() {
	return shader;
}
glm::mat4 Object::getTransform() {
	return transform;
}
glm::vec3 Object::getPosition() {
	return position;
}
glm::vec3 Object::getScale() {
	return scale;
}
glm::vec3 Object::getAxis() {
	return axis;
}
float Object::getAngle() {
	return angle;
}

void Object::setShader(Shader* newShader) {
	shader = newShader;
}
void Object::setTransform(glm::mat4 newTransform) {
	transform = newTransform;
}
void Object::setPosition(glm::vec3 newPosition) {
	position = newPosition;
}
void Object::setScale(glm::vec3 newScale) {
	scale = newScale;
}
void Object::setAxis(glm::vec3 newAxis) {
	axis = newAxis;
}
void Object::setAngle(float newAngle) {
	angle = newAngle;
}

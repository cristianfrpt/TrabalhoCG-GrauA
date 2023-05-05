#include "SceneManager.hpp"



Camera* camera;
Shader* shader;
int selection = 1;
int operation = 0;
int direction = 0;

void SceneManager::initialize() {
	glfwInit();

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(WIDTH, HEIGHT, "Trabalho A", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, &SceneManager::key_callback);
	glfwSetCursorPosCallback(window, &SceneManager::mouse_callback);
	glfwSetScrollCallback(window, &SceneManager::mouse_scroll_callback);
	glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// GLAD: carrega todos os ponteiros d fun??es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glm::vec3 startPosition = glm::vec3(0.0, 0.0, 3.0);
	glm::vec3 startFront = glm::vec3(0.0, 0.0, -1.0);
	glm::vec3 startUp = glm::vec3(0.0, 1.0, 0.0);
	glm::mat4 startView = glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 startProjection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	float fov = 45;
	float zNear = 0.1;
	float zFar = 100;
	float cameraSpeed = 0.05;

	camera = new Camera(startPosition, startFront, startUp, fov, zNear, zFar, startView, startProjection, cameraSpeed);
	reader = new ObjectReader();
	shader = new Shader("Phong.vs", "Phong.fs");

	objects = (Object**)malloc(sizeof(Object**) * 3);


	objects[0] = reader->loadSimpleOBJ("../../3D_models/Suzanne/suzanneTriLowPoly.obj", shader, glm::vec3(0.0, 1.0, 1.0), glm::vec3(-3.0, 0.0, -1.0), glm::vec3(1.0, 1.0, 1.0));
	objects[1] = reader->loadSimpleOBJ("../../3D_models/Suzanne/suzanneTriLowPoly.obj", shader, glm::vec3(1.0, 1.0, 0.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(1.0, 1.0, 1.0));
	objects[2] = reader->loadSimpleOBJ("../../3D_models/Suzanne/suzanneTriLowPoly.obj", shader, glm::vec3(1.0, 0.0, 1.0), glm::vec3(3.0, 0.0, -1.0), glm::vec3(1.0, 1.0, 1.0));

	glUseProgram(shader->ID);

	glm::mat4 model = glm::mat4(1); //matriz identidade;
	GLint modelLoc = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(modelLoc, 1, FALSE, glm::value_ptr(model));

	//Definindo a matriz de view (posi??o e orienta??o da c?mera)
	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 6.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
	GLint viewLoc = glGetUniformLocation(shader->ID, "view");
	glUniformMatrix4fv(viewLoc, 1, FALSE, glm::value_ptr(view));

	//Definindo a matriz de proje??o perpectiva
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(shader->ID, "projection");
	glUniformMatrix4fv(projLoc, 1, FALSE, glm::value_ptr(projection));

	glEnable(GL_DEPTH_TEST);

	//Definindo as propriedades do material da superficie
	shader->setFloat("ka", 0.4);
	shader->setFloat("q", 10.0);

	//Definindo a fonte de luz pontual
	shader->setVec3("lightPos", -2.0, 10.0, 2.0);
	shader->setVec3("lightColor", 1.0, 1.0, 1.0);

	return;
};




int SceneManager::run() {
	while (!glfwWindowShouldClose(window)) {
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun??es de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		updateCamera();
		updateObjects();

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}




void SceneManager::updateObjects() {

	objects[0]->update();
	objects[0]->draw();

	objects[1]->update();
	objects[1]->draw();

	objects[2]->update();
	objects[2]->draw();

	if (operation < 4)
		doTransformation(objects[selection]);

}


void SceneManager::doTransformation(Object* object) {
	float angle = (GLfloat)glfwGetTime();
	if (operation == 1) {
		if (direction == 0) {
			object->setPosition(glm::vec3(object->getPosition().x, cos(angle), object->getPosition().z));
		}
		else if (direction == 1) {
			object->setPosition(glm::vec3(object->getPosition().x, object->getPosition().y, cos(angle)));
		}
		else {
			object->setPosition(glm::vec3(cos(angle), object->getPosition().y, object->getPosition().z));
		}
		object->update();
		object->draw();
	}
	else if (operation == 2) {
		object->setAngle(angle);

		if (direction == 0) {
			object->setAxis(glm::vec3(0.0, 1.0, 0.0));
		}
		else if (direction == 1) {
			object->setAxis(glm::vec3(0.0, 0.0, 1.0));
		}
		else {
			object->setAxis(glm::vec3(1.0, 0.0, 0.0));
		}

		object->update();
		object->draw();
	}
	else if (operation == 3) {
		object->setScale(glm::vec3(abs(cos(angle)), abs(cos(angle)), abs(cos(angle))));
		object->update();
		object->draw();
	}
}






void SceneManager::updateCamera() {
	glm::mat4 model = glm::mat4(1);
	shader->setMat4("model", glm::value_ptr(model));
	camera->updateView();
	glm::mat4 view = camera->getView();
	shader->setMat4("view", glm::value_ptr(view));
	shader->setVec3("cameraPos", camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
}

void SceneManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_SPACE) {
		camera->moveUp();
	}
	if (key == GLFW_KEY_LEFT_CONTROL) {
		camera->moveDown();
	}
	if (key == GLFW_KEY_W) {
		camera->moveFoward();
	}
	if (key == GLFW_KEY_S) {
		camera->moveBack();
	}
	if (key == GLFW_KEY_A) {
		camera->moveLeft();
	}
	if (key == GLFW_KEY_D) {
		camera->moveRight();
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		selection++;
		if (selection >= 3)
			selection = 0;
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		operation++;
		if (operation >= 4)
			operation = 0;
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		direction++;
		if (direction >= 3)
			direction = 0;
	}
}

void SceneManager::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	camera->moveMouse(xpos, ypos);
}

void SceneManager::mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset > 0) {
		camera->moveFoward();
	}
	else {
		camera->moveBack();
	}
}

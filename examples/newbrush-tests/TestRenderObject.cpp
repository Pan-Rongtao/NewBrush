#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/gles/Program.h"
#include "glm/gtc/matrix_transform.hpp"
#include "catch2/catch.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "newbrush/gles/Shader.h"
#include "GLFW/glfw3.h"
#include <GLES2/gl2.h>

using namespace nb;

TEST_CASE("test RenderObject", "[RenderObject]") {

	const GLuint WIDTH = 1280, HEIGHT = 720;
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, WIDTH, HEIGHT);

	auto renderObj = std::make_shared<RenderObject>();
	renderObj->loadFromFile("D:/share/myProject/modelLoading/resources/objects/models/car.fbx");
	renderObj->setProgram(Programs::model());
	while (!glfwWindowShouldClose(window)) {
		//GLfloat currentFrame = glfwGetTime();

		glfwPollEvents();//����¼�
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//״̬���ú���
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//״̬Ӧ�ú���

		Camera camera;
		Projection projection;
		renderObj->draw(camera, projection);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (GLfloat)glfwGetTime()*0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		renderObj->storeUniform("nbM", model);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
}
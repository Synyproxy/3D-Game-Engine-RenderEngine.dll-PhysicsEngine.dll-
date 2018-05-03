#include "stdafx.h"

#include "Window.h"

using namespace RenderEngineNS;

Window::Window(const GLint& p_width, const GLint& p_height)
	: m_width{p_width}, m_height(p_height)
{
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
}

bool Window::Setup()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_window = glfwCreateWindow(m_width, m_height, "OpenGL Architecture", nullptr, nullptr);

	int screenWidth, screenHeight;

	if (m_window == nullptr)
	{
		glfwTerminate();

		return false;
	}

	glfwGetFramebufferSize(m_window, &screenWidth, &screenHeight);

	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
		return false;

	std::cout << "Window Created" << std::endl;

	glViewport(0, 0, screenWidth, screenHeight);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//Disable mouse cursor

	return true;
}

GLFWwindow* Window::WindowGLFW()
{
	return m_window;
}

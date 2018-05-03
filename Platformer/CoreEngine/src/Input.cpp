#include "stdafx.h"

#include <Input.h>

using namespace CoreEngineNS;

GLfloat Input::m_windowWidth = 0;
GLfloat Input::m_windowHeight = 0;
bool Input::m_shouldClose = false;

bool Input::m_updateMouse = false;
bool Input::m_firstMouse = true;
GLfloat Input::m_lastX = 0;
GLfloat Input::m_lastY = 0;
GLfloat Input::m_xOffset = 0;
GLfloat Input::m_yOffset = 0;

glm::vec2 Input::m_movementDirection = glm::vec2(0, 0);
glm::vec2 Input::m_vertical = glm::vec2(0, 0);
glm::vec2 Input::m_horizontal = glm::vec2(0, 0);

CoreEngineNS::Input::Input()
{
}

CoreEngineNS::Input::~Input()
{
}

void Input::KeyCallBack(GLFWwindow* p_window, int p_key, int p_scanCode, int p_action, int p_mods)
{
	

	if (p_action == GLFW_PRESS)
	{
		if (p_key == GLFW_KEY_ESCAPE)
			m_shouldClose = true;	

		if (p_key == GLFW_KEY_W)
			m_vertical.y = -1;
			

		if (p_key == GLFW_KEY_S)
			m_vertical.y = 1;

		if (p_key == GLFW_KEY_A)
			m_horizontal.x = -1;

		if (p_key == GLFW_KEY_D)
			m_horizontal.x = 1;
	}

	if (p_action == GLFW_RELEASE)
	{
		if (p_key == GLFW_KEY_W)
			m_vertical.y = 0;

		if (p_key == GLFW_KEY_S)
			m_vertical.y = 0;

		if (p_key == GLFW_KEY_A)
			m_horizontal.x =0;

		if (p_key == GLFW_KEY_D)
			m_horizontal.x = 0;
	}

	m_movementDirection = m_vertical + m_horizontal;
}

glm::vec2 Input::GetMovementDirection()
{
	return glm::normalize(m_movementDirection);
}

void Input::Reset()
{
	m_updateMouse = false;
}

bool Input::ShouldClose()
{
	return m_shouldClose;
}

void Input::MouseCallBack(GLFWwindow* p_window, double p_xPos, double p_yPos)
{
	m_updateMouse = true;

	if (m_firstMouse)
	{
		m_lastX = p_xPos;
		m_lastY = p_yPos;
		m_firstMouse = false;
	}

	m_xOffset = p_xPos - m_lastX;
	m_yOffset = m_lastY - p_yPos; //Y coordinates are inversed

	m_lastX = p_xPos;
	m_lastY = p_yPos;
}

bool Input::ShouldUpdateMouse()
{
	return m_updateMouse;
}

float Input::GetXOffset()
{
	return (float)m_xOffset;
}

float Input::GetYOffset()
{
	return (float)m_yOffset;
}

float Input::MouseX()
{
	return (float)m_lastX;
}

float Input::MouseY()
{
	return (float)m_lastY;
}

void Input::SetWindowSize(const GLfloat& p_windowWidth, const GLfloat& p_windowHeight)
{
	m_windowWidth = p_windowWidth;
	m_windowHeight = p_windowHeight;

	m_lastX = m_windowWidth / 2;
	m_lastY = m_windowHeight / 2;
}
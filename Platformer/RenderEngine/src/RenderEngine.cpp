// RenderEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <RenderEngine.h>

using namespace RenderEngineNS;


RenderEngine::RenderEngine() : m_isRunning {true}
{
	std::cout << "RenderEngine On" << std::endl;
	m_window = nullptr;
}

RenderEngine::~RenderEngine()
{
	std::cout << "RenderEngine Off" << std::endl;
}

void RenderEngine::SetupWindow(const int& p_width, const int& p_height)
{
	m_width = p_width;
	m_height = p_height;
	m_window = std::make_shared<Window>(m_width, m_height);
	m_window->Setup();
}

void RenderEngine::Update()
{
	glfwPollEvents();

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	glfwSwapBuffers(m_window->WindowGLFW());
}

bool RenderEngine::IsRunning()
{
	return m_isRunning;
}

std::shared_ptr<Window> RenderEngine::GetWindow()
{
	return m_window;
}

int RenderEngine::WindowWidth() const
{
	return m_width;
}

int RenderEngine::WindowHeight() const
{
	return m_height;
}



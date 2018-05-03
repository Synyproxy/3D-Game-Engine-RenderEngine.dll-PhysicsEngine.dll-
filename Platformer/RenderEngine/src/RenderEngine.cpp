// RenderEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "RenderEngine.h"

using namespace RenderEngineNS;


RenderEngine::RenderEngine()
{
	std::cout << "RenderEngine On" << std::endl;
	m_window = nullptr;
}

RenderEngine::~RenderEngine()
{
	std::cout << "RenderEngine Off" << std::endl;
	if (m_window != nullptr)
		delete(m_window);
}

void RenderEngine::SetupWindow(const int& p_width, const int& p_height)
{
	m_window = new Window(p_width, p_height);
	m_window->Setup();
}

void RenderEngine::Update()
{
	while(!glfwWindowShouldClose(m_window->WindowGLFW()))
	{
		glfwPollEvents();

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(m_window->WindowGLFW());
	}
}

// RenderEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <RenderEngine.h>

using namespace RenderEngineNS;

RenderEngine::RenderEngine()
{
	std::cout << "RenderEngine On" << std::endl;
	m_window = nullptr;
}

RenderEngine::~RenderEngine()
{
	std::cout << "RenderEngine Off" << std::endl;
	delete m_camera;
}

void RenderEngine::SetupWindow(const int& p_width, const int& p_height)
{
	m_width = p_width;
	m_height = p_height;
	m_window = std::make_shared<Window>(m_width, m_height);
	m_window->Setup();

	m_camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f));
}

void RenderEngine::Render(Model* p_model, Shader* p_shader, const glm::vec3& p_position) const
{
	p_shader->Bind();
	const glm::mat4 projection = glm::perspective(glm::radians(m_camera->GetZoom()), static_cast<float>(m_width) / static_cast<float>(m_height), 0.1f, 100.0f);
	const glm::mat4 view = m_camera->GetViewMatrix();;
	p_shader->SetUniformMat4f("projection", projection);
	p_shader->SetUniformMat4f("view", view);

	//TODO this should be in the Transform
	// render the loaded model
	glm::mat4 model;
	model = glm::translate(model, p_position);
																  //model = glm::rotate()
	model = glm::rotate(model, 0.0f, glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	
	p_shader->SetUniformMat4f("model", model);
	p_model->Draw(*p_shader);
}

Model* RenderEngine::LoadModel(const std::string& p_filePath)
{
	return new Model(p_filePath);
}

Shader* RenderEngine::LoadShader(const std::string & p_vertexShader, const std::string & p_fragmentShader)
{
	return new Shader(p_vertexShader, p_fragmentShader);
}

void RenderEngine::BeginFrame()
{
	glfwPollEvents();

	//glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClearColor(0.160784f, 0.309803f, 0.478431f, 1.0f);	//Unity's Color for the lol's
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderEngine::EndFrame()
{
	glfwSwapBuffers(m_window->WindowGLFW());
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



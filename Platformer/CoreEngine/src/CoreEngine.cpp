// CoreEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <CoreEngine.h>

using namespace CoreEngineNS;

CoreEngine::CoreEngine() : m_renderEngine(nullptr), m_isRunning{ true }
{
	std::cout << "CoreEngine On" << std::endl;
}

CoreEngine::~CoreEngine()
{
	std::cout << "CoreEngine Off" << std::endl;
}

void CoreEngine::Setup()
{
	BindInput();
	//GameObject& empty(m_scene.AddEntity());

	//Transform& transform = empty.GetComponent<Transform>();

	//transform.SetPosition(glm::vec3(-1, 5, 5));

	//std::cout << "Scene Objects Count " << m_scene.Count() << std::endl;
	m_model = m_renderEngine->LoadModel("res/meshes/nanosuit/nanosuit.obj");
	m_shader = m_renderEngine->LoadShader("res/shaders/NanoSuit/NanoSuit.vert", "res/shaders/NanoSuit/NanoSuit.frag");
	
}



void CoreEngine::IgniteRenderEngine(const int& p_width, const int& p_height)
{
	m_renderEngine = std::make_unique<RenderEngine>();

	m_renderEngine->SetupWindow(p_width, p_height);

	Setup();
}

void CoreEngine::Update()
{
	auto list = m_scene.Hierarchy();
	
	for (auto& gameObject : list)
	{
		//std::cout << "X:" << gameObject->GetComponent<Transform>().GetPosition().x << " Y :" << gameObject->GetComponent<Transform>().GetPosition().y << std::endl;
	}


	while (m_isRunning)
	{
		//std::cout << Input::MouseX() << " " << Input::MouseY() << std::endl;

		if (m_renderEngine->IsRunning())
		{
			m_renderEngine->BeginFrame();
			InputHandle();
			m_renderEngine->Render(m_model, m_shader);
			m_renderEngine->EndFrame();
		}	
	}	
}

void CoreEngine::BindInput()
{
	Input::SetWindowSize(m_renderEngine->WindowWidth(), m_renderEngine->WindowHeight());
	glfwSetKeyCallback(m_renderEngine->GetWindow()->WindowGLFW(), Input::KeyCallBack);
	glfwSetCursorPosCallback(m_renderEngine->GetWindow()->WindowGLFW(), Input::MouseCallBack);
}

void CoreEngine::InputHandle()
{
	if (Input::ShouldClose())
	{
		glfwSetWindowShouldClose(m_renderEngine->GetWindow()->WindowGLFW(), GL_TRUE);
		m_isRunning = false;
	}	
}

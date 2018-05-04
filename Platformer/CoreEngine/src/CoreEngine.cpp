// CoreEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <CoreEngine.h>
#include <MeshRenderer.h>

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
	GameObject& empty(m_scene.AddEntity());

	//Transform& transform = empty.GetComponent<Transform>();

	//transform.SetPosition(glm::vec3(-1, 5, 5));

	//std::cout << "Scene Objects Count " << m_scene.Count() << std::endl;

	//Loading Resources
	m_resManager.LoadModel("Nano", "nanosuit/nanosuit.obj");
	m_resManager.LoadShader("Nano", "NanoSuit/NanoSuit.vert", "NanoSuit/NanoSuit.frag");

	//Getting Resources
	m_shader = m_resManager.GetShader("Nano");

	MeshRenderer& meshRenderer  = empty.AddComponent<MeshRenderer>();
	meshRenderer.SetMesh(m_resManager.GetModel("Nano"));
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
	
	
	while (m_isRunning)
	{
		//std::cout << Input::MouseX() << " " << Input::MouseY() << std::endl;

		if (m_renderEngine->IsRunning())
		{
			m_renderEngine->BeginFrame();
			InputHandle();

			//m_renderEngine->Render(m_model, m_shader, glm::vec3(-10, -2, -10));

			for (auto& gameObject : list)
			{
				if (Input::GetMovementDirection().x > 0)
					gameObject->GetComponent<Transform>().SetPosition(glm::vec3(gameObject->GetComponent<Transform>().GetPosition().x + 0.2f, gameObject->GetComponent<Transform>().GetPosition().y, 0));

				if (Input::GetMovementDirection().x < 0)
					gameObject->GetComponent<Transform>().SetPosition(glm::vec3(gameObject->GetComponent<Transform>().GetPosition().x - 0.2f, gameObject->GetComponent<Transform>().GetPosition().y, 0));

				if (Input::GetMovementDirection().y < 0)
					gameObject->GetComponent<Transform>().SetPosition(glm::vec3(gameObject->GetComponent<Transform>().GetPosition().x, gameObject->GetComponent<Transform>().GetPosition().y + 0.2f, 0));

				if (Input::GetMovementDirection().y > 0)
					gameObject->GetComponent<Transform>().SetPosition(glm::vec3(gameObject->GetComponent<Transform>().GetPosition().x, gameObject->GetComponent<Transform>().GetPosition().y - 0.2f, 0));

				m_renderEngine->Render(gameObject->GetComponent<MeshRenderer>().GetMesh(), m_shader, gameObject->GetComponent<Transform>().GetPosition());
			}
			
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

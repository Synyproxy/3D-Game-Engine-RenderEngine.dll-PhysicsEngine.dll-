// CoreEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <CoreEngine.h>
#include <MeshRenderer.h>
#include <ShaderCore.h>
#include <Player.h>

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

	//Loading Resources
	m_resManager.LoadModel("Nano", "nanosuit/nanosuit.obj");
	m_resManager.LoadShader("Nano", "NanoSuit/NanoSuit.vert", "NanoSuit/NanoSuit.frag");

	
	//GameObject& empty(m_scene.AddEntity());
	GameObject& player= m_scene.AddGameObject<Player>();
	//Player* player = m_scene.AddPlayer();


	MeshRenderer& meshRenderer = player.AddComponent<MeshRenderer>();
	meshRenderer.SetMesh(m_resManager.GetModel("Nano"));

	ShaderCore& shader = player.AddComponent<ShaderCore>();
	shader.SetShader(m_resManager.GetShader("Nano"));

	////Mesh + Material
	//MeshRenderer& meshRenderer  = empty.AddComponent<MeshRenderer>();
	//meshRenderer.SetMesh(m_resManager.GetModel("Nano"));

	////Shader
	//ShaderCore& shader = empty.AddComponent<ShaderCore>();
	//shader.SetShader(m_resManager.GetShader("Nano"));

	m_sceneHierarchy = m_scene.Hierarchy();

	std::cout << "Scene Count " << m_sceneHierarchy.size() << std::endl;

	for (auto& gameObject : m_sceneHierarchy)
	{
		gameObject->Awake();
	}

}

void CoreEngine::IgniteRenderEngine(const int& p_width, const int& p_height)
{
	m_renderEngine = std::make_unique<RenderEngine>();

	m_renderEngine->SetupWindow(p_width, p_height);

	Setup();
}

void CoreEngine::Update()
{
	
	//TODO
	//Components Dont need to have update draw
	
	while (m_isRunning)
	{
		//std::cout << Input::MouseX() << " " << Input::MouseY() << std::endl;

		if (m_renderEngine->IsRunning())
		{
			m_renderEngine->BeginFrame();
			InputHandle();


			for (auto& gameObject : m_sceneHierarchy)
			{
				gameObject->Update();
				m_renderEngine->Render(gameObject->GetComponent<MeshRenderer>().GetMesh(), gameObject->GetComponent<ShaderCore>().GetShader(), gameObject->GetComponent<Transform>().GetPosition());
				
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

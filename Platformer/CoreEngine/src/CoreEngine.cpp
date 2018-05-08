// CoreEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <CoreEngine.h>
#include <MeshRenderer.h>
#include <ShaderCore.h>
#include <Player.h>


#include "vld.h"
using namespace CoreEngineNS;

CoreEngine::CoreEngine() : m_renderEngine(nullptr), m_isRunning{ true }
{
	std::cout << "CoreEngine On" << std::endl;
}

CoreEngine::~CoreEngine()
{
	std::cout << "CoreEngine Off" << std::endl;
}

void CoreEngine::LoadResources()
{
	//Load All Resources needed Flyweight
	ResourceManager::Instance().LoadModel("Nano", "nanosuit/nanosuit.obj");
	ResourceManager::Instance().LoadModel("Cube", "primitives/Cube.obj");
	ResourceManager::Instance().LoadShader("Nano", "NanoSuit/NanoSuit.vert", "NanoSuit/NanoSuit.frag");
}

void CoreEngine::Setup()
{
	//Bind Input
	BindInput();

	//Loading Resources
	LoadResources();

	//Create GameObjects
	//Player 1
	GameObject& player= m_scene.AddGameObject<Player>();

	MeshRenderer& meshRenderer = player.AddComponent<MeshRenderer>();
	meshRenderer.SetMesh(ResourceManager::Instance().GetModel("Cube"));

	ShaderCore& shader = player.AddComponent<ShaderCore>();
	shader.SetShader(ResourceManager::Instance().GetShader("Nano"));

	//Player2
	GameObject& player2 = m_scene.AddGameObject<Player>();
	MeshRenderer& meshRenderer2 = player2.AddComponent<MeshRenderer>();
	meshRenderer2.SetMesh(ResourceManager::Instance().GetModel("Cube"));

	ShaderCore& shader2 = player2.AddComponent<ShaderCore>();
	shader2.SetShader(ResourceManager::Instance().GetShader("Nano"));


	m_sceneHierarchy = m_scene.Hierarchy();

	std::cout << "Scene Count " << m_sceneHierarchy.size() << std::endl;

	for (auto& gameObject : m_sceneHierarchy)
	{
		gameObject->Awake();
	}

	player.GetComponent<Transform>().SetPosition(glm::vec3(0, 0, 0));
	player2.GetComponent<Transform>().SetPosition(glm::vec3(0, 0, 1));

	//m_renderEngine->m_camera->SetYaw(0);
}

void CoreEngine::IgniteRenderEngine(const int& p_width, const int& p_height)
{
	m_renderEngine = std::make_unique<RenderEngine>();

	m_renderEngine->SetupWindow(p_width, p_height);

	Setup();
}

void CoreEngine::Update()
{
	while (m_isRunning)
	{
		//std::cout << Input::MouseX() << " " << Input::MouseY() << std::endl;

		m_renderEngine->BeginFrame();
		InputHandle();

		//if (Input::ShouldUpdateMouse())
			//m_renderEngine->m_camera->ProcessMouseMovement(Input::GetXOffset(), Input::GetYOffset());
		
		for (auto& gameObject : m_sceneHierarchy)
		{
			gameObject->Update();
			m_renderEngine->Render(gameObject->GetComponent<MeshRenderer>().GetMesh(), gameObject->GetComponent<ShaderCore>().GetShader(), gameObject->GetComponent<Transform>().GetPosition());
		}
		
		m_renderEngine->EndFrame();
		Input::Reset();
	}

	FreeResources();
}

void CoreEngine::FreeResources()
{
	ResourceManager::Instance().FreeResources();
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

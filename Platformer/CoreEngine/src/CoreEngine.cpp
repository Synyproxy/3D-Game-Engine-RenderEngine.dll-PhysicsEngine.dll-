// CoreEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <CoreEngine.h>
#include <MeshRenderer.h>
#include <ShaderCore.h>
#include <Player.h>
#include <Collider.h>

using namespace CoreEngineNS;
using namespace PhysicsEngineNS;

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
	GameObject& player1= m_scene.AddGameObject<Player>();
	MeshRenderer& meshRenderer = player1.AddComponent<MeshRenderer>();
	meshRenderer.SetMesh(ResourceManager::Instance().GetModel("Cube"));
	Collider& sphereCollider = player1.AddComponent<Collider>();
	ShaderCore& shader = player1.AddComponent<ShaderCore>();
	shader.SetShader(ResourceManager::Instance().GetShader("Nano"));

	//Cube
	GameObject& dummy(m_scene.AddEntity());
	MeshRenderer& dummyRenderer = dummy.AddComponent<MeshRenderer>();
	dummyRenderer.SetMesh(ResourceManager::Instance().GetModel("Cube"));
	ShaderCore& dummyShader = dummy.AddComponent<ShaderCore>();
	dummyShader.SetShader(ResourceManager::Instance().GetShader("Nano"));
	Collider& dummyCollider = dummy.AddComponent<Collider>();



	m_sceneHierarchy = m_scene.Hierarchy();

	std::cout << "Scene Count " << m_sceneHierarchy.size() << std::endl;

	for (auto& gameObject : m_sceneHierarchy)
	{
		gameObject->Awake();
	}

	player1.GetComponent<Transform>().SetPosition(glm::vec3(0, 0, 0));
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

		auto& player = m_sceneHierarchy[0];
		auto& cube = m_sceneHierarchy[1];

		//std::cout << player->GetComponent<Transform>().GetPosition().y << std::endl;

		m_renderEngine->BeginFrame();
		InputHandle();

		if (Input::ShouldUpdateMouse())
			m_renderEngine->m_camera->ProcessMouseMovement(Input::GetXOffset(), Input::GetYOffset());
		
		for (auto& gameObject : m_sceneHierarchy)
		{
			gameObject->Update();
			m_renderEngine->Render(gameObject->GetComponent<MeshRenderer>().GetMesh(), gameObject->GetComponent<ShaderCore>().GetShader(), gameObject->GetComponent<Transform>().GetPosition());
		}
		
		if (pEngine.Intersect(player->GetComponent<Collider>().GetCollider(), cube->GetComponent<Collider>().GetCollider()))
			std::cout << "BOOOM" << std::endl;
		else
			std::cout << "NOT BOOOM" << std::endl;

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

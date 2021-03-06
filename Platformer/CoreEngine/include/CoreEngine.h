#pragma once

#include "CoreEngineAPI.h"
#include <RenderEngine.h>
#include <Input.h>
#include <GameObject.h>
#include <Transform.h>
#include <Scene.h>
#include <ResourceManager.h>	//Singleto
#include <PhysicsEngine.h>

using namespace RenderEngineNS;
using namespace PhysicsEngineNS;

namespace CoreEngineNS
{
	class COREENGINE_API CoreEngine
	{
	private:
		std::unique_ptr<RenderEngine> m_renderEngine;
		Scene m_scene;
		std::vector<std::shared_ptr<GameObject>> m_sceneHierarchy;
		bool m_isRunning;
		PhysicsEngine pEngine;

	public:
		CoreEngine();
		~CoreEngine();

		void Setup();
		void IgniteRenderEngine(const int& p_width, const int& p_height);
		void Update();

		void LoadResources();
		void FreeResources();

		void BindInput();
		void InputHandle();
	};
}
#pragma once

#include "CoreEngineAPI.h"
#include <RenderEngine.h>
#include <Input.h>
#include <GameObject.h>
#include <Transform.h>
#include <Scene.h>
#include <ResourceManager.h>

using namespace RenderEngineNS;

namespace CoreEngineNS
{
	class COREENGINE_API CoreEngine
	{
	private:
		std::unique_ptr<RenderEngine> m_renderEngine;
		Scene m_scene;
		bool m_isRunning;
		Shader* m_shader;
		ResourceManager m_resManager;

	public:
		CoreEngine();
		~CoreEngine();
		void Setup();
		void IgniteRenderEngine(const int& p_width, const int& p_height);
		void Update();

		void BindInput();
		void InputHandle();
	};
}
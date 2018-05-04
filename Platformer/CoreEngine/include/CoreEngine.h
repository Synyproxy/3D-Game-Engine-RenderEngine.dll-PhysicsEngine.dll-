#pragma once

#include "CoreEngineAPI.h"
#include <RenderEngine.h>
#include <Input.h>
#include <GameObject.h>
#include <Transform.h>
#include <Scene.h>

using namespace RenderEngineNS;

namespace CoreEngineNS
{
	class COREENGINE_API CoreEngine
	{
	private:
		std::unique_ptr<RenderEngine> m_renderEngine;
		Scene m_scene;
		bool m_isRunning;
		Model* m_model;
		Shader* m_shader;

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
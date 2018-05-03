#pragma once

#include "CoreEngineAPI.h"
#include <RenderEngine.h>
#include <Input.h>
#include <GameObject.h>
#include <Transform.h>

using namespace RenderEngineNS;

namespace CoreEngineNS
{
	class COREENGINE_API CoreEngine
	{
	private:
		std::unique_ptr<RenderEngine> m_renderEngine;
		bool m_isRunning;

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
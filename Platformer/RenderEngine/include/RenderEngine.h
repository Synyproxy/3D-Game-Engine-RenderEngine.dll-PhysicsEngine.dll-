#pragma once

#include "RenderEngineAPI.h"
#include "Window.h"

namespace RenderEngineNS
{
	class RENDERENGINE_API RenderEngine
	{
	private:
		Window* m_window;

	public:
		RenderEngine();
		~RenderEngine();

		void SetupWindow(const int& p_width, const int& p_height);
		void Update();
	};
}
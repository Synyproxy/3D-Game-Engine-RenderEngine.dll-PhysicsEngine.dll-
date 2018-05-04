#pragma once

#include "RenderEngineAPI.h"
#include <Window.h>
#include "Model.h"
#include "Camera.h"

namespace RenderEngineNS
{
	class RENDERENGINE_API RenderEngine
	{
	private:
		std::shared_ptr<Window> m_window;
		bool m_isRunning;
		int m_width;
		int m_height;
		float m_time;

		Shader* m_shader;
		Model* m_model;
		Camera* m_camera;

	public:
		RenderEngine();
		~RenderEngine();

		void SetupWindow(const int& p_width, const int& p_height);
		void Update();
		void Render(Model* p_model, Shader* p_shader) const;
		void Clear() const;

		bool IsRunning();

		std::shared_ptr<Window> GetWindow();
		int WindowWidth() const;
		int WindowHeight() const;
	};
}

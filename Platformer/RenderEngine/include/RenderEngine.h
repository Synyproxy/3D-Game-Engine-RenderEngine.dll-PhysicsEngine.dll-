#pragma once

#include <RenderEngineAPI.h>
#include <Window.h>
#include <Model.h>
#include <Camera.h>

namespace RenderEngineNS
{
	class RENDERENGINE_API RenderEngine
	{
	private:
		std::shared_ptr<Window> m_window;
		int m_width;
		int m_height;
		float m_time;

		Camera* m_camera;

	public:
		RenderEngine();
		~RenderEngine();

		void SetupWindow(const int& p_width, const int& p_height);
		void Update();
		void Render(Model* p_model, Shader* p_shader, const glm::vec3& p_position) const;
		Model* LoadModel(const std::string& p_filePath);
		Shader* LoadShader(const std::string& p_vertexShader, const std::string& p_fragmentShader);

		void BeginFrame();
		void EndFrame();

		std::shared_ptr<Window> GetWindow();
		int WindowWidth() const;
		int WindowHeight() const;
	};
}

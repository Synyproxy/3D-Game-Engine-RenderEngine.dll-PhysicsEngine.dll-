#pragma once

#include <Component.h>
#include <Model.h>

using namespace RenderEngineNS;

namespace CoreEngineNS
{
	class MeshRenderer : public Component
	{
	private:
		Model* m_model;

	public:
		MeshRenderer();
		~MeshRenderer();

		void Awake() override;
		void Update() override;
		void Draw() override;

		void SetMesh(Model* p_model);
		Model* GetMesh();
	};
}
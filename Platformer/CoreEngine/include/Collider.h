#pragma once

#include <Component.h>
#include <Sphere.h>
#include <Primitive.h>

using namespace PhysicsEngineNS;

namespace CoreEngineNS
{
	class Collider : public Component
	{
	private:
		Primitive* m_sphere;

	public:
		Collider();
		~Collider();

		Primitive* GetCollider();

	public:
		void Update() override;

	};
}
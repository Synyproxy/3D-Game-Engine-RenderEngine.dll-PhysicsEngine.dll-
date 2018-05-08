#pragma once

#include <PhysicsEngineAPI.h>
#include <Primitive.h>

namespace PhysicsEngineNS
{
	class PHYSICSENGINE_API Sphere : public Primitive
	{
	private:
		float m_radius;

	public:
		Sphere(const glm::vec3 p_position = glm::vec3(0), const float& p_radious = 0.5f);
		~Sphere();

		float Radius();
	};
}
#pragma once

#include <PhysicsEngineAPI.h>

namespace PhysicsEngineNS
{

	enum PHYSICSENGINE_API EPrimitiveType
	{
		UNKNOWN_TYPE,
		SPHERE_TYPE,
	};

	class PHYSICSENGINE_API Primitive
	{
	protected :
		glm::vec3 m_position;
		EPrimitiveType m_type;

	public :
		Primitive();
		~Primitive();

		glm::vec3& Position();
		const EPrimitiveType Type();
	};
}
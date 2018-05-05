#pragma once

#include "stdafx.h"

#include <Component.h>

namespace CoreEngineNS
{
	class Transform : public Component
	{
	private:
		glm::vec3 m_position;
		glm::vec3 m_scale;

	public:
		Transform();
		~Transform();

		const glm::vec3& GetPosition() const;
		const glm::vec3& GetScale() const;

		void SetPosition(const glm::vec3& p_position);
		void SetScale(const glm::vec3& p_scale);
	};

}
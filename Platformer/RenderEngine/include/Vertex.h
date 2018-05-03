#pragma once

#include "stdafx.h"

namespace RenderEngineNS
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
}
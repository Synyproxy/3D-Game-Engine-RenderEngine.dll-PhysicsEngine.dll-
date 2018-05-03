#pragma once

#include "stdafx.h"

namespace RenderEngineNS
{
	struct Texture
	{
		GLuint m_id;
		std::string m_type;
		aiString m_path;
	};
}

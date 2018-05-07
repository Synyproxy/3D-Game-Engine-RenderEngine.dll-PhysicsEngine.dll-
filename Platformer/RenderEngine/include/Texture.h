#pragma once

#include "stdafx.h"

namespace RenderEngineNS
{
	struct Texture
	{
		unsigned int m_id;
		std::string m_type;
		aiString m_path;

		Texture(const unsigned p_id, const std::string& p_type, const aiString& p_path)
			: m_id(p_id),
			m_type(p_type),
			m_path(p_path) {}
	};

	unsigned int TextureFromFile(const char* p_path, const std::string& p_directory, bool p_gamma = false);
}

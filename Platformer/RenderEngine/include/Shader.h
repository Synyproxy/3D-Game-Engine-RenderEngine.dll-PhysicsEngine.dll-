#pragma once

#include "stdafx.h"

namespace RenderEngineNS
{
	class Shader
	{
	private:
		GLuint m_program;

	public:

		Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
		~Shader() = default;

		GLuint GetProgram() const;
	};
}
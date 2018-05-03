#pragma once

#include "stdafx.h"
#include <Vertex.h>
#include <Texture.h>
#include <Shader.h>

namespace RenderEngineNS
{
	class Mesh
	{
	public:

		std::vector<Vertex> m_vertices;
		std::vector<GLuint> m_indices;
		std::vector<Texture> m_textures;

		Mesh(std::vector<Vertex> p_vertices, std::vector<GLuint> p_indices, std::vector<Texture> p_textures);
		~Mesh();

		void Draw(Shader* p_shader);//Needs Shader

	private:

		GLuint VBO;
		GLuint VAO;
		GLuint EBO;

		void Setup();
	};
}
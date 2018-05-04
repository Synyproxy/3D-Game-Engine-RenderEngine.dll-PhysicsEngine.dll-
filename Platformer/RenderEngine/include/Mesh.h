#pragma once

#include "stdafx.h"
#include <Vertex.h>
#include <Texture.h>
#include <Shader.h>

namespace RenderEngineNS
{
	class Mesh
	{
	private:
		// OPENGL BUFFERS
		unsigned int m_vao, m_vbo, m_ebo;

		// MESH DATA
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<Texture> m_textures;

	public:
		Mesh() = default;
		explicit Mesh(const std::vector<Vertex>& p_vertices, const std::vector<unsigned int>& p_indices, const std::vector<Texture>& p_textures);
		~Mesh() = default;

		void Setup();
		void Draw(Shader& p_shader);

		void Bind() const;
		void Unbind() const;
	};
}
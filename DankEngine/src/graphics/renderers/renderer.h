#pragma once

#include "core/nativeapp.h"

#include "graphics/buffers/indexbuffer.h"
#include "graphics/buffers/vertexbuffer.h"

#include "graphics/shader.h"

#include "maths/vec2.h"
#include "maths/vec3.h"

namespace dank {

	struct Vertex {
		vec3 position;
		vec2 texCoord;
		unsigned int color;
		float tid;
		float text;
	};

	class Renderer {
	protected:
		Vertex* buffer;

		VertexBuffer* vbo;
		IndexBuffer* ibo;

		//textures

		Shader* shader;

		unsigned short numSprites;


		virtual void InitShader() = 0;

	public:
		Renderer(unsigned int num_sprites);
		~Renderer();

		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void Present() = 0;

	};
}
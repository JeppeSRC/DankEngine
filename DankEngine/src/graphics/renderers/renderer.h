#pragma once

#include "core/nativeapp.h"

#include "graphics/buffers/indexbuffer.h"
#include "graphics/buffers/vertexbuffer.h"

#include "graphics/shaders/shader.h"

#include "maths/vec2.h"
#include "maths/vec3.h"

namespace dank {

	struct Vertex {
		vec3 position;
		vec2 texCoord;
		unsigned int color;
	};

	class Renderer {
	protected:
		unsigned int numSprites;
		unsigned short count;

		Vertex* buffer;

		VertexBuffer* vbo;
		IndexBuffer* ibo;

		//textures

		Shader* shader;

		virtual void InitShader() {
			//blyat
		}

	public:
		Renderer(unsigned int num_sprites);
		~Renderer();

		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void Present() = 0;

		void Submit(const vec3& position, const vec2& size, unsigned int color);

	};
}
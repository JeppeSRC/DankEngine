#pragma once

#include "core/nativeapp.h"

#include "graphics/buffers/indexbuffer.h"
#include "graphics/buffers/vertexbuffer.h"
#include "graphics/buffers/vertexarray.h"

#include "graphics/shaders/shader.h"

#include "maths/vec2.h"
#include "maths/vec3.h"

namespace dank {

	struct Vertex {
		vec3 position;
		vec2 texCoord;
		unsigned int color;
	};

	enum RendererType {
		RENDERER_GLES2,
		RENDERER_GLES3
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

		static const char *vertex2, *fragment2, *vertex3, *fragment3;
	public:
		Renderer(unsigned int num_sprites, RendererType type);
		virtual ~Renderer();

		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void Present() = 0;

		void Submit(const vec3& position, const vec2& size, unsigned int color);

	};

	class Renderer2 : public Renderer {
	private:
		Vertex* rawbuffer;

		static const char* vertex;
		static const char* fragment;

		int posLocation, uvLocation, colorLocation;

	public:
		Renderer2(unsigned int num_sprites);
		~Renderer2();

		void Begin() override;
		void End() override;
		void Present() override;

	};

	class Renderer3 : public Renderer {
	private:
		VertexArray* vao;

	public:
		Renderer3(unsigned int num_sprites);
		~Renderer3();

		void Begin() override;
		void End() override;
		void Present() override;
	};
}
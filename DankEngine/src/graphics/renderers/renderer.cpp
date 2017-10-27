#include "renderer.h"

#define MAX_TEXTURES 0x10

namespace dank {

	Renderer::Renderer(unsigned int num_sprites) {
		numSprites = num_sprites;
		unsigned short offset = 0;
		unsigned short* indices = new unsigned short[numSprites * 6];

		for (unsigned int i = 0; i < numSprites; i++) {
			indices[i * 6 + 0] = offset + 0;
			indices[i * 6 + 1] = offset + 1;
			indices[i * 6 + 2] = offset + 2;
			indices[i * 6 + 3] = offset + 2;
			indices[i * 6 + 4] = offset + 3;
			indices[i * 6 + 5] = offset + 0;

			offset += 4;
		}

		vbo = new VertexBuffer(nullptr, numSprites * 4 * sizeof(Vertex));

		ibo = new IndexBuffer(indices, numSprites * 6);

		InitShader();

		shader->Bind();

		int ids[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

		shader->SetIntArray("samplers", MAX_TEXTURES, ids);
		//add matrix


	}


	Renderer::~Renderer() {
		delete vbo;
		delete ibo;
		delete shader;
	}

	void Renderer::Submit(const vec3& position, const vec2& size, unsigned int color) {
		buffer->position = position + vec2(size.x * -0.5f, size.y * -0.5f);
		buffer->texCoord = vec2(0, 0);
		buffer->color = color;
		buffer++;

		buffer->position = position + vec2(size.x *  0.5f, size.y * -0.5f);
		buffer->texCoord = vec2(0, 0);
		buffer->color = color;
		buffer++;

		buffer->position = position + vec2(size.x *  0.5f, size.y *  0.5f);
		buffer->texCoord = vec2(0, 0);
		buffer->color = color;
		buffer++;

		buffer->position = position + vec2(size.x * -0.5f, size.y *  0.5f);
		buffer->texCoord = vec2(0, 0);
		buffer->color = color;
		buffer++;

		count += 6;

	}

}
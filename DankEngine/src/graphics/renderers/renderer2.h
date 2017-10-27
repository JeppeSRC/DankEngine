#pragma once

#include "core/nativeapp.h"

#include "renderer.h"

namespace dank {

	class Renderer2 : public Renderer {
	private:
		Vertex* rawbuffer;

		const char* vertex =
			#include "graphics/shaders/renderer2.vs"
			;

		const char* fragment =
			#include "graphics/shaders/renderer2.fs"
			;

	protected:
		

	public:
		Renderer2(unsigned int num_sprites): Renderer(num_sprites) {
			rawbuffer = new Vertex[num_sprites * 4];

		}

		~Renderer2() {
			delete[] rawbuffer;
		}

		void Begin() override {
			count = 0;
			buffer = rawbuffer;
		}

		void End() override {
			vbo->SetData(rawbuffer, (count / 6) * 4 * sizeof(Vertex));
			buffer = nullptr;
		}

		void Present() override {
			shader->Bind();
			vbo->Bind();

			GL(glEnableVertexAttribArray(0));
			GL(glEnableVertexAttribArray(1));
			GL(glEnableVertexAttribArray(2));

			GL(glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, position)));
			GL(glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, texCoord)));
			GL(glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, color)));

			ibo->Bind();
			glDrawElements(GL_TRIANGLES, count, ibo->GetFormat(), nullptr);
		}

		void InitShader() override {
			shader = new Shader(vertex, fragment);
		}

	};

}

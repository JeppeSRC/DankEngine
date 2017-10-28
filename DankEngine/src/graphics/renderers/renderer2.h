#pragma once

#include "core/nativeapp.h"

#include "renderer.h"

namespace dank {

	class Renderer2 : public Renderer {
	private:
		Vertex* rawbuffer;

		static const char* vertex;
		static const char* fragment;

		int posLocation, uvLocation, colorLocation;

	protected:
		

	public:
		Renderer2(unsigned int num_sprites): Renderer(num_sprites, RENDERER_GLES2) {
			rawbuffer = new Vertex[num_sprites * 4];
			posLocation = shader->GetAttributeLocation("position");
			uvLocation = shader->GetAttributeLocation("texCoords");
			colorLocation = shader->GetAttributeLocation("colors");
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

			GL(glEnableVertexAttribArray(posLocation));
			GL(glEnableVertexAttribArray(uvLocation));
			GL(glEnableVertexAttribArray(colorLocation));

			GL(glVertexAttribPointer(posLocation, 3, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, position)));
			GL(glVertexAttribPointer(uvLocation, 2, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, texCoord)));
			GL(glVertexAttribPointer(colorLocation, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (const void*)MOFFSET(Vertex, color)));

			ibo->Bind();
			GL(glDrawElements(GL_TRIANGLES, count, ibo->GetFormat(), nullptr));
		}

	};
}

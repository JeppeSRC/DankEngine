#pragma once

#include "core/nativeapp.h"

#include "renderer.h"

namespace dank {

	class Renderer3 : public Renderer {
	private:
		VertexArray* vao;

	protected:


	public:
		Renderer3(unsigned int num_sprites) : Renderer(num_sprites, RENDERER_GLES3) {
			LOGD("I got here");
			vao = new VertexArray(sizeof(Vertex));

			vbo->Bind();
			vao->Bind();
			vao->AddAttribute(0, 3, GL_FLOAT, false, (unsigned int)MOFFSET(Vertex, position));
			vao->AddAttribute(1, 2, GL_FLOAT, false, (unsigned int)MOFFSET(Vertex, texCoord));
			vao->AddAttribute(2, 4, GL_UNSIGNED_BYTE, true, (unsigned int)MOFFSET(Vertex, color));
		}

		~Renderer3() {
			delete vao;
		}

		void Begin() override {
			count = 0;
			buffer = (Vertex*)vbo->Map(GL_MAP_WRITE_BIT);
		}

		void End() override {
			vbo->Unmap();
			buffer = nullptr;
		}

		void Present() override {
			shader->Bind();

			vao->Bind();
			vbo->Bind();
			ibo->Bind();
			glDrawElements(GL_TRIANGLES, count, ibo->GetFormat(), nullptr);
		}

	};
}

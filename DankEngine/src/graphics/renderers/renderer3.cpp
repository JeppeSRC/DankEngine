#include "renderer.h"

namespace dank {

Renderer3::Renderer3(unsigned int num_sprites) : Renderer(num_sprites, RendererType::RENDERER_GLES3) {
	vao = new VertexArray(sizeof(Vertex));

	vao->Bind();
	vbo->Bind();
	vao->AddAttribute(0, 3, GL_FLOAT, false, (unsigned int)MOFFSET(Vertex, position));
	vao->AddAttribute(1, 2, GL_FLOAT, false, (unsigned int)MOFFSET(Vertex, texCoord));
	vao->AddAttribute(2, 4, GL_UNSIGNED_BYTE, true, (unsigned int)MOFFSET(Vertex, color));
	vao->AddAttribute(3, 1, GL_FLOAT, false, (unsigned int)MOFFSET(Vertex, texID));
	vao->AddAttribute(4, 1, GL_FLOAT, false, (unsigned int)MOFFSET(Vertex, text));
}

Renderer3::~Renderer3() {
	delete vao;
}

void Renderer3::Begin() {
	count = 0;
	buffer = (Vertex*)vbo->Map(GL_MAP_WRITE_BIT);
}

void Renderer3::End() {
	vbo->Unmap();
	buffer = nullptr;
}

void Renderer3::Present() {
	shader->Bind();
	for (size_t i = 0; i < tids.GetSize(); i++) {
		tids[i]->Bind(i);
	}
	vao->Bind();
	vbo->Bind();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ibo->Bind();
	glDrawElements(GL_TRIANGLES, count, ibo->GetFormat(), nullptr);
	glDisable(GL_BLEND);
}

}
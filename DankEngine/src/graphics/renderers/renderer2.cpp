#include "renderer.h"

namespace dank {

Renderer2::Renderer2(unsigned int num_sprites) : Renderer(num_sprites, RENDERER_GLES2) {
	rawbuffer = new Vertex[num_sprites * 4];
	posLocation = shader->GetAttributeLocation("position");
	uvLocation = shader->GetAttributeLocation("texCoords");
	colorLocation = shader->GetAttributeLocation("colors");
	tidLocation = shader->GetAttributeLocation("textureID");
	textLocation = shader->GetAttributeLocation("tex");
}

Renderer2::~Renderer2() {
	delete[] rawbuffer;
}

void Renderer2::Begin()  {
	count = 0;
	buffer = rawbuffer;
}

void Renderer2::End()  {
	vbo->SetData(rawbuffer, (count / 6) * 4 * sizeof(Vertex));
	buffer = nullptr;
}

void Renderer2::Present()  {
	
	shader->Bind();
	for (size_t i = 0; i < tids.GetSize(); i++) {
		tids[i]->Bind(i);
	}
	vbo->Bind();

	GL(glEnableVertexAttribArray(posLocation));
	GL(glEnableVertexAttribArray(uvLocation));
	GL(glEnableVertexAttribArray(colorLocation));
	GL(glEnableVertexAttribArray(tidLocation));
	GL(glEnableVertexAttribArray(textLocation));

	GL(glVertexAttribPointer(posLocation, 3, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, position)));
	GL(glVertexAttribPointer(uvLocation, 2, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, texCoord)));
	GL(glVertexAttribPointer(colorLocation, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (const void*)MOFFSET(Vertex, color)));
	GL(glVertexAttribPointer(tidLocation, 1, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, texID)));
	GL(glVertexAttribPointer(textLocation, 1, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, text)));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ibo->Bind();
	GL(glDrawElements(GL_TRIANGLES, count, ibo->GetFormat(), nullptr));
	glDisable(GL_BLEND);
}

}
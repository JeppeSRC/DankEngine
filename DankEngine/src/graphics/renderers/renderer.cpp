#include "application.h"
#include "freetype-gl.h"
#include "renderer.h"

#define MAX_TEXTURES 0x10

namespace dank {

const char* Renderer::vertex2 = "#version 100\n"
		#include "graphics/shaders/renderer2.vs"
		;

const char* Renderer::fragment2 = "#version 100\n"
		#include "graphics/shaders/renderer2.fs"
		;

const char* Renderer::vertex3 = "#version 300 es\n"
		#include "graphics/shaders/renderer3.vs"
		;
const char* Renderer::fragment3 = "#version 300 es\n"
		#include "graphics/shaders/renderer3.fs"
		;

Renderer* Renderer::CreateRenderer(unsigned int num_sprites) {
	NativeApp* app = NativeApp::app;
	if (app->hasVaos) {
		return new Renderer3(num_sprites);
	}
	else {
		return new Renderer2(num_sprites);
	}

	return nullptr;
}

Renderer::Renderer(unsigned int num_sprites, RendererType type) {
	orthographicMatrix = mat4::Orthographic(0, Application::Get()->GetGameWidth(), 0, Application::Get()->GetGameHeight(), -1.0, 1.0);

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

	

	if (type == RendererType::RENDERER_GLES2) {
		ShaderFactory factory(vertex2, fragment2);
		
		factory.SetVariable("maxTextures", 16U, ShaderType::PIXEL);
		
		shader = factory.CreateShader();
	} else {
		ShaderFactory factory(vertex3, fragment3);

		factory.SetVariable("maxTextures", 16U, ShaderType::PIXEL);

		shader = factory.CreateShader();
	}

	shader->Bind();

	int ids[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

	shader->SetIntArray("samplers", MAX_TEXTURES, ids);
	shader->SetMat4("projection", orthographicMatrix.GetData());
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
	buffer->texID = -1;
	buffer->text = 0.f;
	buffer++;

	buffer->position = position + vec2(size.x *  0.5f, size.y * -0.5f);
	buffer->texCoord = vec2(1, 0);
	buffer->color = color;
	buffer->texID = -1;
	buffer->text = 0.f;
	buffer++;

	buffer->position = position + vec2(size.x *  0.5f, size.y *  0.5f);
	buffer->texCoord = vec2(1, 1);
	buffer->color = color;
	buffer->texID = -1;
	buffer->text = 0.f;
	buffer++;

	buffer->position = position + vec2(size.x * -0.5f, size.y *  0.5f);
	buffer->texCoord = vec2(0, 1);
	buffer->color = color;
	buffer->texID = -1;
	buffer->text = 0.f;
	buffer++;

	count += 6;

}

void Renderer::Submit(const vec3& position, const vec2& size, Texture2D* texture) {
	float tid = SubmitTexture(texture);
	buffer->position = position + vec2(size.x * -0.5f, size.y * -0.5f);
	buffer->texCoord = vec2(0, 0);
	buffer->color = 0xFFFFFFFF;
	buffer->texID = tid;
	buffer->text = 0.f;
	buffer++;

	buffer->position = position + vec2(size.x *  0.5f, size.y * -0.5f);
	buffer->texCoord = vec2(1, 0);
	buffer->color = 0xFFFFFFFF;
	buffer->texID = tid;
	buffer->text = 0.f;
	buffer++;

	buffer->position = position + vec2(size.x *  0.5f, size.y *  0.5f);
	buffer->texCoord = vec2(1, 1);
	buffer->color = 0xFFFFFFFF;
	buffer->texID = tid;
	buffer->text = 0.f;
	buffer++;

	buffer->position = position + vec2(size.x * -0.5f, size.y *  0.5f);
	buffer->texCoord = vec2(0, 1);
	buffer->color = 0xFFFFFFFF;
	buffer->texID = tid;
	buffer->text = 0.f;
	buffer++;

	count += 6;
}

void Renderer::Submit(const vec3& position, const vec2& size, Texture2D* texture, unsigned int color) {
	float tid = SubmitTexture(texture);
	buffer->position = position + vec2(size.x * -0.5f, size.y * -0.5f);
	buffer->texCoord = vec2(0, 0);
	buffer->color = color;
	buffer->texID = tid;
	buffer->text = 0.f;
	buffer++;

	buffer->position = position + vec2(size.x *  0.5f, size.y * -0.5f);
	buffer->texCoord = vec2(1, 0);
	buffer->color = color;
	buffer->texID = tid;
	buffer->text = 0.f;
	buffer++;

	buffer->position = position + vec2(size.x *  0.5f, size.y *  0.5f);
	buffer->texCoord = vec2(1, 1);
	buffer->color = color;
	buffer->texID = tid;
	buffer->text = 0.f;
	buffer++;

	buffer->position = position + vec2(size.x * -0.5f, size.y *  0.5f);
	buffer->texCoord = vec2(0, 1);
	buffer->color = color;
	buffer->texID = tid;
	buffer->text = 0.f;
	buffer++;

	count += 6;
}

float Renderer::SubmitTexture(const Texture* texture) {
	if (!texture) return -1.0f;

	size_t index = tids.Find(texture);

	if (index != (size_t)-1) {
		return (float)index + 0.5f;
	}
	else {
		index = tids.GetSize();
		if (index >= MAX_TEXTURES - 1) {
			End();
			Present();
			Begin();
			index = 0;
		}
		tids.Push_back(texture);
		return (float)index + 0.5;
	}
	return -0.0f;
}

void Renderer::Submit(const String& text, Font* font, const vec2& position, unsigned int color) {
	float tid = SubmitTexture(font->GetTexture());

	float xPos = position.x;
	float yPos = position.y;

	ftgl::texture_font_t* f = font->GetFont();

	color |= 0xFF000000;
	for (size_t i = 0; i < text.length; i++) {
		char c = text[i];

		if (c == ' ') {
			xPos += font->GetSize() * NativeApp::app->xUnitsPerPixel * 0.25f;
		}
		ftgl::texture_glyph_t* glyph = texture_font_get_glyph(f, c);

		float x = xPos + glyph->offset_x * NativeApp::app->xUnitsPerPixel;
		float y = yPos - glyph->offset_y * NativeApp::app->yUnitsPerPixel;

		if (i != 0) {
			float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
			x += kerning * NativeApp::app->xUnitsPerPixel;
		}

		float bitmapWidth = (float)glyph->width * NativeApp::app->xUnitsPerPixel;
		float bitmapHeight = (float)glyph->height * NativeApp::app->yUnitsPerPixel;

		float u0 = glyph->s0;
		float v0 = glyph->t0;
		float u1 = glyph->s1;
		float v1 = glyph->t1;

		buffer->position = vec3(x, y, 0.0);
		buffer->texCoord.x = u0;
		buffer->texCoord.y = v0;
		buffer->color = color;
		buffer->texID = tid;
		buffer->text = 1.0f;
		buffer++;

		buffer->position = vec3(x + bitmapWidth, y, 0.0);
		buffer->texCoord.x = u1;
		buffer->texCoord.y = v0;
		buffer->color = color;
		buffer->texID = tid;
		buffer->text = 1.0f;
		buffer++;

		buffer->position = vec3(x + bitmapWidth, y + bitmapHeight, 0.0);
		buffer->texCoord.x = u1;
		buffer->texCoord.y = v1;
		buffer->color = color;
		buffer->texID = tid;
		buffer->text = 1.0f;
		buffer++;

		buffer->position = vec3(x, y + bitmapHeight, 0.0);
		buffer->texCoord.x = u0;
		buffer->texCoord.y = v1;
		buffer->color = color;
		buffer->texID = tid;
		buffer->text = 1.0f;
		buffer++;

		count += 6;

		xPos += glyph->advance_x * NativeApp::app->xUnitsPerPixel;
	}
}

void Renderer::SubmitTopLeft(const vec3& position, const vec2& size, Texture2D* texture, unsigned int color) {
	float tid = SubmitTexture(texture);
	buffer->position = position;
	buffer->texCoord = vec2(0, 0);
	buffer->color = color;
	buffer->texID = tid;
	buffer->text = 0.f;
	buffer++;

	buffer->position = position + vec2(size.x, 0);
	buffer->texCoord = vec2(1, 0);
	buffer->color = color;
	buffer->texID = tid;
	buffer->text = 0.f;
	buffer++;

	buffer->position = position + vec2(size.x, size.y);
	buffer->texCoord = vec2(1, 1);
	buffer->color = color;
	buffer->texID = tid;
	buffer->text = 0.f;
	buffer++;

	buffer->position = position + vec2(0, size.y);
	buffer->texCoord = vec2(0, 1);
	buffer->color = color;
	buffer->texID = tid;
	buffer->text = 0.f;
	buffer++;

	count += 6;
}


}
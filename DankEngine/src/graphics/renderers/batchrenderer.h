#pragma once

#include "renderer.h"

namespace dank {

	class BatchRenderer {
	private:
		Renderer* renderer;

	public:
		inline BatchRenderer(unsigned int num_sprites) {
			NativeApp* app = NativeApp::app;
			if (app->hasVaos) {
				renderer = new Renderer3(num_sprites);
			}
			else {
				renderer = new Renderer2(num_sprites);
			}
		}

		inline ~BatchRenderer() {
			delete renderer;
		}

		inline void Begin() {
			renderer->Begin();
		}

		inline void Submit(const vec3& position, const vec2& size, unsigned int color) {
			renderer->Submit(position, size, color);
		}

		inline void Submit(const vec3& position, const vec2& size, Texture2D* texture) {
			renderer->Submit(position, size, texture);
		}

		inline void Submit(const String& text, Font* font, const vec2& position, unsigned int color) {
			renderer->Submit(text, font, position, color);
		}

		inline void End() {
			renderer->End();
		}

		inline void Present() {
			renderer->Present();
		}

	};

}
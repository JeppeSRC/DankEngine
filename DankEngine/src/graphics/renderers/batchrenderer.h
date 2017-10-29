#pragma once

#include "renderer.h"

namespace dank {

	class BatchRenderer {
	private:
		Renderer* renderer;

	public:
		BatchRenderer(unsigned int num_sprites) {
			NativeApp* app = NativeApp::app;
			if (app->hasVaos) {
				renderer = new Renderer3(num_sprites);
			}
			else {
				renderer = new Renderer2(num_sprites);
			}
		}

		~BatchRenderer() {
			delete renderer;
		}

		void Begin() {
			renderer->Begin();
		}

		void Submit(const vec3& position, const vec2& size, unsigned int color) {
			renderer->Submit(position, size, color);
		}

		void End() {
			renderer->End();
		}

		void Present() {
			renderer->Present();
		}

	};

}
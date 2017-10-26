#pragma once

#include "renderer.h"

namespace dank {

	class BatchRenderer{
	private:
		Renderer* renderer;

	public:
		BatchRenderer() {
			NativeApp* app = NativeApp::app;
			if (app->hasVaos) {
				//renderer = new Renderer3();
			}
			else {
				//renderer = new Renderer2();
			}
		}

		~BatchRenderer() {
			delete renderer;
		}

		void Render() {
			renderer->Render();
		}

		void Update() {
			renderer->Update();
		}

	}

}
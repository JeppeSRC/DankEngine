#include <application.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES/glplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>
#include <utils/log.h>

using namespace dank;

class MainApp : public Application {
private:
	float r = 0, g = 0 , b = 0;

	BatchRenderer* renderer;
	Texture2D* texture;
	bool vaoe;

	Font* font;

public:
	MainApp(ANativeActivity* activity) 
		: Application(activity, 1000, 500) {
		Application::Set(this);
	}

	void Init() override {
		height = width / ((float)NativeApp::app->surface_width / NativeApp::app->surface_height);
		renderer = new BatchRenderer(30);
		texture = new Texture2D("cube.png");
		FontManager::AddFont("consola.ttf", "Consola");
		font = FontManager::GetFont("Consola", 36);
	}

	void Render() override {
		renderer->Begin();
		renderer->Submit("abcdefghijklmnopqrstuvwxyz", font, vec2(250, 150), 0xFFFF00FF);
		renderer->Submit(vec3(250.0f, 270, 0.0f), vec2(200.f, 200.f), texture);
		renderer->Submit(vec3(100, 100, 0.0f), vec2(100, 100), 0xFFFF00FF);
		renderer->End();
		renderer->Present();
	}

	void End() override {
		delete renderer;
	}


	void Update() override {

	}
};

APP_START(MainApp);

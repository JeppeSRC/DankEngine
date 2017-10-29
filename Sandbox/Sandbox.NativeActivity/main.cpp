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

using namespace dank;

class MainApp : public Application {
private:
	float r = 0, g = 0 , b = 0;

	BatchRenderer* renderer;
	bool vaoe;
public:
	MainApp(ANativeActivity* activity) 
		: Application(activity) {
		Application::Set(this);
		
	}

	void Init() override {
		renderer = new BatchRenderer(30);
		glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
		glDisable(GL_BLEND);
	}

	void Render() override {
		renderer->Begin();
		renderer->Submit(vec3(0.3f, 0.9f, 0.0f), vec2(1.f, 1.f), 0x32fdfa);
		renderer->End();
	//	renderer->Present();
	}

	void End() override {
		delete renderer;
	}


	void Update() override {

	}
};

APP_START(MainApp);

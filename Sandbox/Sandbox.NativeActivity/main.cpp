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

	Shader* shader;

	VertexBuffer* vbo;
	IndexBuffer* ibo;
	const char* vert, *frag;
	mat4 modelMatrix;
public:
	MainApp(ANativeActivity* activity) 
		: Application(activity) {
		Application::Set(this);
	}

	~MainApp() {
		delete vbo, ibo, shader;
	}

	void Init() override {
		String vertex = FileUtils::ReadTextFile("shader.vert");
		vert = vertex.str;
		String fragment = FileUtils::ReadTextFile("shader.frag");
		frag = fragment.str;

		shader = new Shader(vert, frag);
		shader->Bind();

		float vertices[]{
			0, 1, 0,
			1, -1, 0,
			-1, -1, 0
		};

		unsigned short indices[]{ 0, 1, 2 };

		vbo = new VertexBuffer(vertices, sizeof(vertices));
		ibo = new IndexBuffer(indices, 3);

		unsigned int position = shader->GetAttributeLocation("position");

		vbo->Bind();
		ibo->Bind();
		GL(glEnableVertexAttribArray(position));
		GL(glVertexAttribPointer(position, 3, GL_FLOAT, false, 3 * sizeof(float), 0));
		glClearColor(0.3, 0.4, 0.7, 1.0);
	}

	void Render() override {
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
		LOGW("Shit: %.2f", MemoryAllocator::getAllocated());

	}


	void Update() override {

	}
};

static MainApp *app = nullptr;


static void OnConfigurationChanged(ANativeActivity* activity) { app->OnConfigurationChanged(activity); }

static void OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) { app->OnInputQueueCreated(activity, queue); }
static void OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) { app->OnInputQueueDestroyed(activity, queue); }

static void OnLowMemory(ANativeActivity* activity) { app->OnLowMemory(activity); }
static void OnWindowFocusChanged(ANativeActivity* activity, int focus) { app->OnWindowFocusChanged(activity, focus); }

static void OnPause(ANativeActivity* activity) { app->OnPause(activity); }
static void OnResume(ANativeActivity* activity) { app->OnResume(activity); }

static void OnStart(ANativeActivity* activity) { app->OnStart(activity); }
static void OnStop(ANativeActivity* activity) { app->OnStop(activity); }

static void OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) { app->OnNativeWindowCreated(activity, window); }
static void OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) { app->OnNativeWindowDestroyed(activity, window); }

static void OnDestroy(ANativeActivity* activity) { app->OnDestroy(activity); delete app; }

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
	app = new MainApp(activity);
	
	activity->callbacks->onConfigurationChanged = OnConfigurationChanged;
	activity->callbacks->onDestroy = OnDestroy;
	activity->callbacks->onInputQueueCreated = OnInputQueueCreated;
	activity->callbacks->onInputQueueDestroyed = OnInputQueueDestroyed;
	activity->callbacks->onLowMemory = OnLowMemory;
	activity->callbacks->onNativeWindowCreated = OnNativeWindowCreated;
	activity->callbacks->onNativeWindowDestroyed = OnNativeWindowDestroyed;
	activity->callbacks->onPause = OnPause;
	activity->callbacks->onResume = OnResume;
	activity->callbacks->onStart = OnStart;
	activity->callbacks->onStop = OnStop;
	activity->callbacks->onWindowFocusChanged = OnWindowFocusChanged;

	app->Start();
}
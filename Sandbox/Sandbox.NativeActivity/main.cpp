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
	float r = 0, g = 0, b = 0;

	BatchRenderer* renderer;
	UIManager* mainMenu;
	Texture2D* texture;
	bool vaoe;
	Font* font;
	AudioPlaylist *playlist;
	float x = 0, y = 0;
	UIItem* items[4];
public:

	MainApp(ANativeActivity* activity)
		: Application(activity, 1000, 500) {
		Application::Set(this);
	}

	void JoystickCallback(float x, float y) {

	}

	bool shit = true;
	void Init() override {
		height = width / ((float)NativeApp::app->surface_width / NativeApp::app->surface_height);
		NativeApp::app->yUnitsPerPixel = Application::Get()->GetGameHeight() / (float)NativeApp::app->surface_height;
		renderer = new BatchRenderer(30);
		texture = new Texture2D("cube.png");
		FontManager::AddFont("consola.ttf", "Consola");
		font = FontManager::GetFont("Consola", 46);
		FontManager::SetDefaultFont(font);
		glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
		playlist = new AudioPlaylist(true);
		playlist->Push(new Audio("broad spectrum.wav"));
		playlist->Push(new Audio("background.mp3"));
		playlist->Play();
		mainMenu = new UIManager;

		UIButton* btn = new UIButton("btnTest", vec2(300, 300), vec2(200, 75), "Button!!", nullptr);
		btn->SetFont(font);
		btn->SetCallback([](BtnCallbackType type, const vec2& point, void* data) {
			if (type == BtnCallbackType::PRESS) {
				bool& s = *(bool*)data;

				s = !s;
			}
		}, &shit);

		UILabel* lbl = new UILabel("lbl", vec2(100, 1000), "abcdefghijklmnopqrstuvwxyz");
		lbl->SetContentColor(0xAAFF00FF);
		lbl->SetColor(0xAA000000);

		UIImage* image = new UIImage("image", texture, vec2(0, 200), vec2(200, 200));

		UIProgressBar* bar = new UIProgressBar("bar", vec2(20, 900), vec2(400, 40), 0xFF00FF00);
		bar->SetStep(50);

		UIJoystick* joystick = new UIJoystick("joystick", vec2(400, 1200), vec2(200, 200), vec2(100, 100));
		joystick->SetColor(0xAA000000);
		joystick->SetInnerColor(0xFF0000FF);

		items[0] = btn;
		items[1] = lbl;
		items[2] = image;
		items[3] = bar;

		joystick->SetCallback([](float xOffset, float yOffset, void* data) {
			UIItem* *items = (UIItem**)data;
			for (int i = 0; i < 4; i++) {
				UIItem* item = items[i];
				items[i]->SetPosition(items[i]->GetPosition() + vec2(xOffset, yOffset));
			}

		}, (void*)items);

		mainMenu->Add(btn);
		mainMenu->Add(lbl);
		mainMenu->Add(image);
		mainMenu->Add(bar);
		mainMenu->Add(joystick);
	}

	void Render() override {
		renderer->Begin();
		if (shit) renderer->Submit("abcdefghijklmnopqrstuvwxyz", font, vec2(250, 250), 0xFFFF00FF);
		//renderer->Submit(vec3(x, y, 0.0f), vec2(200.f, 200.f), texture);
		renderer->Submit(vec3(100, 100, 0.0f), vec2(100, 100), nullptr, 0xFFFF00FF);
		renderer->End();
		renderer->Present();

		mainMenu->Render();
	}

	void End() override {
		delete renderer;
	}


	void Update(float delta) override {
		x = InputManager::GetX();
		y = InputManager::GetY();
		if (InputManager::GetKey(AKEYCODE_B))
			InputManager::HideKeyboard();

		playlist->Update();
		mainMenu->Update(delta);
	}
};


APP_START(MainApp);

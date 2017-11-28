#pragma once

#include <core/input/inputmanager.h>
#include <graphics/uiitem/uiitem.h>

namespace dank {

class UIManager : public EventListenerComponent {
private:

	void OnPress(float x, float y) override;
	void OnRelease(float x, float y) override;
	void OnMove(float x, float y) override;
	void OnKeyPress(int key) override;
	void OnKeyRelease(int key) override;
	void OnKeyRepeat(int key) override;

	List<UIItem*> items;

	UIItem* infocus;

	Renderer* renderer;
public:
	UIManager();
	UIManager(Renderer* renderer);
	~UIManager();

	void Update(float delta);
	void Render();

	void Add(UIItem* item);
	void Remove(UIItem* item);
};

}
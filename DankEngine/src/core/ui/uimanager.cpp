#include "uimanager.h"

namespace dank {

UIManager::UIManager() {
	renderer = Renderer::CreateRenderer(64);
}

UIManager::UIManager(Renderer* renderer) : renderer(renderer) {

}

UIManager::~UIManager() {
	
}

void UIManager::OnPress(float x, float y) {
	size_t size = items.GetSize();

	UIItem* tmp = infocus;

	infocus = nullptr;

	for (size_t i = 0; i < size; i++) {
		UIItem* item = items[i];

		if (!item->IsPointInside(x, y)) continue;

		infocus = item;
		item->SetPressed(true);
		item->OnPress(vec2(x, y) - item->GetAbsolutePosition());
	}

	if (infocus != tmp) {
		if (tmp) tmp->OnFocusChanged(false);
		if (infocus) infocus->OnFocusChanged(true);
	}
}

void UIManager::OnRelease(float x, float y) {
	if (infocus) infocus->OnRelease();
}

void UIManager::OnMove(float x, float y) {
	size_t size = items.GetSize();

	for (size_t i = 0; i < size; i++) {
		UIItem* item = items[i];

		if (!item->IsPointInside(x, y)) continue;

		item->OnMove(vec2(x, y) - item->GetAbsolutePosition());
	}
}

void UIManager::OnKeyPress(int key) {
	if (infocus) infocus->OnKey(key);
}

void UIManager::OnKeyRelease(int key) {

}

void UIManager::OnKeyRepeat(int key) {
	if (infocus) infocus->OnKey(key);
}

void UIManager::Update(float delta) {
	size_t size = items.GetSize();

	for (size_t i = 0; i < size; i++) {
		items[i]->OnUpdate(delta);
	}
}

void UIManager::Render() {
	renderer->Begin();

	size_t size = items.GetSize();

	for (size_t i = 0; i < size; i++) {
		items[i]->OnRender(renderer);
	}

	renderer->End();
	renderer->Present();
}

void UIManager::Add(UIItem* item) {
	items.Push_back(item);
}

void UIManager::Remove(UIItem* item) {
	items.Remove(item);
}

}
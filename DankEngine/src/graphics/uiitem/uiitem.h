#pragma once


#include <utils/string.h>
#include <maths/vec2.h>
#include <graphics/texture/texture.h>
#include <graphics/renderers/renderer.h>


namespace dank {

class UIItem {
private:
	bool isPressed;
protected:
	String name;

	vec2 position;
	vec2 size;

	unsigned int color;
	Texture2D* texture;

	UIItem* parent;

	bool isVisible;
	bool isInteractable;

	UIItem(const String& name, const vec2& position, const vec2& size);
public:
	virtual ~UIItem();

	virtual bool IsPointInside(float x, float y) const;
	virtual bool IsPointInside(const vec2& point) const;

	virtual void OnUpdate(float delta) { }
	virtual void OnRender(Renderer* renderer) = 0;

	virtual void OnPress(const vec2& point);
	virtual void OnRelease();
	virtual void OnMove(const vec2& point);
	virtual void OnKey(int keyCode);
	virtual void OnFocusChanged(bool infocus) {}

	inline void SetName(const String& name) { this->name = name; }
	inline void SetPosition(const vec2& position) { this->position = position; }
	inline void SetSize(const vec2& size) { this->size = size; }
	inline void SetColor(unsigned int color) { this->color = color; }
	inline void SetTexture(Texture2D* texture) { this->texture = texture; }
	inline void SetParent(UIItem* parent) { this->parent = parent; }
	inline void SetVisible(bool visible) { this->isVisible = visible; }
	inline void SetInteractable(bool interactable) { this->isInteractable = interactable; }

	inline const String& GetName() const { return name; }
	inline vec2 GetPosition() const { return position; }
	inline vec2 GetAbsolutePosition() const { 
		if (parent) { 
			return position + parent->GetAbsolutePosition(); 
		} else { 
			return position; 
		} 
	}
	inline vec2 GetSize() const { return size; }
	inline unsigned int GetColor() const { return color; }
	inline Texture2D* GetTexture() const { return texture; }
	inline UIItem* GetParent() const { return parent; }
	inline bool IsVisible() const { return isVisible; }
	inline bool IsInteractable() const { return isInteractable; }


	inline void SetPressed(bool pressed) { this->isPressed = pressed; }
	inline bool IsPressed() const { return isPressed; }

};


}
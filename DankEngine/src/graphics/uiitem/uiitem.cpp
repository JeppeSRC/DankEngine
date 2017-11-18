

#include "uiitem.h"
#include <utils/log.h>

namespace dank {

UIItem::UIItem(const String& name, const vec2& position, const vec2& size) : name(name), position(position), size(size), color(0xFFFFFFFF), texture(nullptr) {

}

UIItem::~UIItem() {
	delete texture;
}

bool UIItem::IsPointInside(float x, float y) const {
	vec2 pos = GetAbsolutePosition();
	if (x > pos.x && y > pos.y) {
		if (x < pos.x + size.x && y < pos.y + size.y) {
			return true;
		}
	}

	return false;
}

bool UIItem::IsPointInside(const vec2& point) const {
	return IsPointInside(point.x, point.y);
}

void UIItem::OnPress(const vec2& point) {
	LOGD("[UIItem] %s not implemented for %s Position: X=%f Y=%f", __FUNCTION__, *name, position.x, position.y);
}

void UIItem::OnRelease() {
	LOGD("[UIItem] %s not implemented for %s", __FUNCTION__, *name);
}

void UIItem::OnMove(const vec2& point) {
	LOGD("[UIItem] %s not implemented for %s", __FUNCTION__, *name);
}

void UIItem::OnKey(int keyCode) {
	LOGD("[UIItem] %s not implemented for %s KeyCode: %d", __FUNCTION__, *name, keyCode);
}

}
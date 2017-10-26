#pragma once

#include "core/nativeapp.h"


namespace dank {

	class Renderer {
	public:

		virtual void Render() = 0;
		virtual void Update() = 0;

	};
}
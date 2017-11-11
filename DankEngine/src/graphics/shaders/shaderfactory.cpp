#include "shader.h"

namespace dank {

ShaderFactory::ShaderFactory(const String& vsCode, const String& psCode) : vsCode(vsCode), psCode(psCode), prefix("#") {


}

void ShaderFactory::SetVariablePrefix(const String& prefix) { 
	this->prefix = prefix;  
}

void ShaderFactory::SetVariable(const String& name, const unsigned int v, ShaderType type) {

	size_t variableStart = (size_t)~0;
	size_t variableEnd = (size_t)~0;

	String variableName = prefix + name;

	char buff[128] = { 0 };

	switch (type) {
	case ShaderType::VERTEX:
		variableStart = vsCode.Find(variableName, 0);

		if (variableStart == (size_t)~0) {
			LOGW("[ShaderFactory] Variable \"%s\" doesn't exist in Vertex shader code!", *name);
			return;
		}

		variableEnd = variableStart + variableName.length;

		vsCode.Remove(variableStart, variableEnd);

		sprintf(buff, "%u", v);

		vsCode.Insert(buff, variableStart);

		LOGD("[ShaderFactory] Variable \"%s\" set to %s", *name, buff);

		break;

	case ShaderType::PIXEL:
		variableStart = psCode.Find(variableName, 0);

		if (variableStart == (size_t)~0) {
			LOGW("[ShaderFactory] Variable \"%s\" doesn't exist in Pixel shader code!", *name);
			return;
		}

		variableEnd = variableStart + variableName.length;

		psCode.Remove(variableStart, variableEnd);

		sprintf(buff, "%u", v);

		psCode.Insert(buff, variableStart);

		LOGD("[ShaderFactory] Variable \"%s\" set to %s", *name, buff);

		break;
	case ShaderType::ALL:
		SetVariable(name, v, ShaderType::VERTEX);
		SetVariable(name, v, ShaderType::PIXEL);
		break;
	}
}

void ShaderFactory::SetVariable(const String& name, const float v, ShaderType type) {

	size_t variableStart = (size_t)~0;
	size_t variableEnd = (size_t)~0;

	String variableName = prefix + name;

	char buff[128] = { 0 };

	switch (type) {
		case ShaderType::VERTEX:
			variableStart = vsCode.Find(variableName, 0);

			if (variableStart == (size_t)~0) {
				LOGW("[ShaderFactory] Variable \"%s\" doesn't exist in Vertex shader code!", *name);
				return;
			}

			variableEnd = variableStart + variableName.length;

			vsCode.Remove(variableStart, variableEnd);

			sprintf(buff, "%f", v);

			vsCode.Insert(buff, variableStart);

			LOGD("[ShaderFactory] Variable \"%s\" set to %s", *name, buff);

			break;

		case ShaderType::PIXEL:
			variableStart = psCode.Find(variableName, 0);

			if (variableStart == (size_t)~0) {
				LOGW("[ShaderFactory] Variable \"%s\" doesn't exist in Pixel shader code!", *name);
				return;
			}

			variableEnd = variableStart + variableName.length;

			psCode.Remove(variableStart, variableEnd);

			sprintf(buff, "%f", v);

			psCode.Insert(buff, variableStart);

			LOGD("[ShaderFactory] Variable \"%s\" set to %s", *name, buff);

			break;
		case ShaderType::ALL:
			SetVariable(name, v, ShaderType::VERTEX);
			SetVariable(name, v, ShaderType::PIXEL);
			break;
	}
}

void ShaderFactory::SetVariable(const String& name, const vec2& v, ShaderType type) {

	size_t variableStart = (size_t)~0;
	size_t variableEnd = (size_t)~0;

	String variableName = prefix + name;

	char buff[128] = { 0 };

	switch (type) {
	case ShaderType::VERTEX:
		variableStart = vsCode.Find(variableName, 0);

		if (variableStart == (size_t)~0) {
			LOGW("[ShaderFactory] Variable \"%s\" doesn't exist in Vertex shader code!", *name);
			return;
		}

		variableEnd = variableStart + variableName.length;

		vsCode.Remove(variableStart, variableEnd);

		sprintf(buff, "vec2(%f,%f)", v.x, v.y);

		vsCode.Insert(buff, variableStart);

		LOGD("[ShaderFactory] Variable \"%s\" set to %s", *name, buff);

		break;

	case ShaderType::PIXEL:
		variableStart = psCode.Find(variableName, 0);

		if (variableStart == (size_t)~0) {
			LOGW("[ShaderFactory] Variable \"%s\" doesn't exist in Pixel shader code!", *name);
			return;
		}

		variableEnd = variableStart + variableName.length;

		psCode.Remove(variableStart, variableEnd);

		sprintf(buff, "vec2(%f,%f)", v.x, v.y);

		psCode.Insert(buff, variableStart);

		LOGD("[ShaderFactory] Variable \"%s\" set to %s", *name, buff);

		break;
	case ShaderType::ALL:
		SetVariable(name, v, ShaderType::VERTEX);
		SetVariable(name, v, ShaderType::PIXEL);
		break;
	}
}

void ShaderFactory::SetVariable(const String& name, const vec3& v, ShaderType type) {

	size_t variableStart = (size_t)~0;
	size_t variableEnd = (size_t)~0;

	String variableName = prefix + name;

	char buff[128] = { 0 };

	switch (type) {
	case ShaderType::VERTEX:
		variableStart = vsCode.Find(variableName, 0);

		if (variableStart == (size_t)~0) {
			LOGW("[ShaderFactory] Variable \"%s\" doesn't exist in Vertex shader code!", *name);
			return;
		}

		variableEnd = variableStart + variableName.length;

		vsCode.Remove(variableStart, variableEnd);

		sprintf(buff, "vec3(%f,%f, %f)", v.x, v.y, v.z);

		vsCode.Insert(buff, variableStart);

		LOGD("[ShaderFactory] Variable \"%s\" set to %s", *name, buff);

		break;

	case ShaderType::PIXEL:
		variableStart = psCode.Find(variableName, 0);

		if (variableStart == (size_t)~0) {
			LOGW("[ShaderFactory] Variable \"%s\" doesn't exist in Pixel shader code!", *name);
			return;
		}

		variableEnd = variableStart + variableName.length;

		psCode.Remove(variableStart, variableEnd);

		sprintf(buff, "vec3(%f,%f, %f)", v.x, v.y, v.z);

		psCode.Insert(buff, variableStart);

		LOGD("[ShaderFactory] Variable \"%s\" set to %s", *name, buff);

		break;
	case ShaderType::ALL:
		SetVariable(name, v, ShaderType::VERTEX);
		SetVariable(name, v, ShaderType::PIXEL);
		break;
	}
}

void ShaderFactory::SetVariable(const String& name, const vec4& v, ShaderType type) {

	size_t variableStart = (size_t)~0;
	size_t variableEnd = (size_t)~0;

	String variableName = prefix + name;

	char buff[128] = { 0 };

	switch (type) {
	case ShaderType::VERTEX:
		variableStart = vsCode.Find(variableName, 0);

		if (variableStart == (size_t)~0) {
			LOGW("[ShaderFactory] Variable \"%s\" doesn't exist in Vertex shader code!", *name);
			return;
		}

		variableEnd = variableStart + variableName.length;

		vsCode.Remove(variableStart, variableEnd);

		sprintf(buff, "vec4(%f,%f,%f,%f)", v.x, v.y, v.z, v.w);

		vsCode.Insert(buff, variableStart);

		LOGD("[ShaderFactory] Variable \"%s\" set to %s", *name, buff);

		break;

	case ShaderType::PIXEL:
		variableStart = psCode.Find(variableName, 0);

		if (variableStart == (size_t)~0) {
			LOGW("[ShaderFactory] Variable \"%s\" doesn't exist in Pixel shader code!", *name);
			return;
		}

		variableEnd = variableStart + variableName.length;

		psCode.Remove(variableStart, variableEnd);

		sprintf(buff, "vec4(%f,%f,%f,%f)", v.x, v.y, v.z, v.w);

		psCode.Insert(buff, variableStart);

		LOGD("[ShaderFactory] Variable \"%s\" set to %s", *name, buff);

		break;
	case ShaderType::ALL:
		SetVariable(name, v, ShaderType::VERTEX);
		SetVariable(name, v, ShaderType::PIXEL);
		break;
	}
}

Shader* ShaderFactory::CreateShader() const {
	return denew Shader(*vsCode, *psCode);
}

}
#pragma once

#include <core/nativeapp.h>
#include <utils/map.h>
#include <utils/utils.h>
#include <core/resource/resource.h>
#include <maths/math.h>

namespace dank {

enum class ShaderType {
	VERTEX,
	PIXEL,
	ALL
};

class Shader : public ResourceShader {
public:
	static unsigned int activeShaderID;
	static Shader* activeShader;
private:
	unsigned int shader;

	Map<unsigned int, unsigned int> cache;

	void CompileShader(const char* vertex, const char* fragment);

	void OnCreate(ResourceCreateState satet);

public:
	Shader(ResourceShader* resource);
	Shader(const char* vertex, const char* fragment);
	~Shader();

	void Bind();

	unsigned int GetUniformLocation(const char* name);
	unsigned int GetAttributeLocation(const char* name);

	void SetInt(const char* const name, int v);
	void SetInt(unsigned int location, int v);
	void SetIntArray(const char* const name, int count, int* values);
	void SetIntArray(unsigned int location, int count, int* values);
	void SetFloat(const char* const name, float v);
	void SetFloat(unsigned int location, float v) const;
	void SetVec2(const char* const name, float x, float y);
	void SetVec2(unsigned int location, float x, float y) const;
	void SetVec3(const char* const name, float x, float y, float z);
	void SetVec3(unsigned int location, float x, float y, float z) const;
	void SetVec4(const char* const name, float x, float y, float z, float w);
	void SetVec4(unsigned int location, float x, float y, float z, float w) const;
	void SetMat4(const char* const name, const float* const data);
	void SetMat4(unsigned int location, const float* const data) const;

	inline void SetVec2(const char* const name, const vec2& v) { SetVec2(name, v.x, v.y); }
	inline void SetVec2(unsigned int location, const vec2& v) {  SetVec2(location, v.x, v.y); }
	inline void SetVec3(const char* const name, const vec3& v) { SetVec3(name, v.x, v.y, v.z); }
	inline void SetVec3(unsigned int location, const vec3& v) {  SetVec3(location, v.x, v.y, v.z); }
	inline void SetVec4(const char* const name, const vec4& v) { SetVec4(name, v.x, v.y, v.z, v.w); }
	inline void SetVec4(unsigned int location, const vec4& v) {  SetVec4(location, v.x, v.y, v.z, v.w); }
	inline void SetMat4(const char* const name, const mat4& m) { SetMat4(name, m.GetData()); }
	inline void SetMat4(unsigned int location, const mat4& m) {  SetMat4(location, m.GetData()); }
	
};

class ShaderFactory {
private:
	String vsCode;
	String psCode;

	String prefix;

public:
	ShaderFactory(const String& vcCode, const String& psCode);

	void SetVariablePrefix(const String& prefix);

	void SetVariable(const String& name, const unsigned int, ShaderType type);
	void SetVariable(const String& name, const float v, ShaderType type);
	void SetVariable(const String& name, const vec2& v, ShaderType type);
	void SetVariable(const String& name, const vec3& v, ShaderType type);
	void SetVariable(const String& name, const vec4& v, ShaderType type);


	Shader* CreateShader() const;

	inline String GetVSCode() const { return vsCode; }
	inline String GetPSCode() const { return psCode; }


};

}
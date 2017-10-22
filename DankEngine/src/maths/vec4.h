#pragma once
#include "mathcommon.h"

namespace dank {

	class vec2;
	class vec3;

	class vec4 {
	public:
		float x;
		float y;
		float z;
		float w;

	public:
		vec4();
		explicit vec4(const vec2& v, float z = 0, float w = 0);
		explicit vec4(const vec3& v, float z = 0);
		vec4(float x, float y, float z, float w);

		vec4& Add(const vec4& v);
		vec4& Add(const vec3& v);
		vec4& Add(const vec2& v);
		vec4& Add(float v);
		vec4& Subtract(const vec4& v);
		vec4& Subtract(const vec3& v);
		vec4& Subtract(const vec2& v);
		vec4& Subtract(float v);
		vec4& Multiply(const vec4& v);
		vec4& Multiply(const vec3& v);
		vec4& Multiply(const vec2& v);
		vec4& Multiply(float v);
		vec4& Divide(const vec4& v);
		vec4& Divide(const vec3& v);
		vec4& Divide(const vec2& v);
		vec4& Divide(float v);
		vec4& Normalize();

		float Length() const;
		float LengthSqrt() const;

		inline friend vec4 operator+(const vec4& l, const vec4& r) { return vec4(l).Add(r); }
		inline friend vec4 operator-(const vec4& l, const vec4& r) { return vec4(l).Subtract(r); }
		inline friend vec4 operator*(const vec4& l, const vec4& r) { return vec4(l).Multiply(r); }
		inline friend vec4 operator/(const vec4& l, const vec4& r) { return vec4(l).Divide(r); }

		inline friend vec4 operator+(const vec4& l, const vec3& r) { return vec4(l).Add(r); }
		inline friend vec4 operator-(const vec4& l, const vec3& r) { return vec4(l).Subtract(r); }
		inline friend vec4 operator*(const vec4& l, const vec3& r) { return vec4(l).Multiply(r); }
		inline friend vec4 operator/(const vec4& l, const vec3& r) { return vec4(l).Divide(r); }

		inline friend vec4 operator+(const vec4& l, const vec2& r) { return vec4(l).Add(r); }
		inline friend vec4 operator-(const vec4& l, const vec2& r) { return vec4(l).Subtract(r); }
		inline friend vec4 operator*(const vec4& l, const vec2& r) { return vec4(l).Multiply(r); }
		inline friend vec4 operator/(const vec4& l, const vec2& r) { return vec4(l).Divide(r); }

		inline friend vec4 operator+(const vec4& l, float r) { return vec4(l).Add(r); }
		inline friend vec4 operator-(const vec4& l, float r) { return vec4(l).Subtract(r); }
		inline friend vec4 operator*(const vec4& l, float r) { return vec4(l).Multiply(r); }
		inline friend vec4 operator/(const vec4& l, float r) { return vec4(l).Divide(r); }

		inline void operator+=(const vec4& v) { Add(v); }
		inline void operator-=(const vec4& v) { Subtract(v); }
		inline void operator*=(const vec4& v) { Multiply(v); }
		inline void operator/=(const vec4& v) { Divide(v); }

		inline void operator+=(const vec3& v) { Add(v); }
		inline void operator-=(const vec3& v) { Subtract(v); }
		inline void operator*=(const vec3& v) { Multiply(v); }
		inline void operator/=(const vec3& v) { Divide(v); }

		inline void operator+=(const vec2& v) { Add(v); }
		inline void operator-=(const vec2& v) { Subtract(v); }
		inline void operator*=(const vec2& v) { Multiply(v); }
		inline void operator/=(const vec2& v) { Divide(v); }

		inline void operator+=(float v) { Add(v); }
		inline void operator-=(float v) { Subtract(v); }
		inline void operator*=(float v) { Multiply(v); }
		inline void operator/=(float v) { Divide(v); }

		bool operator==(const vec4& v) const;
		bool operator!=(const vec4& v) const;

		bool operator>(const vec4& v) const;
		bool operator<(const vec4& v) const;
		bool operator>=(const vec4& v) const;
		bool operator<=(const vec4& v) const;

		inline vec4 operator-() { return vec4(-x, -y, -z, -w); }
	};
}
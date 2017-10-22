#pragma once
#include "mathcommon.h"

namespace dank {

	class vec2;
	class vec4;

	class vec3 {
	public:
		float x;
		float y;
		float z;


	public:
		vec3();
		explicit vec3(const vec2& v, float z = 0);
		vec3(float x, float y, float z);
		explicit vec3(const vec4& v);

		vec3& Add(const vec4& v);
		vec3& Add(const vec3& v);
		vec3& Add(const vec2& v);
		vec3& Add(float v);
		vec3& Subtract(const vec4& v);
		vec3& Subtract(const vec3& v);
		vec3& Subtract(const vec2& v);
		vec3& Subtract(float v);
		vec3& Multiply(const vec4& v);
		vec3& Multiply(const vec3& v);
		vec3& Multiply(const vec2& v);
		vec3& Multiply(float v);
		vec3& Divide(const vec4& v);
		vec3& Divide(const vec3& v);
		vec3& Divide(const vec2& v);
		vec3& Divide(float v);
		vec3& Normalize();


		float Length() const;
		float LengthSqrt() const;

		float Dot(const vec3& v) const;
		vec3 Cross(const vec3& v) const;

		vec3& RotateX(float angle);
		vec3& RotateY(float angle);
		vec3& RotateZ(float angle);

		inline friend vec3 operator+(const vec3& l, const vec4& r) { return vec3(l).Add(r); }
		inline friend vec3 operator-(const vec3& l, const vec4& r) { return vec3(l).Subtract(r); }
		inline friend vec3 operator*(const vec3& l, const vec4& r) { return vec3(l).Multiply(r); }
		inline friend vec3 operator/(const vec3& l, const vec4& r) { return vec3(l).Divide(r); }

		inline friend vec3 operator+(const vec3& l, const vec3& r) { return vec3(l).Add(r); }
		inline friend vec3 operator-(const vec3& l, const vec3& r) { return vec3(l).Subtract(r); }
		inline friend vec3 operator*(const vec3& l, const vec3& r) { return vec3(l).Multiply(r); }
		inline friend vec3 operator/(const vec3& l, const vec3& r) { return vec3(l).Divide(r); }

		inline friend vec3 operator+(const vec3& l, const vec2& r) { return vec3(l).Add(r); }
		inline friend vec3 operator-(const vec3& l, const vec2& r) { return vec3(l).Subtract(r); }
		inline friend vec3 operator*(const vec3& l, const vec2& r) { return vec3(l).Multiply(r); }
		inline friend vec3 operator/(const vec3& l, const vec2& r) { return vec3(l).Divide(r); }

		inline friend vec3 operator+(const vec3& l, float r) { return vec3(l).Add(r); }
		inline friend vec3 operator-(const vec3& l, float r) { return vec3(l).Subtract(r); }
		inline friend vec3 operator*(const vec3& l, float r) { return vec3(l).Multiply(r); }
		inline friend vec3 operator/(const vec3& l, float r) { return vec3(l).Divide(r); }

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

		bool operator==(const vec3& v) const;
		bool operator!=(const vec3& v) const;

		bool operator>(const vec3& v) const;
		bool operator<(const vec3& v) const;
		bool operator>=(const vec3& v) const;
		bool operator<=(const vec3& v) const;

		inline vec3 operator-() { return vec3(-x, -y, -z); }
	};
}
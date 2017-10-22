#include "vec3.h"
#include "vec2.h"
#include <utils/log.h>
#include <memory>
#include "vec4.h"


namespace dank {

	vec3::vec3() : x(0), y(0), z(0) {}

	vec3::vec3(const vec2& v, float z) : x(v.x), y(v.y), z(z) {}

	vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	vec3::vec3(const vec4& v) : x(v.x), y(v.y), z(v.z) {}

	vec3& vec3::Add(const vec4& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3& vec3::Add(const vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3& vec3::Add(const vec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	vec3& vec3::Add(float v) {
		x += v;
		y += v;
		z += v;
		return *this;
	}

	vec3& vec3::Subtract(const vec4& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec3& vec3::Subtract(const vec3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec3& vec3::Subtract(const vec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	vec3& vec3::Subtract(float v) {
		x -= v;
		y -= v;
		z -= v;
		return *this;
	}

	vec3& vec3::Multiply(const vec4& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	vec3& vec3::Multiply(const vec3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	vec3& vec3::Multiply(const vec2& v) {
		x *= v.x;
		y *= v.y;
		return *this;
	}

	vec3& vec3::Multiply(float v) {
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	vec3& vec3::Divide(const vec4& v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	vec3& vec3::Divide(const vec3& v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	vec3& vec3::Divide(const vec2& v) {
		x /= v.x;
		y /= v.y;
		return *this;
	}

	vec3& vec3::Divide(float v) {
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}

	float vec3::Dot(const vec3& v) const {
		return x * v.x + y * v.y * z * v.z;
	}

	vec3& vec3::Normalize() {
		return Multiply(1.0f / LengthSqrt());
	}

	float vec3::Length() const {
		return x * x + y * y + z * z;
	}

	float vec3::LengthSqrt() const {
		return sqrtf(Length());
	}

	vec3 vec3::Cross(const vec3& v) const {

		float _x = y * v.z - z * v.y;
		float _y = z * v.x - x * v.z;
		float _z = x * v.y - y * v.x;

		return vec3(_x, _y, _z);
	}

	vec3& vec3::RotateX(float angle) {

		float a = (float)FD_TO_RADIANS_F(angle);

		float _y = y * cosf(a) - z * sinf(a);
		float _z = z * cosf(a) + y * sinf(a);

		y = _y;
		z = _z;

		return *this;
	}

	vec3& vec3::RotateY(float angle) {

		float a = (float)FD_TO_RADIANS_F(angle);

		float _z = z * cosf(a) - x * sinf(a);
		float _x = x * cosf(a) + z * sinf(a);

		x = _x;
		z = _z;

		return *this;
	}

	vec3& vec3::RotateZ(float angle) {

		float a = (float)FD_TO_RADIANS_F(angle);

		float _x = x * cosf(a) - y * sinf(a);
		float _y = y * cosf(a) + x * sinf(a);

		x = _x;
		y = _y;

		return *this;
	}

	bool vec3::operator==(const vec3& v) const {
		return x == v.x && y == v.y && z == v.z;
	}

	bool vec3::operator!=(const vec3& v) const {
		return !(x == v.x && y == v.y && z == v.z);
	}

	bool vec3::operator>(const vec3& v) const {
		return x > v.x && y > v.y && z > v.z;
	}

	bool vec3::operator<(const vec3& v) const {
		return x < v.x && y < v.y && z < v.z;
	}

	bool vec3::operator>=(const vec3& v) const {
		return x >= v.x && y >= v.y && z >= v.z;
	}

	bool vec3::operator<=(const vec3& v) const {
		return x <= v.x && y <= v.y && z <= v.z;
	}
}
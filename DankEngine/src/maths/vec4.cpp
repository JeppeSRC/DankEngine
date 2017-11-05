#include "vec4.h"
#include "vec3.h"
#include "vec2.h"
#include <memory>

namespace dank {

	vec4::vec4() : x(0), y(0), z(0), w(0) {}

	vec4::vec4(const vec2& v, float z, float w) : x(v.x), y(v.x), z(z), w(w) {}

	vec4::vec4(const vec3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

	vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

#if SSE_MATH
#if defined(__arm__) || defined(__aarch64__)
vec4& vec4::Add(const vec4& v) {
	float vtmp[4]{ v.x, v.y, v.z, v.w };
	float tmp[4]{ x, y, z, w };
	float32x4_t vxmm = vld1q_f32(vtmp);
	float32x4_t xmm = vld1q_f32(tmp);
	xmm = vaddq_f32(xmm, vxmm);
    memcpy(this, &xmm, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Add(const vec3& v) {
	float vtmp[4]{ v.x, v.y, v.z, 0 };
	float tmp[4]{ x, y, z, w };
	float32x4_t vxmm = vld1q_f32(vtmp);
	float32x4_t xmm = vld1q_f32(tmp);
	xmm = vaddq_f32(xmm, vxmm);
    memcpy(this, &xmm, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Add(const vec2& v) {
	float vtmp[2]{ v.x, v.y };
	float tmp[2]{ x, y };
	float32x2_t vxmm = vld1_f32(vtmp);
	float32x2_t xmm = vld1_f32(tmp);
	xmm = vadd_f32(xmm, vxmm);
	memcpy(this, &xmm, sizeof(float) * 2);
	return *this;
}

vec4& vec4::Add(float v) {
	float vtmp[4]{ v, v, v, v };
	float tmp[4]{ x, y, z, w };
	float32x4_t vxmm = vld1q_f32(vtmp);
	float32x4_t xmm = vld1q_f32(tmp);
	xmm = vaddq_f32(xmm, vxmm);
    memcpy(this, &xmm, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Subtract(const vec4& v) {
	float vtmp[4]{ v.x, v.y, v.z, v.w };
	float tmp[4]{ x, y, z, w };
	float32x4_t vxmm = vld1q_f32(vtmp);
	float32x4_t xmm = vld1q_f32(tmp);
	xmm = vsubq_f32(xmm, vxmm);
    memcpy(this, &xmm, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Subtract(const vec3& v) {
	float vtmp[4]{ v.x, v.y, v.z, 0 };
	float tmp[4]{ x, y, z, w };
	float32x4_t vxmm = vld1q_f32(vtmp);
	float32x4_t xmm = vld1q_f32(tmp);
	xmm = vsubq_f32(xmm, vxmm);
    memcpy(this, &xmm, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Subtract(const vec2& v) {
	float vtmp[2]{ v.x, v.y };
	float tmp[2]{ x, y };
	float32x2_t vxmm = vld1_f32(vtmp);
	float32x2_t xmm = vld1_f32(tmp);
	xmm = vsub_f32(xmm, vxmm);
	memcpy(this, &xmm, sizeof(float) * 2);
	return *this;
}

vec4& vec4::Subtract(float v) {
	float vtmp[4]{ v, v, v, v };
	float tmp[4]{ x, y, z, w };
	float32x4_t vxmm = vld1q_f32(vtmp);
	float32x4_t xmm = vld1q_f32(tmp);
	xmm = vsubq_f32(xmm, vxmm);
    memcpy(this, &xmm, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Multiply(const vec4& v) {
	float vtmp[4]{ v.x, v.y, v.z, v.w };
	float tmp[4]{ x, y, z, w };
	float32x4_t vxmm = vld1q_f32(vtmp);
	float32x4_t xmm = vld1q_f32(tmp);
	xmm = vmulq_f32(xmm, vxmm);
    memcpy(this, &xmm, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Multiply(const vec3& v) {
	float vtmp[4]{ v.x, v.y, v.z, 1 };
	float tmp[4]{ x, y, z, w };
	float32x4_t vxmm = vld1q_f32(vtmp);
	float32x4_t xmm = vld1q_f32(tmp);
	xmm = vmulq_f32(xmm, vxmm);
    memcpy(this, &xmm, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Multiply(const vec2& v) {
	float vtmp[2]{ v.x, v.y };
	float tmp[2]{ x, y };
	float32x2_t vxmm = vld1_f32(vtmp);
	float32x2_t xmm = vld1_f32(tmp);
	xmm = vmul_f32(xmm, vxmm);
	memcpy(this, &xmm, sizeof(float) * 2);
	return *this;
}

vec4& vec4::Multiply(float v) {
	float vtmp[4]{ v, v, v, v };
	float tmp[4]{ x, y, z, w };
	float32x4_t vxmm = vld1q_f32(vtmp);
	float32x4_t xmm = vld1q_f32(tmp);
	xmm = vmulq_f32(xmm, vxmm);
    memcpy(this, &xmm, sizeof(float) * 4);
	return *this;
}
#else
vec4& vec4::Add(const vec4& v) {
	__attribute__((aligned(16))) float tmp[4];
	__m128 vxmm = _mm_set_ps(v.w, v.z, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_add_ps(xmm, vxmm);
	_mm_store_ps((float*)&tmp, xmm);
	memcpy(this, &tmp, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Add(const vec3& v) {
	__attribute__((aligned(16))) float tmp[4];
	__m128 vxmm = _mm_set_ps(0, v.z, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_add_ps(xmm, vxmm);
	_mm_store_ps((float*)&tmp, xmm);
	memcpy(this, &tmp, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Add(const vec2& v) {
	__attribute__((aligned(16))) float tmp[4];
	__m128 vxmm = _mm_set_ps(0, 0, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_add_ps(xmm, vxmm);
	_mm_store_ps((float*)&tmp, xmm);
	memcpy(this, &tmp, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Add(float v) {
	__attribute__((aligned(16))) float tmp[4];
	__m128 vxmm = _mm_set_ps(v, v, v, v);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_add_ps(xmm, vxmm);
	_mm_store_ps((float*)&tmp, xmm);
	memcpy(this, &tmp, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Subtract(const vec4& v) {
	__attribute__((aligned(16))) float tmp[4];
	__m128 vxmm = _mm_set_ps(v.w, v.z, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_sub_ps(xmm, vxmm);
	_mm_store_ps((float*)&tmp, xmm);
	 memcpy(this, &tmp, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Subtract(const vec3& v) {
	__attribute__((aligned(16))) float tmp[4];
	__m128 vxmm = _mm_set_ps(0, v.z, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_sub_ps(xmm, vxmm);
	_mm_store_ps((float*)&tmp, xmm);
	 memcpy(this, &tmp, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Subtract(const vec2& v) {
	__attribute__((aligned(16))) float tmp[4];
	__m128 vxmm = _mm_set_ps(0, 0, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_sub_ps(xmm, vxmm);
	_mm_store_ps((float*)&tmp, xmm);
	memcpy(this, &tmp, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Subtract(float v) {
	__attribute__((aligned(16))) float tmp[4];
	__m128 vxmm = _mm_set_ps(v, v, v, v);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_sub_ps(xmm, vxmm);
	_mm_store_ps((float*)&tmp, xmm);
	memcpy(this, &tmp, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Multiply(const vec4& v) {
	__attribute__((aligned(16))) float tmp[4];
	__m128 vxmm = _mm_set_ps(v.w, v.z, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_mul_ps(xmm, vxmm);
	_mm_store_ps((float*)&tmp, xmm);
	memcpy(this, &tmp, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Multiply(const vec3& v) {
	__attribute__((aligned(16))) float tmp[4];
	__m128 vxmm = _mm_set_ps(1, v.z, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_mul_ps(xmm, vxmm);
	_mm_store_ps((float*)&tmp, xmm);
	memcpy(this, &tmp, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Multiply(const vec2& v) {
	__attribute__((aligned(16))) float tmp[4];
	__m128 vxmm = _mm_set_ps(1, 1, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_mul_ps(xmm, vxmm);
	_mm_store_ps((float*)&tmp, xmm);
	memcpy(this, &tmp, sizeof(float) * 4);
	return *this;
}

vec4& vec4::Multiply(float v) {
	__attribute__((aligned(16))) float tmp[4];
	__m128 vxmm = _mm_set_ps(v, v, v, v);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_mul_ps(xmm, vxmm);
	_mm_store_ps((float*)&tmp, xmm);
	memcpy(this, &tmp, sizeof(float) * 4);
	return *this;
}

#endif
#else
vec4& vec4::Add(const vec4& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

vec4& vec4::Add(const vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vec4& vec4::Add(const vec2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

vec4& vec4::Add(float v) {
	x += v;
	y += v;
	z += v;
	w += v;
	return *this;
}

vec4& vec4::Subtract(const vec4& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w += v.w;
	return *this;
}

vec4& vec4::Subtract(const vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vec4& vec4::Subtract(const vec2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

vec4& vec4::Subtract(float v) {
	x -= v;
	y -= v;
	z -= v;
	w += v;
	return *this;
}

vec4& vec4::Multiply(const vec4& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w += v.w;
	return *this;
}

vec4& vec4::Multiply(const vec3& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

vec4& vec4::Multiply(const vec2& v) {
	x *= v.x;
	y *= v.y;
	return *this;
}

vec4& vec4::Multiply(float v) {
	x *= v;
	y *= v;
	z *= v;
	w += v;
	return *this;
}

#endif

vec4& vec4::Divide(const vec4& v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w += v.w;
	return *this;
}

vec4& vec4::Divide(const vec3& v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

vec4& vec4::Divide(const vec2& v) {
	x /= v.x;
	y /= v.y;
	return *this;
}

vec4& vec4::Divide(float v) {
	x /= v;
	y /= v;
	z /= v;
	w += v;
	return *this;
}


vec4& vec4::Normalize() {
	return Multiply(1.0f / LengthSqrt());
}

float vec4::Length() const {
	return x * x + y * y + z * z + w * w;
}

float vec4::LengthSqrt() const {
	return sqrtf(Length());
}

bool vec4::operator==(const vec4& v) const {
	return x == v.x && y == v.y && z == v.z && w == v.w;
}

bool vec4::operator!=(const vec4& v) const {
	return !(x == v.x && y == v.y && z == v.z && w == v.w);
}

bool vec4::operator>(const vec4& v) const {
	return x > v.x && y > v.y && z > v.z && w > v.w;
}

bool vec4::operator<(const vec4& v) const {
	return x < v.x && y < v.y && z < v.z && w < v.w;
}

bool vec4::operator>=(const vec4& v) const {
	return x >= v.x && y >= v.y && z >= v.z && w >= v.w;
}

bool vec4::operator<=(const vec4& v) const {
	return x <= v.x && y <= v.y && z <= v.z && w <= v.w;
}
}
#include "mat4.h"
#include "vec4.h"
#include "vec3.h"
#include "vec2.h"
#include <memory>

namespace dank {

#ifdef SSE_X86

void mat4::LoadRows(__m128* xmm) const {

	xmm[0] = _mm_set_ps(m[0 + 3 * 4], m[0 + 2 * 4], m[0 + 1 * 4], m[0 + 0 * 4]);
	xmm[1] = _mm_set_ps(m[1 + 3 * 4], m[1 + 2 * 4], m[1 + 1 * 4], m[1 + 0 * 4]);
	xmm[2] = _mm_set_ps(m[2 + 3 * 4], m[2 + 2 * 4], m[2 + 1 * 4], m[2 + 0 * 4]);
	xmm[3] = _mm_set_ps(m[3 + 3 * 4], m[3 + 2 * 4], m[3 + 1 * 4], m[3 + 0 * 4]);
}

void mat4::LoadColumns(__m128* xmm) const {

	xmm[0] = _mm_set_ps(m[3 + 0 * 4], m[2 + 0 * 4], m[1 + 0 * 4], m[0 + 0 * 4]);
	xmm[1] = _mm_set_ps(m[3 + 1 * 4], m[2 + 1 * 4], m[1 + 1 * 4], m[0 + 1 * 4]);
	xmm[2] = _mm_set_ps(m[3 + 2 * 4], m[2 + 2 * 4], m[1 + 2 * 4], m[0 + 2 * 4]);
	xmm[3] = _mm_set_ps(m[3 + 3 * 4], m[2 + 3 * 4], m[1 + 3 * 4], m[0 + 3 * 4]);
}

#elif defined(SSE_ARM)

void mat4::LoadRows(float32x4_t* xmm) const {
	__attribute__((aligned(16))) float tmp[4];

	tmp[0] = m[0 + 0 * 4];
	tmp[1] = m[0 + 1 * 4];
	tmp[2] = m[0 + 2 * 4];
	tmp[3] = m[0 + 3 * 4];

	xmm[0] = vld1q_f32(tmp);

	tmp[0] = m[1 + 0 * 4];
	tmp[1] = m[1 + 1 * 4];
	tmp[2] = m[1 + 2 * 4];
	tmp[3] = m[1 + 3 * 4];

	xmm[1] = vld1q_f32(tmp);

	tmp[0] = m[2 + 0 * 4];
	tmp[1] = m[2 + 1 * 4];
	tmp[2] = m[2 + 2 * 4];
	tmp[3] = m[2 + 3 * 4];

	xmm[2] = vld1q_f32(tmp);

	tmp[0] = m[3 + 0 * 4];
	tmp[1] = m[3 + 1 * 4];
	tmp[2] = m[3 + 2 * 4];
	tmp[3] = m[3 + 3 * 4];

	xmm[3] = vld1q_f32(tmp);
}

void mat4::LoadColumns(float32x4_t* xmm) const {
	__attribute__((aligned(16))) float tmp[4];

	tmp[0] = m[0 + 0 * 4];
	tmp[1] = m[1 + 0 * 4];
	tmp[2] = m[2 + 0 * 4];
	tmp[3] = m[3 + 0 * 4];

	xmm[0] = vld1q_f32(tmp);

	tmp[0] = m[0 + 1 * 4];
	tmp[1] = m[1 + 1 * 4];
	tmp[2] = m[2 + 1 * 4];
	tmp[3] = m[3 + 1 * 4];

	xmm[1] = vld1q_f32(tmp);

	tmp[0] = m[0 + 2 * 4];
	tmp[1] = m[1 + 2 * 4];
	tmp[2] = m[2 + 2 * 4];
	tmp[3] = m[3 + 2 * 4];

	xmm[2] = vld1q_f32(tmp);

	tmp[0] = m[0 + 3 * 4];
	tmp[1] = m[1 + 3 * 4];
	tmp[2] = m[2 + 3 * 4];
	tmp[3] = m[3 + 3 * 4];

	xmm[3] = vld1q_f32(tmp);
}

#endif

mat4::mat4() { memset(m, 0, sizeof(m)); }

mat4::mat4(float diagonal) {
	memset(m, 0, sizeof(m));
	m[0 + 0 * 4] = diagonal;
	m[1 + 1 * 4] = diagonal;
	m[2 + 2 * 4] = diagonal;
	m[3 + 3 * 4] = diagonal;
}

mat4::mat4(const float* const data) {
	memcpy(m, data, sizeof(m));
}

mat4 mat4::Translate(const vec3& v) {
	mat4 tmp(1);

	tmp.m[0 + 3 * 4] = v.x;
	tmp.m[1 + 3 * 4] = v.y;
	tmp.m[2 + 3 * 4] = v.z;

	return tmp;
}

mat4 mat4::Rotate(const vec3& v) {
	mat4 x(1), y(1), z(1);

	float xcos = cosf((float)FD_TO_RADIANS_F(v.x));
	float xsin = sinf((float)FD_TO_RADIANS_F(v.x));
	float ycos = cosf((float)FD_TO_RADIANS_F(v.y));
	float ysin = sinf((float)FD_TO_RADIANS_F(v.y));
	float zcos = cosf((float)FD_TO_RADIANS_F(v.z));
	float zsin = sinf((float)FD_TO_RADIANS_F(v.z));

	x.m[1 + 1 * 4] = xcos; x.m[1 + 2 * 4] = -xsin;
	x.m[2 + 1 * 4] = xsin; x.m[2 + 2 * 4] = xcos;

	y.m[0 + 0 * 4] = ycos; y.m[0 + 2 * 4] = -ysin;
	y.m[2 + 0 * 4] = ysin; y.m[2 + 2 * 4] = ycos;

	z.m[0 + 0 * 4] = zcos; z.m[0 + 1 * 4] = -zsin;
	z.m[1 + 0 * 4] = zsin; z.m[1 + 1 * 4] = zcos;

	return x * y * z;
}

mat4 mat4::Scale(const vec3& v) {
	mat4 tmp(1);

	tmp.m[0 + 0 * 4] = v.x;
	tmp.m[1 + 1 * 4] = v.y;
	tmp.m[2 + 2 * 4] = v.z;

	return tmp;
}

mat4 mat4::Inverse(mat4 m) {

	float tmp[16];

	tmp[0] = m.m[5] * m.m[10] * m.m[15] -
		m.m[5] * m.m[11] * m.m[14] -
		m.m[9] * m.m[6] * m.m[15] +
		m.m[9] * m.m[7] * m.m[14] +
		m.m[13] * m.m[6] * m.m[11] -
		m.m[13] * m.m[7] * m.m[10];

	tmp[4] = -m.m[4] * m.m[10] * m.m[15] +
		m.m[4] * m.m[11] * m.m[14] +
		m.m[8] * m.m[6] * m.m[15] -
		m.m[8] * m.m[7] * m.m[14] -
		m.m[12] * m.m[6] * m.m[11] +
		m.m[12] * m.m[7] * m.m[10];

	tmp[8] = m.m[4] * m.m[9] * m.m[15] -
		m.m[4] * m.m[11] * m.m[13] -
		m.m[8] * m.m[5] * m.m[15] +
		m.m[8] * m.m[7] * m.m[13] +
		m.m[12] * m.m[5] * m.m[11] -
		m.m[12] * m.m[7] * m.m[9];

	tmp[12] = -m.m[4] * m.m[9] * m.m[14] +
		m.m[4] * m.m[10] * m.m[13] +
		m.m[8] * m.m[5] * m.m[14] -
		m.m[8] * m.m[6] * m.m[13] -
		m.m[12] * m.m[5] * m.m[10] +
		m.m[12] * m.m[6] * m.m[9];

	tmp[1] = -m.m[1] * m.m[10] * m.m[15] +
		m.m[1] * m.m[11] * m.m[14] +
		m.m[9] * m.m[2] * m.m[15] -
		m.m[9] * m.m[3] * m.m[14] -
		m.m[13] * m.m[2] * m.m[11] +
		m.m[13] * m.m[3] * m.m[10];

	tmp[5] = m.m[0] * m.m[10] * m.m[15] -
		m.m[0] * m.m[11] * m.m[14] -
		m.m[8] * m.m[2] * m.m[15] +
		m.m[8] * m.m[3] * m.m[14] +
		m.m[12] * m.m[2] * m.m[11] -
		m.m[12] * m.m[3] * m.m[10];

	tmp[9] = -m.m[0] * m.m[9] * m.m[15] +
		m.m[0] * m.m[11] * m.m[13] +
		m.m[8] * m.m[1] * m.m[15] -
		m.m[8] * m.m[3] * m.m[13] -
		m.m[12] * m.m[1] * m.m[11] +
		m.m[12] * m.m[3] * m.m[9];

	tmp[13] = m.m[0] * m.m[9] * m.m[14] -
		m.m[0] * m.m[10] * m.m[13] -
		m.m[8] * m.m[1] * m.m[14] +
		m.m[8] * m.m[2] * m.m[13] +
		m.m[12] * m.m[1] * m.m[10] -
		m.m[12] * m.m[2] * m.m[9];

	tmp[2] = m.m[1] * m.m[6] * m.m[15] -
		m.m[1] * m.m[7] * m.m[14] -
		m.m[5] * m.m[2] * m.m[15] +
		m.m[5] * m.m[3] * m.m[14] +
		m.m[13] * m.m[2] * m.m[7] -
		m.m[13] * m.m[3] * m.m[6];

	tmp[6] = -m.m[0] * m.m[6] * m.m[15] +
		m.m[0] * m.m[7] * m.m[14] +
		m.m[4] * m.m[2] * m.m[15] -
		m.m[4] * m.m[3] * m.m[14] -
		m.m[12] * m.m[2] * m.m[7] +
		m.m[12] * m.m[3] * m.m[6];

	tmp[10] = m.m[0] * m.m[5] * m.m[15] -
		m.m[0] * m.m[7] * m.m[13] -
		m.m[4] * m.m[1] * m.m[15] +
		m.m[4] * m.m[3] * m.m[13] +
		m.m[12] * m.m[1] * m.m[7] -
		m.m[12] * m.m[3] * m.m[5];

	tmp[14] = -m.m[0] * m.m[5] * m.m[14] +
		m.m[0] * m.m[6] * m.m[13] +
		m.m[4] * m.m[1] * m.m[14] -
		m.m[4] * m.m[2] * m.m[13] -
		m.m[12] * m.m[1] * m.m[6] +
		m.m[12] * m.m[2] * m.m[5];

	tmp[3] = -m.m[1] * m.m[6] * m.m[11] +
		m.m[1] * m.m[7] * m.m[10] +
		m.m[5] * m.m[2] * m.m[11] -
		m.m[5] * m.m[3] * m.m[10] -
		m.m[9] * m.m[2] * m.m[7] +
		m.m[9] * m.m[3] * m.m[6];

	tmp[7] = m.m[0] * m.m[6] * m.m[11] -
		m.m[0] * m.m[7] * m.m[10] -
		m.m[4] * m.m[2] * m.m[11] +
		m.m[4] * m.m[3] * m.m[10] +
		m.m[8] * m.m[2] * m.m[7] -
		m.m[8] * m.m[3] * m.m[6];

	tmp[11] = -m.m[0] * m.m[5] * m.m[11] +
		m.m[0] * m.m[7] * m.m[9] +
		m.m[4] * m.m[1] * m.m[11] -
		m.m[4] * m.m[3] * m.m[9] -
		m.m[8] * m.m[1] * m.m[7] +
		m.m[8] * m.m[3] * m.m[5];

	tmp[15] = m.m[0] * m.m[5] * m.m[10] -
		m.m[0] * m.m[6] * m.m[9] -
		m.m[4] * m.m[1] * m.m[10] +
		m.m[4] * m.m[2] * m.m[9] +
		m.m[8] * m.m[1] * m.m[6] -
		m.m[8] * m.m[2] * m.m[5];

	mat4 n;

	float determinant = m.m[0] * tmp[0] + m.m[1] * tmp[4] + m.m[2] * tmp[8] + m.m[3] * tmp[12];

	for (uint_t i = 0; i < 16; i++)
		n.m[i] = tmp[i] * determinant;

	return n;
}

mat4 mat4::Perspective(float fov, float aspect, float zNear, float zFar) {

	mat4 r(1);

	float* m = r.m;

	const float tanHalf = tanh(fov / 2);

	m[0 + 0 * 4] = 1.0f / (tanHalf * aspect);
	m[1 + 1 * 4] = 1.0f / tanHalf;
	m[2 + 2 * 4] = zFar / (zFar - zNear);
	m[3 + 2 * 4] = 1;
	m[2 + 3 * 4] = -zNear * (zFar / (zFar - zNear));
	m[3 + 3 * 4] = 0;

	return r;
}


mat4 mat4::Orthographic(float left, float right, float top, float bottom, float zNear, float zFar) {
	mat4 r;

	float* m = r.m;

	float w = 2.0f / (right - left);
	float h = 2.0f / (top - bottom);
	float z = -2.0f / (zFar - zNear);

	m[0 + 0 * 4] = w;
	m[1 + 1 * 4] = h;
	m[2 + 2 * 4] = z;

	m[0 + 3 * 4] = -(right + left) / (right - left);
	m[1 + 3 * 4] = -(top + bottom) / (top - bottom);
	m[2 + 3 * 4] = -(zFar + zNear) / (zFar - zNear);
	m[3 + 3 * 4] = 1.0f;

	return r;
}

#ifdef SSE_X86

mat4 mat4::operator*(const mat4& r) const {
	mat4 tmp;
	__m128 col[4];
	__m128 rows[4];

	r.LoadColumns(col);
	LoadRows(rows);

	float tmpRes[4];
	
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			__m128 res = _mm_mul_ps(rows[x], col[y]);
			_mm_store_ps(tmpRes, res);
			tmp.m[x + y * 4] = tmpRes[0] + tmpRes[1] + tmpRes[2] + tmpRes[3];
		}
	}


	return tmp;
}

vec4 mat4::operator*(const vec4& v) const {
	__m128 vec;
	__m128 col[4];

	vec = _mm_set_ps(v.w, v.z, v.y, v.x);

	LoadRows(col);

	__m128 res = _mm_mul_ps(vec, col[0]);

	for (int i = 1; i < 4; i++) {
		//res = _mm_fmadd_ps(vec[i], col[i], res);
		res = _mm_add_ps(_mm_mul_ps(vec, col[i]), res);
	}
	
	vec4 m(0, 0, 0, 0);

	memcpy(&m, &res, sizeof(float) * 4);

	return m;
}

vec3 mat4::operator*(const vec3& v) const {
	__m128 vec;
	__m128 col[4];

	vec = _mm_set_ps(1, v.z, v.y, v.x);


	LoadRows(col);

	__m128 res = _mm_mul_ps(vec, col[0]);

	for (int i = 1; i < 3; i++) {
		//res = _mm_fmadd_ps(vec[i], col[i], res);
		res = _mm_add_ps(_mm_mul_ps(vec, col[i]), res);
	}

	vec3 m(0, 0, 0);

	memcpy(&m, &res, sizeof(float) * 3);

	return m;
}

#elif defined(SSE_ARM)

mat4 mat4::operator*(const mat4& r) const {
	mat4 tmp;

	float32x4_t col[4];
	float32x4_t rows[4];

	r.LoadColumns(col);
	LoadRows(rows);

	float tmpRes[4];

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			float32x4_t res = vmulq_f32(rows[x], col[y]);
			vst1q_f32(tmpRes, res);
			tmp.m[x + y * 4] = tmpRes[0] + tmpRes[1] + tmpRes[2] + tmpRes[3];
		}
	}

	return tmp;
}

vec4 mat4::operator*(const vec4& v) const {
	float32x4_t vec;
	float32x4_t col[4];

	float tmp[4]{ v.x, v.y, v.z, v.w };

	vec = vld1q_f32(tmp);

	LoadRows(col);

	float32x4_t res = vmulq_f32(vec, col[0]);

	for (int i = 1; i < 4; i++) {
#ifdef __aarch64__
		res = vfmaq_f32(res, vec, col[i]);
#else
		res = vaddq_f32(vmulq_f32(vec, col[i]), res);
#endif
	}

	vst1q_f32(tmp, res);

	return vec4(tmp[0], tmp[1], tmp[2], tmp[3]);
}

vec3 mat4::operator*(const vec3& v) const {

	float32x4_t vec;
	float32x4_t col[4];

	float tmp[4]{ v.x, v.y, v.z, 1 };

	vec = vld1q_f32(tmp);

	LoadRows(col);

	float32x4_t res = vmulq_f32(vec, col[0]);

	for (int i = 1; i < 4; i++) {
#ifdef __aarch64__
		res = vfmaq_f32(res, vec, col[i]);
#else
		res = vaddq_f32(vmulq_f32(vec, col[i]), res);
#endif
	}

	vst1q_f32(tmp, res);

	return vec3(tmp[0], tmp[1], tmp[2]);
}

#else

mat4 mat4::operator*(const mat4& r) const {
	float tmp[16];

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			tmp[x + y * 4] = m[x + 0 * 4] * r.m[0 + y * 4] +
				m[x + 1 * 4] * r.m[1 + y * 4] +
				m[x + 2 * 4] * r.m[2 + y * 4] +
				m[x + 3 * 4] * r.m[3 + y * 4];
		}
	}

	return mat4(tmp);
}

vec4 mat4::operator*(const vec4& v) const {

	float x = m[0 + 0 * 4] * v.x + m[0 + 1 * 4] * v.y + m[0 + 2 * 4] * v.z + m[0 + 3 * 4] * v.w;
	float y = m[1 + 0 * 4] * v.x + m[1 + 1 * 4] * v.y + m[1 + 2 * 4] * v.z + m[1 + 3 * 4] * v.w;
	float z = m[2 + 0 * 4] * v.x + m[2 + 1 * 4] * v.y + m[2 + 2 * 4] * v.z + m[2 + 3 * 4] * v.w;
	float w = m[3 + 0 * 4] * v.x + m[3 + 1 * 4] * v.y + m[3 + 2 * 4] * v.z + m[3 + 3 * 4] * v.w;

	return vec4(x, y, z, w);
}

vec3 mat4::operator*(const vec3& v) const {
	float x = m[0 + 0 * 4] * v.x + m[0 + 1 * 4] * v.y + m[0 + 2 * 4] * v.z + m[0 + 3 * 4] * 1;
	float y = m[1 + 0 * 4] * v.x + m[1 + 1 * 4] * v.y + m[1 + 2 * 4] * v.z + m[1 + 3 * 4] * 1;
	float z = m[2 + 0 * 4] * v.x + m[2 + 1 * 4] * v.y + m[2 + 2 * 4] * v.z + m[2 + 3 * 4] * 1;
	float w = m[3 + 0 * 4] * v.x + m[3 + 1 * 4] * v.y + m[3 + 2 * 4] * v.z + m[3 + 3 * 4] * 1;
	
	return vec3(x, y, z);
}

#endif

}


#ifndef MATH_H_INCLUDE_GUARD
#define MATH_H_INCLUDE_GUARD

#include <cmath>

struct vec3 {
	long double x;
	long double y;
	long double z;
}

vec3 operator+(const vec3& a, const vec3& b) {
	vec3 res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return res;
}

vec3 operator-(const vec3& a, const vec3& b) {
	vec3 res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return res;
}

vec3 operator*(long double k, const vec3& a) {
	vec3 res;
	res.x = k * a.x;
	res.y = k * a.y;
	res.z = k * a.z;
	return res;
}

inline long double magnitude(const vec3& a) {
	long double magsq;
	magsq = a.x * a.x + a.y * a.y + a.z * a.z;
	return std::sqrt(magsq);
}

inline vec3 normalize(const vec3& a) {
	long double mag = magnitude(a);
	long double unitscale = 1.0 / mag;
	vec3 res = unitscale * a;
}

#endif



#ifndef MATH_H_INCLUDE_GUARD
#define MATH_H_INCLUDE_GUARD

#include <cmath>

namespace vecmath {

struct vec3 {
	long double x;
	long double y;
	long double z;
};

constexpr vec3 zeroVec = {0.0, 0.0, 0.0};

inline vec3 operator+(const vec3& a, const vec3& b) {
	vec3 res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return res;
}

inline vec3 operator-(const vec3& a, const vec3& b) {
	vec3 res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return res;
}

inline vec3 operator*(long double k, const vec3& a) {
	vec3 res;
	res.x = k * a.x;
	res.y = k * a.y;
	res.z = k * a.z;
	return res;
}

inline long double sqMagnitude(const vec3& a) {
	long double magsq;
	magsq = a.x * a.x + a.y * a.y + a.z * a.z;
	return magsq;
}

inline long double magnitude(const vec3& a) {
	return std::sqrt(sqMagnitude(a));
}

inline vec3 normalize(const vec3& a) {
	long double mag = magnitude(a);
	long double unitscale = 1.0 / mag;
	vec3 res = unitscale * a;
}

inline vec3 cross(const vec3& a, const vec3& b) {
	vec3 res;
	res.x = a.y * b.z - a.z * b.y;
	res.y = - a.x * b.z + a.z * b.x;
	res.z = a.x * b.y - a.y * b.x;
	return res;
}

}

#endif



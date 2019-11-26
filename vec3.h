#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <vector>
#include <iostream>

class vec3
{
public:
	float v[3];
	vec3(){}
	vec3(float x, float y, float z) { v[0] = x; v[1] = y; v[2] = z; }
	inline float x() const { return v[0]; }
	inline float y() const { return v[1]; }
	inline float z() const { return v[2]; }
	inline float r() const { return v[0]; }
	inline float g() const { return v[1]; }
	inline float b() const { return v[2]; }
	
	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]); }
	inline float operator[](int i) const { return v[i]; }
	inline float& operator[](int i) { return v[i]; }

	inline vec3& operator+=(const vec3 &v2);
	inline vec3& operator-=(const vec3 &v2);
	inline vec3& operator*=(const vec3 &v2);
	inline vec3& operator/=(const vec3 &v2);
	inline vec3& operator*=(const float &f);
	inline vec3& operator/=(const float &f);

	inline float length() const { return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); }
	inline float squared_length() const { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }
	inline void make_unit_vector();
};

inline void vec3::make_unit_vector()
{
	float k = length();
	v[0] /= k; v[1] /= k; v[2] /= k;
}
inline vec3& vec3::operator+=(const vec3 &v2)
{
	v[0] += v2.v[0]; v[1] += v2.v[1]; v[2] += v2.v[2];
	return *this;
}
inline vec3& vec3::operator-=(const vec3 &v2)
{
	v[0] -= v2.v[0]; v[1] -= v2.v[1]; v[2] -= v2.v[2];
	return *this;
}

inline vec3& vec3::operator*=(const vec3 &v2)
{
	v[0] *= v2.v[0]; v[1] *= v2.v[1]; v[2] *= v2.v[2];
	return *this;
}
inline vec3& vec3::operator/=(const vec3 &v2)
{
	v[0] /= v2.v[0]; v[1] /= v2.v[1]; v[2] /= v2.v[2];
	return *this;
}
inline vec3& vec3::operator*=(const float &f)
{
	v[0] *= f; v[1] *= f; v[2] *= f;
	return *this;
}
inline vec3& vec3::operator/=(const float &f)
{
	v[0] /= f; v[1] /= f; v[2] /= f;
	return *this;
}
inline std::istream& operator>>(std::istream& is, vec3 &v)
{
	is >> v.v[0] >> v.v[1] >> v.v[2];
	return is;
}
inline std::ostream& operator<<(std::ostream& os, vec3 &v)
{
	os << v.v[0] << v.v[1] << v.v[2];
	return os;
}
inline vec3 operator+(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1], v1.v[2] + v2.v[2]);
}
inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1], v1.v[2] - v2.v[2]);
}
inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.v[0] * v2.v[0], v1.v[1] * v2.v[1], v1.v[2] * v2.v[2]);
}
inline vec3 operator/(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.v[0] / v2.v[0], v1.v[1] / v2.v[1], v1.v[2] / v2.v[2]);
}

inline vec3 operator*(const vec3 &v1, const float &k )
{
	return vec3(v1.v[0] * k, v1.v[1] * k, v1.v[2] * k);
}
inline vec3 operator*(const float &k, const vec3 &v1)
{
	return vec3(v1.v[0] * k, v1.v[1] * k, v1.v[2] * k);
}
inline vec3 operator/(const vec3 &v1, const float &k)
{
	return vec3(v1.v[0] / k, v1.v[1] / k, v1.v[2] / k);
}
inline vec3 make_unit(vec3 v)
{
	return v / v.length();
}
inline float dot(const vec3 &v1, const vec3 &v2)
{
	return v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1],
		v1.v[2] * v2.v[0] - v1.v[0] * v2.v[2],
		v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0]);
}
#endif //VEC3H


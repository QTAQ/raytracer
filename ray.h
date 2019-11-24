#ifndef RAYH
#define RAYH
#include "geometry.h"
class ray
{
public:
	vec3 a;
	vec3 b;
	ray(){}
	ray(const vec3 &origin, const vec3 &direction) { a = origin; b = direction; }
	inline vec3 origin() const { return a; }
	inline vec3 direction() const { return b; }
	inline vec3 point_at_parameter(float t) { return a + b * t; }
};
#endif // !RAYH


#ifndef HITABLEH
#define HITABLEH
#include "ray.h"

struct hit_record
{
	float t;
	vec3 p;
	vec3 n;
};
class hitable
{
public:
	virtual bool hit(ray &r, float tmin, float tmax, hit_record &rec) const = 0;
};
#endif // !HITABLEH

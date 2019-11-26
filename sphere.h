#ifndef SPHEREH
#define SPHEREH
#include "hitable.h"
#include "material.h"
class sphere : public hitable
{
public:
	vec3 center;
	float radius;
	material *mat_ptr;
	sphere(){}
	sphere(vec3 v, float r,material *mptr) : center(v),radius(r),mat_ptr(mptr){}
	virtual bool hit(ray &r, float tmin, float tmax, hit_record &rec) const;
};

bool sphere::hit(ray &r, float tmin, float tmax, hit_record &rec) const
{
	vec3 B = r.direction(); vec3 oc = r.origin() - center;
	float a = dot(B, B);
	float b = dot(B, oc);
	float c = dot(oc, oc) - radius * radius;
	float delta = b * b - a*c;
	if (delta >= 0)
	{
		float temp = (-b - sqrt(delta)) / (a); //closeat t
		if (temp<tmax && temp>tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.n = make_unit(rec.p - center);
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(delta)) / (a);
		if (temp<tmax && temp>tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.n = make_unit(rec.p - center);
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}
#endif

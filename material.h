#ifndef MATERIALH
#define MATERIALH
#include "hitable.h"

vec3 random_in_unit_sphere()
{
	vec3 p;
	vec3 u(1.f, 1.f, 1.f);
	do
	{
		p = 2 * vec3(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f) - u;
	} while (p.squared_length() >= 1.f);
	return p;
}
//vec3 reflect(const vec3 &v, const vec3 &n)
//{
//	return 
//}
class material
{
public:
	material(){}
	virtual bool scatter(const ray &r_in, hit_record &rec, vec3 &attenuation, ray &scatter_ray) const = 0;
};

class lambertian : public material
{
public:
	lambertian(const vec3 &a) :albedo(a) {}
	virtual bool scatter(const ray &r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const
	{
		vec3 target = rec.p + rec.n + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
	vec3 albedo;
};
class metal : public material
{
public:
	metal(const vec3 &a) :albedo(a) {}
	virtual bool scatter(const ray &r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const
	{
		vec3 target = rec.p + rec.n + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
	vec3 albedo;
};



#endif // !MATERIALH

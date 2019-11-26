#ifndef MATERIALH
#define MATERIALH
#include "hitable.h"
#include "vec3.h"

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
vec3 reflect(const vec3 &v, const vec3 &n)
{
	return v - 2 * dot(v, n)*n;
}
bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted)
{
	vec3 uv = make_unit(v); vec3 un = make_unit(n);
	float cosine_i = dot(uv, un);
	float delta = 1.0f - ni_over_nt * ni_over_nt*(1.0f - cosine_i * cosine_i); //sin_t*sin_t
	if (delta > 0)
	{
		refracted = ni_over_nt * (uv + un * cosine_i) - un * sqrt(delta);
		return true;
	}
	return false;
}
float schlick(float cosine, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
}
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
	metal(const vec3 &a,float f) :albedo(a) 
	{
		fuzz = (f < 1) ? f : 1;
	}
	virtual bool scatter(const ray &r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const
	{
		vec3 reflected = reflect(make_unit(r_in.direction()), make_unit(rec.n));
		scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return (dot(rec.n,scattered.direction())>0);
	}
	vec3 albedo;
	float fuzz;
};
class dielectric : public material
{
public:
	dielectric(float r) :ref_idx(r)
	{
	}
	virtual bool scatter(const ray &r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const
	{
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.n);
		float ni_over_nt;
		attenuation = vec3(1.0,1.0,1.0);
		vec3 refracted;


		float reflect_prob;
		float cosine;
		if (dot(r_in.direction(), rec.n) > 0) //介质内的光线
		{
			outward_normal = -rec.n;
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r_in.direction(), rec.n) / r_in.direction().length();
		}
		else
		{
			outward_normal = rec.n;
			ni_over_nt = 1.0f/ref_idx;
			cosine = -dot(r_in.direction(), rec.n) / r_in.direction().length();
		}
		if ((refract(r_in.direction(), outward_normal, ni_over_nt, refracted)))
		{
			reflect_prob = schlick(cosine, ref_idx);
		}
		else
		{
			reflect_prob = 1.0f;
		}
		if (rand() % 100 / 100.0f < reflect_prob)
		{
			scattered = ray(rec.p, reflected);
		}
		else
		{
			scattered = ray(rec.p, refracted);
		}
		return true;
	}
	float ref_idx;
};

#endif // !MATERIALH

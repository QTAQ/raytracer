#ifndef CAMERAH
#define CAMERAH
#define M_PI 3.1415926f
#include "ray.h"
double arandom_double()
{
	return rand() % 100 / 100.0f;
}
vec3 random_in_unit_disk()
{
	vec3 p;
	do
	{
		p = 2.0*vec3(arandom_double(), arandom_double(), 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}

class camera
{
public:
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist)
	{
		// vfov is top to bottom in degrees
		lens_radius = aperture / 2;
		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = make_unit(lookfrom - lookat);
		u = make_unit(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = origin - half_width * focus_dist*u - half_height * focus_dist*v - focus_dist * w;
		horizontal = 2 * half_width*focus_dist*u;
		vertical = 2 * half_height*focus_dist*v;
	}
	ray get_ray(float s, float t)
	{
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
	}

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	float lens_radius;
};
//class camera
//{
//public:
//	camera(vec3 lookfrom, vec3 lookat, vec3 up, float fov, float aspect,float apt,float focus_dist)
//	{
//		vec3 u, v, w;
//		float theta = fov * 3.1415926f / 180;
//		float half_height = tan(theta / 2);
//		float half_width = half_height * aspect;
//		origin = lookfrom;
//		w = make_unit(lookfrom - lookat);
//		u = make_unit(cross(up, w));
//		v = cross(w, u);
//		lower_left_corner = origin  - half_height * v - half_width * u - w;
//		horizontal = 2 * half_width*u;
//		vertical = 2 * half_height*v;
//	}
//	ray get_ray(float a, float b)
//	{
//		return ray(origin, lower_left_corner + a * horizontal + b * vertical - origin);
//	}
//
//	vec3 lower_left_corner;
//	vec3 horizontal;
//	vec3 vertical;
//	vec3 origin;
//
//};

#endif //!CAMERAH
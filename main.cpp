#include "ray.h"
#include<fstream>
using namespace std;
const int width = 200;
const int height = 100;
bool hit(const vec3 &center, float R, const ray &r)
{
	vec3 B = r.direction(); vec3 oc = r.origin()-center;
	float a = dot(B, B);
	float b = 2 * dot(B, oc);
	float c = dot(oc, oc) - R * R;

	return (b*b - 4 * a*c > 0);
}
vec3 color(const ray &r)
{
	if (hit(vec3(0, 0, -1), 0.5f, r)) return vec3(0.5,0.9,0.9);
	vec3 unit = make_unit(r.direction());
	float t = 0.5f*(unit.y() + 1.0f);
	return (1.f - t)*vec3(1.f, 1.f, 1.f) + t * vec3(0.5f, 0.7f, 1.f);
}
void render()
{
	ofstream of(".\\out.ppm");
	of << "P3" << endl << width << " " << height << endl << 255 << endl;
	vec3 lower_left_corner(-2, -1, -1);
	vec3 horizontal(4, 0, 0);
	vec3 vertical(0, 2, 0);
	vec3 origin(0, 0, 0);
	for (int y = height-1; y >= 0; --y)
	{
		for (int x = 0; x < width; ++x)
		{
			float u = (float)x / (float)width; float v = (float)y / (float)height;
			ray r(origin, lower_left_corner + v * vertical + u * horizontal);
			vec3 clr = color(r);
			int ir = (int)(255.99f*clr[0]);
			int ig = (int)(255.99f*clr[1]);
			int ib = (int)(255.99f*clr[2]);
			of << ir << " " << ig << " " << ib << endl;
		}
	}
	of.close();
}

int main()
{
	render();
	return 0;
}

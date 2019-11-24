#include "hitable_list.h"
#include "sphere.h"
#include "float.h"
#include<fstream>
using namespace std;
const int width = 200;
const int height = 100;
vec3 color(ray &r, hitable *world)
{
	hit_record rec;
	if (world->hit(r,0.0,FLT_MAX,rec))
	{
		return 0.5*vec3(rec.n[0] + 1.0f, rec.n[1] + 1.0f, rec.n[2] + 1.0f);
	}
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
	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5f);
	list[1] = new sphere(vec3(0, -100.5f, -1), 100.0f);
	hitable *world = new hitable_list(list, 2);
	for (int y = height-1; y >= 0; --y)
	{
		for (int x = 0; x < width; ++x)
		{
			float u = (float)x / (float)width; float v = (float)y / (float)height;
			ray r(origin, lower_left_corner + v * vertical + u * horizontal);
			vec3 clr = color(r,world);
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

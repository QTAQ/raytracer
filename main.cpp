#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include<fstream>
using namespace std;
const int width = 200;
const int height = 100;
const int ns = 100;

vec3 color(ray &r, hitable *world,int depth)
{
	hit_record rec;
	if (world->hit(r,0.00001f,FLT_MAX,rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else return vec3(0, 0, 0);
	}
	vec3 unit = make_unit(r.direction());
	float t = 0.5f*(unit.y() + 1.0f);
	return (1.f - t)*vec3(1.f, 1.f, 1.f) + t * vec3(0.5f, 0.7f, 0.1f);
}
void render()
{
	ofstream of(".\\out.ppm");
	of << "P3" << endl << width << " " << height << endl << 255 << endl;
	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5f,new lambertian(vec3(0.8,0.3,0.8)));
	list[1] = new sphere(vec3(0, -100.5f, -1), 100.0f, new lambertian(vec3(0.3, 0.5, 0.8)));
	hitable *world = new hitable_list(list, 2);
	camera cam;
	for (int y = height-1; y >= 0; --y)
	{
		for (int x = 0; x < width; ++x)
		{
			vec3 clr(0, 0, 0);
			for (int i = 0; i < ns; ++i)
			{
				float u = ((float)x+ rand() % 100 / 100.0f)/ (float)width; 
				float v = ((float)y+ rand() % 100 / 100.0f)/ (float)height;
				ray r = cam.get_ray(u,v);
				clr += color(r, world,0);
			}
			clr /= ns;
			int ir = (int)(255.99f*(sqrt(clr[0])));
			int ig = (int)(255.99f*(sqrt(clr[1])));
			int ib = (int)(255.99f*(sqrt(clr[2])));
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

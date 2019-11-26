#include <fstream>
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"



const int width = 1200;
const int height = 800;
const int ns = 10;
double random_double()
{
	return rand() % 100 / 100.0f;
}
hitable *random_scene()
{
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = random_double();
			vec3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (choose_mat < 0.8)
				{  // diffuse
					list[i++] = new sphere(
						center, 0.2,
						new lambertian(vec3(random_double()*random_double(),
							random_double()*random_double(),
							random_double()*random_double()))
					);
				}
				else if (choose_mat < 0.95)
				{ // metal
					list[i++] = new sphere(
						center, 0.2,
						new metal(vec3(0.5*(1 + random_double()),
							0.5*(1 + random_double()),
							0.5*(1 + random_double())),
							0.5*random_double())
					);
				}
				else
				{  // glass
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new hitable_list(list, i);
}
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
	return (1.f - t)*vec3(1.f, 1.f, 1.f) + t * vec3(0.5f, 0.7f, 1.0f);
}
void render()
{
	std::ofstream of(".\\out.ppm");
	of << "P3" << std::endl << width << " " << height << std::endl << 255 << std::endl;
	hitable *world = random_scene();
	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;
	camera cam(lookfrom, lookat, vec3(0.f, 1.f, 0.f), 90.f,(float)width/(float)height,aperture,dist_to_focus);
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
			of << ir << " " << ig << " " << ib << std::endl;
		}
	}
	of.close();
}

int main()
{
	render();
	return 0;
}

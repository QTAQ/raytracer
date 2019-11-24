#ifndef HITABLE_LISTH
#define HITABLE_LISTH
#include "hitable.h"

class hitable_list : public hitable
{
public:
	hitable **list;
	int size;
	hitable_list(){}
	hitable_list(hitable **l, int n): list(l),size(n){}
	virtual bool hit(ray &r, float tmin, float tmax, hit_record &rec) const;
};

bool hitable_list::hit(ray &r, float tmin, float tmax, hit_record &rec) const
{
	hit_record tmp_rec;
	bool hitted = false;
	float closest_so_far = tmax;
	for (int i = 0; i < size; ++i)
	{
		if (list[i]->hit(r, tmin, closest_so_far, tmp_rec))
		{
			hitted = true;
			closest_so_far = tmp_rec.t;
			rec = tmp_rec;
		}
	}
	return hitted;
}


#endif // !HITABLE_LISTH

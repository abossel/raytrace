#include "raytrace.h"

t_hit	disk_hit(t_ray *r, t_v3 d_centre, t_v3 d_normal, float d_radius)
{
	t_hit	h;
	t_v3    rv;

	h = plane_hit(r, d_centre, d_normal);
	if (h.hit)
	{
		rv = v3sub(h.point, d_centre);
		if (v3dot(rv, rv) > d_radius * d_radius)
			h.hit = 0;
	}
	return (h);
}

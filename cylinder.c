#include "raytrace.h"

/*
 * set the cylinder texture coordinates
 * make a normal from the centre to the hit point to set u and v like a sphere
 */
void    cylinder_texture_uv(t_hit *h, t_v3 c_centre, t_v3 c_direction)
{
	t_v3    normal;
	t_v3    axis;
	float   angle;

	axis = v3norm(v3cross(v3new(0.0f, 0.0f, 1.0f), c_direction));
	angle = acos(v3dot(v3new(0.0f, 0.0f, 1.0f), c_direction));
	normal = v3norm(v3sub(h->point, c_centre));
	normal = v3rot_axis(normal, axis, -angle);
	h->u = (1.0f + atan2(normal.y, normal.x) / M_PI) * 0.5f;
	h->v = acosf(normal.z) / M_PI;
}

t_hit	cylinder_hit(t_ray *r, t_v3 c_centre, t_v3 c_direction, float c_radius, float c_height)
{
	float	limit2;
	float	hh;
	t_v3	vhh;
	t_v3	vpoint;
	t_hit	h;

	hh = c_height / 2.0f;
	vhh = v3scale(c_direction, hh);
	if (v3dot(c_direction, r->direction) < 0.0f)
	{
		h = disk_hit(r, v3add(c_centre, vhh), c_direction, c_radius);
		if (h.hit)
		{
			cylinder_texture_uv(&h, c_centre, c_direction);
			return (h);
		}
	}
	if (v3dot(v3neg(c_direction), r->direction) < 0.0f)
	{
		h = disk_hit(r, v3sub(c_centre, vhh), v3neg(c_direction), c_radius);
		if (h.hit)
		{
			cylinder_texture_uv(&h, c_centre, c_direction);
			return (h);
		}
	}
	h = tube_hit(r, c_centre, c_direction, c_radius);
	if (h.hit)
	{
		limit2 = c_radius * c_radius + hh * hh;
		vpoint = v3sub(h.point, c_centre);
		if (v3dot(vpoint, vpoint) <= limit2)
		{
			cylinder_texture_uv(&h, c_centre, c_direction);
			return (h);
		}
	}
	h.hit = 0;
	return (h);
}


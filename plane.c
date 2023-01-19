#include "raytrace.h"

/*
 * set the plane texture coordinates
 * planes are infinite so the texture repeats every 10 units
 * rotate the plane to point to +z then use the x and y for u and v
 * if x or y is negative invert the u or v
 */
void	plane_texture_uv(t_hit *h, t_v3 p_centre, t_v3 p_normal)
{
	t_v3	axis;
	float	angle;
	t_v3	pplane;

	axis = v3norm(v3cross(v3new(0.0f, 0.0f, 1.0f), p_normal));
	angle = acos(v3dot(v3new(0.0f, 0.0f, 1.0f), p_normal));
	pplane = v3rot_axis(v3sub(h->point, p_centre), axis, -angle);
	h->u = fmodf(fabs(pplane.x), 10.0f) / 10.0f;
	if (pplane.x < 0.0f)
		h->u = 1.0f - h->u;
	h->v = fmodf(fabs(pplane.y), 10.0f) / 10.0f;
	if (pplane.y < 0.0f)
		h->v = 1.0f - h->v;
}


/*
 * check if a ray hits a plane
 * returns t_hit.hit = 1 if hit otherwise 0
 */
t_hit	plane_hit(t_ray *r, t_v3 p_centre, t_v3 p_normal)
{
	float	denom;
	t_hit	h;

	h.hit = 0;
	denom = v3dot(p_normal, r->direction);
	if (fabs(denom) > 0.001f)
		h.distance = v3dot(v3sub(p_centre, r->origin), p_normal) / denom;
	if (h.distance < 0.001f)
		return (h);
	h.hit = 1;
	h.point = v3add(v3scale(r->direction, h.distance), r->origin);
	h.normal = p_normal;
	plane_texture_uv(&h, p_centre, p_normal);
	return (h);
}

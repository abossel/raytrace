#include "raytrace.h"

void	sphere_texture_uv(t_hit *h)
{
	h->u = (1.0f + atan2(h->normal.y, h->normal.x) / M_PI) * 0.5f;
	h->v = acosf(h->normal.z) / M_PI;
}

/*
 * check if a ray hits a sphere
 * returns the intersection information in a t_hit
 * t_hit.hit is 1 if no intersection
 */
t_hit	sphere_hit(t_ray *r, t_v3 s_centre, float s_radius)
{
	t_v3	L;
	t_v3	Q;
	t_v3	S;
	t_hit	h;

	h.hit = 0;
	L = v3sub(r->origin, s_centre);
	Q.v[0] = v3dot(r->direction, r->direction);
	Q.v[1] = 2.0f * v3dot(r->direction, L);
	Q.v[2] = v3dot(L, L) - (s_radius * s_radius);
	S = v3solve_quad(Q.v[0], Q.v[1], Q.v[2]);
	if (S.v[0] == 0.0f || S.v[1] < 0.0f || S.v[2] < 0.0f)
		return (h);
	h.hit = 1;
	h.distance = S.v[1];
	h.point = v3add(v3scale(r->direction, h.distance), r->origin);
	h.normal = v3norm(v3sub(h.point, s_centre));
	sphere_texture_uv(&h);
	return (h);
}

#include "raytrace.h"
#include "vector3.h"
#include <math.h>

void	tube_texture_uv(t_hit *h)
{
	h->u = (1.0f + atan2(h->normal.y, h->normal.x) / M_PI) * 0.5f;
	h->v = acosf(h->normal.z) / M_PI;
}

t_hit	tube_hit(t_ray *r, t_v3 t_centre, t_v3 t_direction, float t_radius)
{
	t_v3    L;
	t_v3    Q;
	float   t1;
	float   t2;
	t_hit	h;
	float	m;

	h.hit = 0;
	L = v3sub(r->origin, t_centre);
	t1 = v3dot(r->direction, t_direction);
	t2 = v3dot(L, t_direction);
	Q.v[0] = v3dot(r->direction, r->direction) - t1 * t1;
	Q.v[1] = 2.0f * (v3dot(r->direction, L) - t1 * t2);
	Q.v[2] = v3dot(L, L) - t2 * t2 - t_radius * t_radius;
	Q = v3solve_quad(Q.v[0], Q.v[1], Q.v[2]);
	if (Q.v[0] == 0.0f || Q.v[1] < 0.01f || Q.v[2] < 0.01f)
		return (h);
	h.hit = 1;
	h.distance = Q.v[1];
	h.point = v3add(v3scale(r->direction, h.distance), r->origin);
	m = v3dot(r->direction, t_direction) * h.distance + v3dot(L, t_direction);
	h.normal = v3norm(v3sub(v3sub(h.point, t_centre), v3scale(t_direction, m)));
	tube_texture_uv(&h);
	return (h);
}

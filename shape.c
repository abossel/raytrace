#include "raytrace.h"
#include <float.h>

/*
 * get shape intersection information
 * the information is returned in a t_hit
 */
t_hit	shape_hit(t_ray *r, t_obj *s)
{
	t_hit	h;

	h.hit = 0;
	if (s->type == T_SPHERE)
		h = sphere_hit(r, s->origin, s->radius);
	else if (s->type == T_PLANE)
		h = plane_hit(r, s->origin, s->direction);
	else if (s->type == T_TUBE)
		h = tube_hit(r, s->origin, s->direction, s->radius);
	else if (s->type == T_CYLINDER)
		h = cylinder_hit(r, s->origin, s->direction, s->radius, s->height);
	return (h);
}

/*
 * find the shape closest to the ray
 * returns a pointer to the closest shape from the ray r
 * returns NULL if no shape found
 */
t_obj	*find_shape(t_env *env, t_ray *r)
{
	float	min_dist;
	t_obj	*shape;
	t_hit	h;
	int		i;

	i = 0;
	shape = NULL;
	min_dist = FLT_MAX;
	while (env->objects[i] != NULL)
	{
		if (env->objects[i]->type != T_LIGHT)
		{
			h = shape_hit(r, env->objects[i]);
			if (h.hit && h.distance < min_dist)
			{
				min_dist = h.distance;
				shape = env->objects[i];
			}
		}
		i++;
	}
	return (shape);
}

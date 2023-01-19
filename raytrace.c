#include "raytrace.h"
#include "vector3.h"
#include "mlx_render.h"
#include <string.h>

int	cast_ray(t_env *env, t_ray *r);

int	mirror_ray(t_env *env, t_ray *r, t_obj *shape)
{
	t_ray	reflect_ray;
	t_hit	h;

	h = shape_hit(r, shape);
	reflect_ray.direction = v3reflect(r->direction, h.normal);
	reflect_ray.origin = h.point;
	return (cast_ray(env, &reflect_ray));
}

int	light_ray(t_env *env, t_ray *r, t_obj *shape)
{
	float	intensity;
	t_v3	colour;
	t_v3	light_dir;
	t_hit	h;
	t_mat	m;
	int		i;

	h = shape_hit(r, shape);
	m = get_material(shape->material);
	colour = v3scale(env->ambient.colour, env->ambient.bright * m.ambient);
	if (strncmp(shape->material, "check", 13) == 0 && checkerboard_black(&h, 10.0f))
		colour = reflect_colour(v3zero(), colour);
	else
		colour = reflect_colour(shape->colour, colour);
	if (strncmp(shape->material, "bumpy", 6) == 0)
		h.normal = v3norm(v3add(h.normal, v3rot_rel(bumpmap_normal(&h), v3unitz(), h.normal)));
	i = 0;
	while (env->objects[i] != NULL)
	{
		if (env->objects[i]->type == T_LIGHT && light_hit(env, h.point, env->objects[i]))
		{
			light_dir = v3norm(v3sub(h.point, env->objects[i]->origin));
			intensity = phong_lighting(r, &h, &m, light_dir);
			colour = v3add(colour, reflect_colour(shape->colour,
				v3scale(env->objects[i]->colour, intensity)));
		}
		i++;
	}
	return (v3toirgb(colour));
}

int	cast_ray(t_env *env, t_ray *r)
{
	t_obj	*shape;

	shape = find_shape(env, r);
	if (shape != NULL)
	{
		if (strncmp(shape->material, "mirror", 7) == 0)
			return (mirror_ray(env, r, shape));
		return (light_ray(env, r, shape));
	}
	return (rgb(0, 0, 0));
}

/*
 * raytrace a scene
 * default camera orientation (0, 0, 0)
 * +y axis is forward
 * +x axis is right
 * +z axis is up
 * values go from -1 to 1 (-180 to 180 deg) or (-pi to pi rad)
 * direction.z is inverted because in screen y coordinates are inverted
 */
void raytrace(t_app *app, t_env *env)
{
	float	fov;
	t_ray	r;
	t_v3	axis;
	float	angle;
	int		p;

	if (env->fov >= 180.0f)
		env->fov = 179.9f;
	axis = v3norm(v3cross(v3new(0.0f, 0.0f, -1.0f), env->cam.direction));
	angle = acos(v3dot(v3new(0.0f, 0.0f, -1.0f), env->cam.direction));
	fov = deg2rad(env->fov);
	p = 0;
	while (p < app->width * app->height)
	{
		r.origin = env->cam.origin;
		r.direction.x = (p % app->width + 0.5f) - app->width / 2.0f;
		r.direction.y = -(p / app->width + 0.5f) + app->height / 2.0f;
		r.direction.z = -app->height / (2.0f * tan(fov / 2.0f));
		r.direction = v3rot_axis(r.direction, axis, angle);
		r.direction = v3norm(r.direction);
		pixel_put(app->screen, p % app->width, p / app->width,
			cast_ray(env, &r));
		p++;
	}
	app->render = 1;
}

#include "mlx_render.h"
#include "raytrace.h"
#include <string.h>

void	set_sphere(t_obj *s, t_v3 origin, float radius, t_v3 colour, char *material)
{
	s->type = T_SPHERE;
	s->origin = origin;
	s->radius = radius;
	s->colour = colour;
	strlcpy(s->material, material, RT_MAT_SIZE);
}

void	set_plane(t_obj *s, t_v3 origin, t_v3 direction, t_v3 colour, char *material)
{
	s->type = T_PLANE;
	s->origin = origin;
	s->direction = direction;
	s->colour = colour;
	strlcpy(s->material, material, RT_MAT_SIZE);
}

void	set_tube(t_obj *s, t_v3 origin, t_v3 direction, float radius, t_v3 colour, char *material)
{
	s->type = T_TUBE;
	s->origin = origin;
	s->direction = direction;
	s->radius = radius;
	s->colour = colour;
	strlcpy(s->material, material, RT_MAT_SIZE);
}

void	set_cylinder(t_obj *s, t_v3 origin, t_v3 direction, float radius, float height, t_v3 colour, char *material)
{
	s->type = T_CYLINDER;
	s->origin = origin;
	s->direction = direction;
	s->radius = radius;
	s->height = height;
	s->colour = colour;
	strlcpy(s->material, material, RT_MAT_SIZE);
}

void	set_camera(t_obj *c, t_v3 origin, t_v3 direction)
{
	c->type = T_CAMERA;
	c->origin = origin;
	c->direction = direction;
	c->material[0] = '\0';
}

void	set_light(t_obj *l, t_v3 origin, float bright, t_v3 colour)
{
	l->type = T_LIGHT;
	l->origin = origin;
	l->bright = bright;
	l->colour = colour;
	l->material[0] = '\0';
}

#define MAX_OBJS 12

int	main(void)
{
	t_app	app;
	t_env	env;
	t_obj	objs[MAX_OBJS];
	t_obj	*objp[MAX_OBJS + 1];
	int		i;

	set_sphere(&objs[0], v3new(2, 10, 0), 2.5, v3new(255, 0, 0), "glass");
	set_sphere(&objs[1], v3new(-2, 14, 0), 2.5, v3new(0, 128, 255), "mirror");
	set_sphere(&objs[2], v3new(7, 12, 0), 2.5, v3new(255, 128, 0), "bumpy");
	set_sphere(&objs[3], v3new(-2, 8, 3), 0.5, v3new(255, 0, 0), "glass");
	set_sphere(&objs[4], v3new(0, 8, 3), 0.5, v3new(0, 255, 0), "glass");
	set_sphere(&objs[5], v3new(2, 8, 3), 0.5, v3new(0, 0, 255), "glass");
	set_cylinder(&objs[6], v3new(-7, 12, 0), v3norm(v3new(0, -0.7, 0.7)), 2.5, 3, v3new(0, 255, 0), "check");
	set_plane(&objs[7], v3new(0, 20, 0), v3new(0, -1, 0), v3new(255, 255, 255), "glass");
	set_plane(&objs[8], v3new(0, 0, -5), v3new(0, 0, 1), v3new(255, 128, 255), "check");
	set_plane(&objs[9], v3new(0, 0, 50), v3new(0, 0, -1), v3new(115, 215, 255), "paper");
	set_light(&objs[10], v3new(0, 5, 20), 0.7, v3new(0, 255, 255));
	set_light(&objs[11], v3new(30, 5, 20), 0.7, v3new(255, 255, 0));
	i = 0;
	while (i < MAX_OBJS)
	{
		objp[i] = &objs[i];
		objp[i + 1] = NULL;
		i++;
	}
	set_camera(&env.cam, v3new(0, 0, 0), v3new(0, 1, 0));
	set_light(&env.ambient, v3new(0, 0, 0), 0.5, v3new(255, 255, 255));
	env.fov = 70;
	env.objects = objp;
	app.data = (void *)&env;
	app.render = 1;
	gfx_main(&app);
	return (0);
}

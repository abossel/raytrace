#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "mlx_render.h"
# include "vector3.h"
# include <stddef.h>
# include <math.h>

# define RT_MAT_SIZE 128

# define T_CAMERA 1
# define T_LIGHT 2
# define T_AMBIENT 3
# define T_DIFFUSE 4
# define T_PHONG 5
# define T_MIRROR 6
# define T_SPHERE 7
# define T_PLANE 8
# define T_DISK 9
# define T_TUBE 10
# define T_CYLINDER 11

typedef struct s_ray
{
	t_v3	origin;
	t_v3	direction;
}	t_ray;

typedef struct s_hit
{
	int		hit;
	float	distance;
	t_v3	point;
	t_v3	normal;
	float	u;
	float	v;
}	t_hit;

typedef struct s_mat
{
	int		type;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shine;
}	t_mat;

typedef struct s_obj
{
	int		type;
	t_v3	origin;
	t_v3	direction;
	float	radius;
	float	height;
	t_v3	colour;
	float	bright;
	char	material[RT_MAT_SIZE];
}	t_obj;

typedef struct s_env
{
	t_obj	cam;
	float	fov;
	t_obj	ambient;
	t_obj	**objects;
}	t_env;

void 	raytrace(t_app *app, t_env *env);

t_hit	sphere_hit(t_ray *r, t_v3 s_centre, float s_radius);
t_hit	plane_hit(t_ray *r, t_v3 p_centre, t_v3 p_normal);
t_hit	tube_hit(t_ray *r, t_v3 t_centre, t_v3 t_direction, float t_radius);
t_hit	disk_hit(t_ray *r, t_v3 d_centre, t_v3 d_normal, float d_radius);
t_hit	cylinder_hit(t_ray *r, t_v3 c_centre, t_v3 c_direction, float c_radius, float c_height);

t_obj	*find_shape(t_env *env, t_ray *r);
t_hit	shape_hit(t_ray *r, t_obj *s);

float	phong_lighting(t_ray *r, t_hit *h, t_mat *m, t_v3 light_dir);
float	diffuse_lighting(t_hit *h, t_mat *m, t_v3 light_dir);
int		light_hit(t_env *env, t_v3 point, t_obj *l);
t_v3	reflect_colour(t_v3 colour, t_v3 light);

t_mat   get_material(char *name);

int		checkerboard_black(t_hit *h, float scale);
float   perlin_tiling(float x, float y, int octaves);
float	perlin(float x, float y, int octaves);
t_v3	bumpmap_normal(t_hit *h);

float	noise2(float x, float y);

#endif

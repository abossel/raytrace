#include "raytrace.h"
#include <string.h>

t_mat   get_mat_glass()
{
    t_mat   m;

    m.specular = 1.5f;
	m.diffuse = 0.7f;
	m.ambient = 0.5f;
	m.shine = 125.0f;
    return (m);
}

t_mat   get_mat_paper()
{
    t_mat   m;

    m.specular = 0.0f;
	m.diffuse = 0.7f;
	m.ambient = 0.5f;
	m.shine = 0.0f;
    return (m);
}

t_mat   get_material(char *name)
{
    if (strncmp("glass", name, 6) == 0)
        return (get_mat_glass());
    if (strncmp("paper", name, 6) == 0)
        return (get_mat_paper());
    if (strncmp("check", name, 6) == 0)
        return (get_mat_paper());
    if (strncmp("bumpy", name, 6) == 0)
        return (get_mat_glass());
    return (get_mat_glass());
}
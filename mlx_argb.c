#include "mlx_render.h"

int	argb(int a, int r, int g, int b)
{
	return ((a & 0xff) << 24 | (r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff));
}

int	rgb(int r, int g, int b)
{
	return ((r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff));
}

int	get_r(int argb)
{
	return ((argb >> 16) & 0xff);
}

int	get_g(int argb)
{
	return ((argb >> 8) & 0xff);
}

int	get_b(int argb)
{
	return (argb & 0xff);
}

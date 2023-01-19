#include "mlx.h"
#include "mlx_events.h"
#include "mlx_render.h"
#include <stdlib.h>
#include "raytrace.h"

int	render(t_app *app)
{
	t_env	*env;

	env = (t_env *)app->data;
	if (app->render)
	{
		raytrace(app, env);
		mlx_put_image_to_window(app->mlx, app->win, app->screen->image, 0, 0);
		app->render = 0;
	}
	return (0);
}

int	mouse(int button, int x, int y, t_app *app)
{
	if (x >= 0 && y >= 0 && x < app->width && y < app->height)
	{
		if (button == MOUSE_CLICK_LEFT)
			;
	}
	if (app)
		;
	return (0);
}

int	keypress(int keycode, t_app *app)
{
	if (keycode == KEY_ESCAPE)
		destroy(app);
	app->render = 0;
	return (0);
}

int	destroy(t_app *app)
{
	gfx_free(app, app->screen);
	exit(EXIT_SUCCESS);
	return (0);
}

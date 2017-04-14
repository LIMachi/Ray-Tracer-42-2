#include <rt.h>

void		filter_sepia(t_env *e, int keycode)
{
	keycode = keycode + 32;
	e->glfw.render->params[2].needs_update = 1;
	e->argn.filter = 1;
}

void		filter_cartoon(t_env *e, int keycode)
{
	keycode = keycode + 32;
	e->glfw.render->params[2].needs_update = 1;
	e->argn.filter = 3;
}

void		filter_gray(t_env *e, int keycode)
{
	keycode = keycode + 32;
	e->glfw.render->params[2].needs_update = 1;
	e->argn.filter = 2;
}

void		filter_none(t_env *e, int keycode)
{
	keycode = keycode + 32;
	e->glfw.render->params[2].needs_update = 1;
		e->argn.filter = 0;
}
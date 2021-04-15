//
// Created by Demeter Xhoan on 4/15/21.
//
#include "miniRT.h"
#define SS_MULTIPLIER 4
#define SS_MAX 1000
#define SS_MIN 0.25f

enum e_direction {
	PREV = 43,
	NEXT = 47
};

enum e_scale {
	CLOSER = 24,
	FURTHER = 27
};

enum e_wasd {
	LEFT,
	BACKWARD,
	RIGHT,
	FORWARD = 13,
	DOWN = 125,
	UP
};

enum e_sign {
	MINUS,
	PLUS
};

int	change_camera(t_all *scene, enum e_direction direction)
{
	if (scene->cameras->next == NULL || scene->cameras->prev == NULL)
		return (-1);
	if (direction == NEXT)
		scene->cameras = scene->cameras->next;
	if (direction == PREV)
		scene->cameras = scene->cameras->prev;
	render_scene(*scene, NULL);
	return (direction);
}

int	change_fov(t_all *scene, enum e_scale scale)
{
	if (scene == NULL || scene->cameras == NULL)
		return (-1);
	if (scale == FURTHER)
		scene->cameras->fov += 10;
	else if (scale == CLOSER)
		scene->cameras->fov -= 10;
	if (scene->cameras->fov > 179)
	{
		scene->cameras->fov = 179;
		printf("179 is MAX FOV\n\a");
		return (scale);
	}
	else if (scene->cameras->fov < 1)
	{
		scene->cameras->fov = 1;
		printf("1 in MIN FOV\n\a");
		return (scale);
	}
	render_scene(*scene, NULL);
	return (scale);
}

void	xz_transform(t_all *scene, t_vec trans, enum e_sign sign)
{
	if (sign == PLUS)
	{
		scene->cameras->point.x += trans.x * scene->step_size;
		scene->cameras->point.z += trans.z * scene->step_size;
	}
	else
	{
		scene->cameras->point.x -= trans.x * scene->step_size;
		scene->cameras->point.z -= trans.z * scene->step_size;
	}
}

int	change_point_of_camera(t_all *scene, enum e_wasd wasd)
{
	t_vec	left;

	if (wasd == FORWARD)
		xz_transform(scene, scene->cameras->orient, PLUS);
	if (wasd == BACKWARD)
		xz_transform(scene, scene->cameras->orient, MINUS);
	if (wasd == LEFT || wasd == RIGHT)
	{
		left = vector_norm(vecs_cross(scene->cameras->orient,
					create_vector(0, 1, 0)));
		if (wasd == LEFT)
			xz_transform(scene, left, PLUS);
		else
			xz_transform(scene, left, MINUS);
	}
	if (wasd == UP)
		scene->cameras->point.y += scene->step_size;
	if (wasd == DOWN)
		scene->cameras->point.y -= scene->step_size;
	render_scene(*scene, NULL);
	return (wasd);
}

int	key_hook(int keycode, t_all *scene)
{
	if (keycode == 53)
		window_close(scene);
	if (keycode == NEXT || keycode == PREV)
		return (change_camera(scene, keycode));
	if (keycode == FURTHER || keycode == CLOSER)
		return (change_fov(scene, keycode));
	if (keycode == FORWARD || keycode == BACKWARD || keycode == UP
		|| keycode == LEFT || keycode == RIGHT || keycode == DOWN)
		return (change_point_of_camera(scene, keycode));
	if (keycode == 48)
	{
		scene->step_size *= SS_MULTIPLIER;
		if (scene->step_size > SS_MAX)
			scene->step_size = SS_MIN;
		printf("Step Size : %f\n\a", scene->step_size);
	}
	return (keycode);
}

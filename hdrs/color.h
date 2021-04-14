//
// Created by Demeter Xhoan on 3/5/21.
//

#ifndef COLOR_H
# define COLOR_H

typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
}				t_rgb;

t_rgb	create_rgb_norm(float r, float g, float b, float ratio);
t_rgb	rgb_multiply(t_rgb for_multiply, float factor);
t_rgb	rgbs_addition(t_rgb add_here, t_rgb add_this);
int		create_color(t_rgb orig, t_rgb light);
#endif
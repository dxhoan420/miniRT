//
// Created by Demeter Xhoan on 3/5/21.
//

#include "../headers/color.h"

int		r_g_b_to_color(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

int 	rgb_to_color(t_color rgb)
{
	return(rgb.r << 16 | rgb.g << 8 | rgb.b);
}

t_color	color_to_rgb(int color)
{
	t_color rgb;

	rgb.r = color >> 16;
	rgb.g = (color & (0xFF << 8)) >> 8;
	rgb.b = color & 0xFF;
	return (rgb);
}

t_color r_g_b_to_rgb(int r, int g, int b)
{
	t_color rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
}

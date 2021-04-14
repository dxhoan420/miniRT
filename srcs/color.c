//
// Created by Demeter Xhoan on 3/5/21.
//

#include "color.h"

t_rgb	create_rgb_norm(float r, float g, float b, float ratio)
{
	t_rgb	rgb;

	if (ratio > 1)
		ratio = 1;
	rgb.r = ratio / 255 * r;
	if (rgb.r > 1)
		rgb.r = 1;
	rgb.g = ratio / 255 * g;
	if (rgb.g > 1)
		rgb.g = 1;
	rgb.b = ratio / 255 * b;
	if (rgb.b > 1)
		rgb.b = 1;
	return (rgb);
}

t_rgb	rgbs_addition(t_rgb add_here, t_rgb add_this)
{
	add_here.r += add_this.r;
	if (add_here.r > 1)
		add_here.r = 1;
	add_here.g += add_this.g;
	if (add_here.g > 1)
		add_here.g = 1;
	add_here.b += add_this.b;
	if (add_here.b > 1)
		add_here.b = 1;
	return (add_here);
}

t_rgb	rgb_multiply(t_rgb for_multiply, float factor)
{
	for_multiply.r *= factor;
	for_multiply.g *= factor;
	for_multiply.b *= factor;
	return (for_multiply);
}

int	create_color(t_rgb orig, t_rgb light)
{
	orig.r *= light.r;
	orig.g *= light.g;
	orig.b *= light.b;
	return ((int)orig.r << 16 | (int)orig.g << 8 | (int)orig.b);
}

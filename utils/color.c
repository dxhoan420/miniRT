//
// Created by Demeter Xhoan on 3/5/21.
//

#include "../headers/color.h"

t_rgb create_rgb_norm(float r, float g, float b, float ratio)
{
	t_rgb rgb;

	rgb.r = ratio / 255 * r;
	rgb.g = ratio / 255 * g;
	rgb.b = ratio / 255 * b;
	return (rgb);
}

t_rgb create_rgb(float r, float g, float b)
{
	t_rgb rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

t_rgb rgbs_adding(t_rgb add_here, t_rgb add_this)
{
	add_here.r += add_this.r;
	add_here.g += add_this.g;
	add_here.b += add_this.b;
	return (add_here);
}

t_rgb rgb_dividing(t_rgb for_division, float divider)
{
	for_division.r /= divider;
	for_division.g /= divider;
	for_division.b /= divider;
	return (for_division);
}

t_rgb rgb_multiplying(t_rgb for_multiply, float factor)
{
	for_multiply.r *= factor;
	for_multiply.g *= factor;
	for_multiply.b *= factor;
	return (for_multiply);
}
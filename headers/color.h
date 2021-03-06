//
// Created by Demeter Xhoan on 3/5/21.
//

#ifndef MINIRT_COLOR_H
#define MINIRT_COLOR_H
//colors for debugging
#define GREEN	0,255,0
#define BLUE	0,0,255
#define RED		255,0,0
#define WHITE	255,255,255

typedef struct	s_rgb
{
	float r;
	float g;
	float b;
}				t_rgb;

t_rgb			create_rgb_norm(float r, float g, float b, float ratio);
t_rgb			rgb_multiplying(t_rgb for_multiply, float factor);
t_rgb			rgb_dividing(t_rgb for_division, float divider);
t_rgb			rgbs_adding(t_rgb add_here, t_rgb add_this);
t_rgb			create_rgb(float r, float g, float b);
#endif //MINIRT_COLOR_H
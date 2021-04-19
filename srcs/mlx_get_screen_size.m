//
// Created by Demeter Xhoan on 4/19/21.
//

#import <AppKit/NSScreen.h>
#include "../hdrs/miniRT.h"

void    mlx_get_screen_size(int *width, int *height)
{
	NSRect disp = [[NSScreen mainScreen] frame];
	*height = (int)disp.size.height;
	*width = (int)disp.size.width;
}
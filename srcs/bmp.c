//
// Created by Demeter Xhoan on 4/11/21.
//
#include "miniRT.h"
#include <unistd.h>

#define FHEADER 14
#define BMHEADER 40

char	*get_bmp_name_malloc(char *rt)
{
	char	*bmp_filename;
	int		length;

	bmp_filename = rt;
	while (*rt)
	{
		if (*rt == '/' && *(rt + 1) != '\0')
			bmp_filename = ++rt;
		else
			rt++;
	}
	length = 0;
	while (bmp_filename[length++])
		;
	rt -= 3;
	bmp_filename = malloc(++length);
	bmp_filename[--length] = '\0';
	bmp_filename[--length] = 'p';
	bmp_filename[--length] = 'm';
	bmp_filename[--length] = 'b';
	bmp_filename[--length] = '.';
	while (length >= 0)
		bmp_filename[length--] = *rt--;
	return (bmp_filename);
}

void	put_int_to_header(unsigned char *part, int data)
{
	part[0] = (unsigned char)(data);
	part[1] = (unsigned char)(data >> 8);
	part[2] = (unsigned char)(data >> 16);
	part[3] = (unsigned char)(data >> 24);
}

/*
** Info by ska42
**
** FIlE HEADER
** Position | Hex	| Description
** 00		| 00	| TYPE OF BMP FILE
** 02		| 02	| TOTAL SIZE OF FILE
** 06-08	| 06-08	| RESERVED TO SIGN
** 10		| 0A	| HEADER SIZE
** =============================================================================
** BITMAP HEADER
** Position | Hex	| Description
** 14		| 0E	| HEADER INFOS SIZE
** 18		| 12	| WIDTH OF IMG (PX)
** 22		| 16	| HEIGHT OF IMG (PX)
** 26		| 1A	| NUMBER OF PLANS
** 28		| 1C	| BITS PER PIXELS (1 - 4 - 8 - 24)
** 30		| 1E	| COMPRESSION TYPE
** 34		| 22	| SIZE OF IMG
** 38		| 26	| RES X PX PER METER
** 42		| 2A	| RES Y PX PER METER
** 46		| 2E	| NB OF USED COLOR (0 = MAX)
** 50		| 32	| NB OF INDEX OF COLOR (0 = ALL)
*/

void	header_write(int fd, int x_res, int y_res)
{
	int				total;
	unsigned char	header[FHEADER + BMHEADER];

	total = FHEADER + BMHEADER;
	while (total-- > 0)
		header[total] = 0;
	total = (int) sizeof(int) * x_res * y_res + FHEADER + BMHEADER;
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	put_int_to_header(header + 2, total);
	header[10] = (unsigned char)(FHEADER + BMHEADER);
	header[14] = (unsigned char)(BMHEADER);
	put_int_to_header(header + 18, x_res);
	put_int_to_header(header + 22, y_res);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	put_int_to_header(header + 34, x_res * y_res * 4);
	put_int_to_header(header + 38, 300);
	put_int_to_header(header + 42, 300);
	write(fd, header, 54);
}

void	start_bmp_n_exit(char *rt_filename, char *save, t_all scene)
{
	int		fd;
	int		*picture;
	char	*bmp_filename;

	if (save[0] == save[1] && save[1] == '-' && save[2] == 's'
		&& save[3] == 'a' && save[4] == 'v' && save[5] == 'e' && save[6] == '\0')
		printf("\nFlag '--save' is activated for file: %s\n", rt_filename);
	else
		error("WRONG FLAG! Need '--save' for screenshot", save);
	bmp_filename = get_bmp_name_malloc(rt_filename);
	printf("\nRendering result will store in file: %s\n", bmp_filename);
	fd = open(bmp_filename, O_WRONLY | O_TRUNC | O_CREAT, S_IREAD | S_IWRITE);
	if (fd == -1)
		error("Can't open output file", bmp_filename);
	free(bmp_filename);
	picture = malloc(scene.x_res * scene.y_res * 4);
	if (picture == NULL)
		error("Picture memory allocation failed", rt_filename);
	render_scene(scene, picture);
	header_write(fd, scene.x_res, scene.y_res);
	write(fd, picture, scene.x_res * scene.y_res * 4);
	exit(0);
}

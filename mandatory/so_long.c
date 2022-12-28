/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:22:49 by aechaoub          #+#    #+#             */
/*   Updated: 2022/12/28 18:45:22 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../getsky/get_next_line.h"

void	getrslt(void *map, char *av);
char	**ft_split(char const *s, char c);
int		key_hook(int keycode, t_data *vars);
void	key_hook_1(int keycode, t_data *vars);
int		render_next_frame(t_data *img);
void	callimage(t_data *img);

int	destroy(t_data *vars)
{
	int	j;

	j = 0;
	mlx_destroy_window(vars->mlx, vars->win);
	write(1, "closed\n", 7);
	while (j < vars->map.y)
	{
		free(vars->map.map[j]);
		j++;
	}
	free(vars->map.map);
	exit(0);
	return (0);
}

int	render_next_frame(t_data *img)
{
	static int	ds = 1;
	static int	sa = 3;

	if (img->stillplay <= 0)
		return (0);
	if (ds % 1000 == 0)
		callimage(img);
	if (ds++ > 100000)
		ds = 0;
	if (sa++ > 9000)
		sa = 0;
	return (0);
}

void	check_images(t_data *img)
{
	if (!img->lol.pht || !img->gras.pht || !img->door.pht || !img->dollar.pht
		|| !img->small.pht || !img->mywin.pht)
	{
		ft_putstr("error in images \n");
		destroy(img);
	}
	return ;
}

void	initvals(t_data *img)
{
	img->dollar.pht = mlx_xpm_file_to_image(img->mlx,
			"a/frame_0.xpm", &img->dollar.img_width,
			&img->dollar.img_height);
	srand(time(0));
	if (rand() % 2 == 0)
		img->gras.pht = mlx_xpm_file_to_image(img->mlx,
				"a/back_cyan.xpm", &img->gras.img_width, &img->gras.img_height);
	else
		img->gras.pht = mlx_xpm_file_to_image(img->mlx,
				"a/back_gold.xpm", &img->gras.img_width, &img->gras.img_height);
	img->lol.pht = mlx_xpm_file_to_image(img->mlx,
			"a/rock.xpm", &img->lol.img_width, &img->lol.img_height);
	img->mywin.pht = mlx_xpm_file_to_image(img->mlx,
			"a/youwin.xpm", &img->mywin.img_width, &img->mywin.img_height);
	img->small.pht = mlx_xpm_file_to_image(img->mlx,
			"a/small.xpm", &img->small.img_width, &img->small.img_height);
	img->door.pht = mlx_xpm_file_to_image(img->mlx,
			"a/door.xpm", &img->door.img_width, &img->door.img_height);
}

int	main(int ac, char **av)
{
	t_data	img;

	if (ac != 2)
		return (0);
	img.door.many = 0;
	img.gras.many = 0;
	img.small.many = 0;
	img.dollar.many = 0;
	getrslt(&img, av[1]);
	img.mlx = mlx_init();
	initvals(&img);
	img.win = mlx_new_window(img.mlx, (img.map.x) * 50,
			(img.map.y + 1) * 50, "So_Long");
	img.stillplay = 1;
	callimage(&img);
	mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_hook(img.win, 2, 0, key_hook, &img);
	mlx_hook(img.win, 17, 0, destroy, &img);
	mlx_loop(img.mlx);
}

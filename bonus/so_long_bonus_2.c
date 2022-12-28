/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:22:49 by aechaoub          #+#    #+#             */
/*   Updated: 2022/12/25 15:59:29 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../getsky/get_next_line.h"

int	destroy(t_data *vars);

void	callimage_1_puststrs(t_data *img, int i, int j)
{
	char	*k;
	char	*e;

	k = ft_itoa(img->small.many);
	e = ft_strjoin(ft_strdup("Moves : "), k);
	mlx_string_put(img->mlx, img->win, 20, (j + 1) * 50 - 25, 0, e);
	free(e);
	free(k);
	k = ft_itoa(img->dollar.many);
	e = ft_strjoin(ft_strdup("Coins : "), k);
	mlx_string_put(img->mlx, img->win,
		(i - 1) * 50 - 70, (j + 1) * 50 - 25, 0, e);
	free(e);
	free(k);
}

void	callimage_1(t_data *img)
{
	int	i;
	int	j;

	j = 0;
	while (j < img->map.y)
	{
		i = 0;
		while (i < img->map.x)
		{
			if (img->map.map[j][i] == 1)
				mlx_put_image_to_window(img->mlx,
					img->win, img->lol.pht, i * 50, j * 50);
			if (img->map.map[j][i] == 5)
				mlx_put_image_to_window(img->mlx,
					img->win, img->dollar.pht, i * 50, j * 50);
			if (img->map.map[j][i] == 8)
				mlx_put_image_to_window(img->mlx, img->win,
					img->door.pht, i * 50, j * 50);
			if (img->map.map[j][i++] == 3)
				mlx_put_image_to_window(img->mlx, img->win,
					img->enemy.pht, (i - 1) * 50, j * 50);
		}
		j++;
	}
	callimage_1_puststrs(img, i, j);
}

void	callimage_2(t_data *img)
{
	int	j;

	j = 0;
	img->stillplay = -1;
	ft_putstr("you lose\n");
}

void	check_images(t_data *img)
{
	if (!img->lol.pht || !img->gras.pht
		|| !img->door.pht || !img->dollar.pht || !img->small.pht
		|| !img->enemy.pht || !img->mywin.pht)
	{
		ft_putstr("error in images \n");
		destroy(img);
	}
	return ;
}

void	callimage(t_data *img)
{
	static int	frame = 0;

	img->dollar.pht = mlx_xpm_file_to_image(img->mlx,
			img->frame_coins[(frame) % 7], &img->dollar.img_width,
			&img->dollar.img_height);
	img->enemy.pht = mlx_xpm_file_to_image(img->mlx,
			img->frame_enemy[(frame) % 4], &img->enemy.img_width,
			&img->enemy.img_height);
	check_images(img);
	mlx_put_image_to_window(img->mlx, img->win, img->gras.pht, 0, 0);
	callimage_1(img);
	if (img->enemy.xplace == img->small.xplace
		&& img->enemy.yplace == img->small.yplace)
		return (callimage_2(img));
	if (img->stillplay == 0)
		mlx_put_image_to_window(img->mlx, img->win, img->mywin.pht,
			img->map.x * 25 - 150, img->map.y * 25 - 150);
	mlx_put_image_to_window(img->mlx, img->win,
		img->small.pht, img->small.xplace * 50, img->small.yplace * 50);
	frame++;
	if (frame > 28)
		frame = 0;
	mlx_destroy_image(img->mlx, img->dollar.pht);
	mlx_destroy_image(img->mlx, img->enemy.pht);
}

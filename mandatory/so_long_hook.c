/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:22:49 by aechaoub          #+#    #+#             */
/*   Updated: 2022/12/25 15:59:36 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../getsky/get_next_line.h"

void	check_images(t_data *img);
int		destroy(t_data *vars);

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
			i++;
		}
		j++;
	}
	callimage_1_puststrs(img, i, j);
}

void	callimage(t_data *img)
{
	static int	frame = 0;

	check_images(img);
	mlx_put_image_to_window(img->mlx, img->win, img->gras.pht, 0, 0);
	callimage_1(img);
	if (img->stillplay == 0)
		mlx_put_image_to_window(img->mlx, img->win, img->mywin.pht,
			img->map.x * 25 - 150, img->map.y * 25 - 150);
	mlx_put_image_to_window(img->mlx, img->win,
		img->small.pht, img->small.xplace * 50, img->small.yplace * 50);
	frame++;
	if (frame > 28)
		frame = 0;
}

void	key_hook_1(int keycode, t_data *vars)
{
	int	i;

	i = vars->small.yplace;
	if (keycode == 0 && vars->map.map[i][vars->small.xplace - 1] != 1)
		vars->small.xplace -= 1;
	else if (keycode == 1 && vars->map.map[i + 1][vars->small.xplace] != 1)
		vars->small.yplace += 1;
	else if (keycode == 2 && vars->map.map[i][vars->small.xplace + 1] != 1)
		vars->small.xplace += 1;
	else if (keycode == 13 && vars->map.map[i - 1][vars->small.xplace] != 1)
		vars->small.yplace -= 1;
	else
		return ;
	vars->small.many++;
	ft_putnbr(vars->small.many);
	ft_putstr("\n");
}

int	key_hook(int keycode, t_data *vars)
{
	if (keycode == 53)
		destroy(vars);
	if ((keycode == 0 || keycode == 1 || keycode == 2
			|| keycode == 13) && vars->stillplay > 0)
	{
		key_hook_1(keycode, vars);
		if (vars->map.map[vars->small.yplace][vars->small.xplace] == 5)
		{
			vars->dollar.many -= 1;
			vars->map.map[vars->small.yplace][vars->small.xplace] = 0;
		}
		if (vars->map.map[vars->small.yplace][vars->small.xplace] == 8
			&& vars->dollar.many == 0)
		{
			vars->stillplay = 0;
			callimage(vars);
			ft_putstr("youuu win\n");
		}
	}
	return (0);
}

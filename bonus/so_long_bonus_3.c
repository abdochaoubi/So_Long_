/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:22:49 by aechaoub          #+#    #+#             */
/*   Updated: 2022/12/24 16:53:12 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../getsky/get_next_line.h"

void	callimage(t_data *img);
int		destroy(t_data *vars);
void	moveright(t_data *img, int nt);
void	moveleft(t_data *img, int nt);
void	movedown(t_data *img, int nt);
void	moveup(t_data *img, int nt);

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

void	movedown(t_data *img, int nt)
{
	nt++;
	if (nt > 3)
		return ;
	if (img->map.map[img->enemy.yplace + 1][img->enemy.xplace] != 1
		&& img->map.map[img->enemy.yplace + 1][img->enemy.xplace] != 5
		&& img->map.map[img->enemy.yplace + 1][img->enemy.xplace] != 8)
	{
		img->map.map[img->enemy.yplace][img->enemy.xplace] = 0;
		img->map.map[img->enemy.yplace + 1][img->enemy.xplace] = 3;
		img->enemy.yplace++;
	}
	else if (img->enemy.xplace >= img->small.xplace)
	{
		moveleft(img, nt);
		return ;
	}
	else
	{
		moveright(img, nt);
		return ;
	}
}

void	moveup(t_data *img, int nt)
{
	nt++;
	if (nt > 3)
		return ;
	if (img->map.map[img->enemy.yplace - 1][img->enemy.xplace] != 1
		&& img->map.map[img->enemy.yplace - 1][img->enemy.xplace] != 5
		&& img->map.map[img->enemy.yplace - 1][img->enemy.xplace] != 8)
	{
		img->map.map[img->enemy.yplace][img->enemy.xplace] = 0;
		img->map.map[img->enemy.yplace - 1][img->enemy.xplace] = 3;
		img->enemy.yplace--;
	}
	else if (img->enemy.xplace >= img->small.xplace)
	{
		moveleft(img, nt);
		return ;
	}
	else
	{
		moveright(img, nt);
		return ;
	}
}

void	moveleft(t_data *img, int nt)
{
	nt++;
	if (nt > 3)
		return ;
	if (img->map.map[img->enemy.yplace][img->enemy.xplace - 1] != 1
		&& img->map.map[img->enemy.yplace][img->enemy.xplace - 1] != 5
		&& img->map.map[img->enemy.yplace][img->enemy.xplace - 1] != 8)
	{
		img->map.map[img->enemy.yplace][img->enemy.xplace] = 0;
		img->map.map[img->enemy.yplace][img->enemy.xplace - 1] = 3;
		img->enemy.xplace--;
	}
	else if (img->enemy.yplace <= img->small.yplace)
	{
		movedown(img, nt);
		return ;
	}
	else
	{
		moveup(img, nt);
		return ;
	}
}

void	moveright(t_data *img, int nt)
{
	nt++;
	if (nt > 3)
		return ;
	if (img->map.map[img->enemy.yplace][img->enemy.xplace + 1] != 1
		&& img->map.map[img->enemy.yplace][img->enemy.xplace + 1] != 5
		&& img->map.map[img->enemy.yplace][img->enemy.xplace + 1] != 8)
	{
		img->map.map[img->enemy.yplace][img->enemy.xplace] = 0;
		img->map.map[img->enemy.yplace][img->enemy.xplace + 1] = 3;
		img->enemy.xplace++;
	}
	else if (img->enemy.yplace <= img->small.yplace)
	{
		movedown(img, nt);
		return ;
	}
	else
	{
		moveup(img, nt);
		return ;
	}
}

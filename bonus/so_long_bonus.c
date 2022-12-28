/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:22:49 by aechaoub          #+#    #+#             */
/*   Updated: 2022/12/28 19:24:05 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../getsky/get_next_line.h"
int hardness=10;

void	getrslt(void *map, char *av);
char	**ft_split(char const *s, char c);
void	callimage(t_data *img);
void	callimage_1_puststrs(t_data *img, int i, int j);
void	callimage_1(t_data *img);
void	callimage_2(t_data *img);
void	check_images(t_data *img);
void	key_hook_1(int keycode, t_data *vars);
void	moveright(t_data *img, int nt);
void	moveleft(t_data *img, int nt);
void	movedown(t_data *img, int nt);
void	moveup(t_data *img, int nt);
int		destroy(t_data *vars);

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

void	changee_enemy(t_data *img)
{
	int	i;

	i = abs(img->enemy.xplace - img->small.xplace);
	if (i > abs(img->enemy.yplace - img->small.yplace))
	{
		if (img->enemy.xplace >= img->small.xplace)
			moveleft(img, 0);
		else
			moveright(img, 0);
		return ;
	}
	if (img->enemy.yplace <= img->small.yplace)
	{
		movedown(img, 0);
		return ;
	}
	else
	{
		moveup(img, 0);
		return ;
	}
}

int	render_next_frame(t_data *img)
{
	static int	ds = 1;
	static int	sa = 3;

	if (img->stillplay <= 0)
		return (0);
	if (img->enemy.xplace > 0 && sa % (2600-(hardness*70)) == 0)
		changee_enemy(img);
	if (ds % 1000 == 0)
		callimage(img);
	if (ds++ > 100000)
		ds = 0;
	if (sa++ > 9000)
		sa = 0;
	return (0);
}

void	initvals(t_data *img)
{
	char	*str;

	str = ft_strjoin(ft_strdup("a/enemy_3.xpm|a/enemy_4.xpm|"),
			"a/enemy_5.xpm|a/enemy_6.xpm");
	img->frame_enemy = ft_split(str, '|');
	free(str);
	str = ft_strjoin(ft_strdup("a/frame_0.xpm|a/frame_1.xpm|a/frame_2.xpm|"),
			"a/frame_3.xpm|a/frame_4.xpm|a/frame_5.xpm|a/frame_6.xpm");
	img->frame_coins = ft_split(str, '|');
	free(str);
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

	if (ac != 3 && ac!=2)
		return (0);
	img.enemy.many = 0;
	img.door.many = 0;
	img.gras.many = 0;
	img.enemy.xplace = -1;
	img.small.many = 0;
	img.dollar.many = 0;
	if(ac==3)
		if(ft_atoi(av[2])>0 && ft_atoi(av[2])<31)
			hardness=ft_atoi(av[2]);
	getrslt(&img, av[1]);
	img.mlx = mlx_init();
	initvals(&img);
	img.win = mlx_new_window(img.mlx, (img.map.x) * 50,
			(img.map.y + 1) * 50, "So_Long_Bonus");
	img.stillplay = 1;
	callimage(&img);
	mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_hook(img.win, 2, 0, key_hook, &img);
	mlx_hook(img.win, 17, 0, destroy, &img);
	mlx_loop(img.mlx);
}

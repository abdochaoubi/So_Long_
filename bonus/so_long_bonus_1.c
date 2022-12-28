/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:22:49 by aechaoub          #+#    #+#             */
/*   Updated: 2022/12/24 16:54:28 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../getsky/get_next_line.h"

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
	j = 0;
	while (vars->frame_enemy[j])
	{
		free(vars->frame_enemy[j]);
		j++;
	}
	j = 0;
	while (vars->frame_coins[j])
		free(vars->frame_coins[j++]);
	free(vars->frame_enemy);
	free(vars->frame_coins);
	free(vars->map.map);
	exit(0);
	return (0);
}

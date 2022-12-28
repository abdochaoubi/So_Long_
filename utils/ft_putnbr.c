/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:44:05 by aechaoub          #+#    #+#             */
/*   Updated: 2022/12/23 19:30:12 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_pow1(int n)
{
	int	i;

	i = 1;
	while (n / 10)
	{
		i *= 10;
		n /= 10;
	}
	return (i);
}

void	ft_putnbr(int n)
{
	int				nlen;
	char			i;
	unsigned int	un;

	if (n < 0)
	{
		write(1, "-", 1);
		un = n * -1;
	}
	else
		un = n;
	nlen = ft_pow1(un);
	while (nlen)
	{
		i = un / (nlen) + '0';
		write(1, &i, 1);
		un = un - (un / (nlen)) * nlen;
		nlen /= 10;
	}
}

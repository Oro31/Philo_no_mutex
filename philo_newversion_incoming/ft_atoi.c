/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:32:35 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/05 13:40:24 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_pwr(int nb, size_t p)
{
	int	res;

	if (p == 0)
		return (1);
	if (p == 1)
		return (nb);
	res = nb;
	while (p > 1)
	{
		res = res * nb;
		p--;
	}
	return (res);
}

static int	ft_calc_res(const char *nptr, int i, int sign, int mark)
{
	int	r;
	int	len;

	len = i;
	r = 0;
	if (sign == -1)
	{
		while (i > mark)
		{
			i--;
			r = r - ((nptr[i] - 48) * ft_pwr(10, len - 1 - i));
		}
	}
	else
	{
		while (i > mark)
		{
			i--;
			r = r + ((nptr[i] - 48) * ft_pwr(10, len - 1 - i));
		}
	}
	return (r);
}

static int	ft_wi(const char *nptr, int i, int sign, int mark)
{
	int	res;

	if (i - mark > 10)
		return (0);
	res = ft_calc_res(nptr, i, sign, mark);
	if ((res < 0 && sign == 1) || (res > 0 && sign == -1))
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	mark;

	sign = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * (-1);
		i++;
	}
	mark = i;
	while (*(nptr + i) && nptr[i] >= '0' && nptr[i] <= '9')
		i++;
	return (ft_wi(nptr, i, sign, mark) * ft_calc_res(nptr, i, sign, mark));
}

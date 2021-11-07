/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:05:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/07 18:00:05 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_eat(t_vars *vars, int i)
{
	long			print;
	int				ret;

	ret = (i + 1) % vars->nb_philos;
	if (vars->forks[i].use == 0 && vars->forks[ret].use == 0)
	{
		vars->forks[i].use = 1;
		vars->forks[ret].use = 1;
		ret = gettimeofday(&vars->philos[i].last_meal, NULL);
		print = ft_timediff(vars->initial_tmstmp, vars->philos[i].last_meal);
		printf("%ld %d has taken a fork\n", print, (i + 1));
		printf("%ld %d has taken a fork\n", print, (i + 1));
		vars->philos[i].thi = 0;
		vars->philos[i].eat = 1;
	}
}

void	ft_sleep(t_vars *vars, int i)
{
	int				ret;

	ret = (i + 1) % vars->nb_philos;
	vars->forks[i].use = 0;
	vars->forks[ret].use = 0;
	ret = gettimeofday(&vars->philos[i].start_sleep, NULL);
	vars->philos[i].feat = 0;
	vars->philos[i].sle = 1;
}

void	ft_check_for_dead(t_vars *vars, int i)
{
	struct timeval	t;
	long			lm;
	long			at;
	int				ret;

	lm = (vars->philos[i].last_meal.tv_sec * 1000000)
		+ vars->philos[i].last_meal.tv_usec;
	ret = gettimeofday(&t, NULL);
	at = (t.tv_sec * 1000000) + t.tv_usec;
	if (at >= lm + vars->ttd)
	{
		ft_eat(vars, i);
		lm = (vars->philos[i].last_meal.tv_sec * 1000000)
			+ vars->philos[i].last_meal.tv_usec;
		if (at >= lm + vars->ttd)
		{
			printf("%ld %d died\n", ft_timediff(vars->initial_tmstmp, t),
					(i + 1));
			vars->philos[i].alive = 0;
			vars->play = 0;
		}
	}
}

void	ft_check_if_satiated(t_vars *vars)
{
	int	i;
	int	c;

	c = 0;
	i = -1;
	while (++i < vars->nb_philos)
	{
		if (vars->philos[i].nb_eat >= vars->nb_must_eat)
			c++;
	}
	if (c == vars->nb_philos)
		vars->play = 0;
}

void	*thread_monitoring(void *p_data)
{
	t_vars			*vars;
	int				i;

	vars = (t_vars *)p_data;
	i = gettimeofday(&vars->initial_tmstmp, NULL);
	ft_init_philos(vars, vars->nb_arg);
	while (vars->play)
	{
		i = -1;
		while (++i < vars->nb_philos && vars->play)
		{
			if (vars->philos[i].thi)
				ft_eat(vars, i);
			if (vars->philos[i].feat)
				ft_sleep(vars, i);
			ft_check_for_dead(vars, i);
		}
		if (vars->nb_arg == 6)
			ft_check_if_satiated(vars);
	}
	i = -1;
	while (++i < vars->nb_philos)
		vars->philos[i].alive = 0;
	return (NULL);
}

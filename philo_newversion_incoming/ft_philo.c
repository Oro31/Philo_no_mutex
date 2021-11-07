/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:38:50 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/07 18:01:09 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_wait(struct timeval start, int ttw)
{
	struct timeval	t;
	int				ret;

	ret = gettimeofday(&t, NULL);
/*	while ((t.tv_sec * 1000000) + t.tv_usec < (start.tv_sec * 1000000)
		+ start.tv_usec + ttw)
*/	while (ft_timediff(start, t) < ttw / 1000)
		ret = gettimeofday(&t, NULL);
}

void	ft_philo_eating(t_philo *philo)
{
	if (philo->alive)
	{
		printf("%ld %d is eating\n", ft_timediff(philo->i_tt, philo->last_meal)
			, (philo->id + 1));
		ft_wait(philo->last_meal, philo->tte);
		philo->eat = 0;
		philo->nb_eat++;
		philo->feat = 1;
	}
}

void	ft_philo_sleeping(t_philo *philo)
{
	if (philo->alive)
	{
		printf("%ld %d is sleeping\n", ft_timediff(philo->i_tt,
				philo->start_sleep), (philo->id + 1));
		ft_wait(philo->start_sleep, philo->tts);
		philo->sle = 0;
		philo->ret = gettimeofday(&philo->t, NULL);
		printf("%ld %d is thinking\n", ft_timediff(philo->i_tt, philo->t),
			(philo->id + 1));
		philo->thi = 1;
	}
}

void	*thread_philo(void *p_data)
{
	t_philo			*philo;

	philo = (t_philo *)p_data;
	while (philo->alive)
	{
		if (philo->eat == 1 && philo->alive)
			ft_philo_eating(philo);
		else if (philo->sle == 1 && philo->alive)
			ft_philo_sleeping(philo);
	}
	return (NULL);
}

void	ft_init_philos(t_vars *vars, int argc)
{
	int	i;

	i = -1;
	while (++i < vars->nb_philos)
	{
		if (argc == 6)
			vars->philos[i].nb_eat = 0;
		else
			vars->philos[i].nb_eat = -2147483647;
		vars->forks[i].use = 0;
		vars->philos[i].id = i;
		vars->philos[i].i_tt = vars->initial_tmstmp;
		vars->philos[i].ret = gettimeofday(&vars->philos[i].last_meal, NULL);
		printf("%ld %d is thinking\n", ft_timediff(vars->initial_tmstmp,
				vars->philos[i].last_meal), (i + 1));
		vars->philos[i].thi = 1;
	}
}

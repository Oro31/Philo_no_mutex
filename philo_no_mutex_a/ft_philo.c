/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:38:50 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/03 12:33:56 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	ft_eat(t_vars *vars, int i)
{
	struct timeval	t;
	int				ret;

	ret = 0;
	if (vars->forks[i].use == 0 &&
			vars->forks[(i + 1) % vars->nb_philos].use == 0)
	{
		vars->forks[i].use = 1;
		vars->forks[(i + 1) % vars->nb_philos].use = 1;
		vars->philos[i].eat = 0;
		vars->philos[i].fsle = 0;
		vars->philos[i].thi = 0;
		ret = gettimeofday(&t, NULL);
		printf("%ld %d has taken a fork\n", (t.tv_sec * 1000000) + t.tv_usec, i);
		printf("%ld %d is eating\n", (t.tv_sec * 1000000) + t.tv_usec, i);
		vars->philos[i].feat = 1;
	}
}

static void	ft_sleep(t_vars *vars, int i)
{
	struct timeval	t;
	int				ret;

	vars->forks[i].use = 0;
	vars->forks[(i + 1) % vars->nb_philos].use = 0;
	vars->philos[i].feat = 0;
	vars->philos[i].sle = 0;
	ret = gettimeofday(&t, NULL);
	printf("%ld %d is sleeping\n", (t.tv_sec * 1000000) + t.tv_usec, i);
	vars->philos[i].fsle = 1;
}

static void	ft_check_for_dead(t_vars *vars, int i)
{
	int	ret;

	ret = gettimeofday(&vars->philos[i].t, NULL);
	if (vars->philos[i].feat == 0)
	{
		if ((vars->philos[i].t.tv_sec * 1000000) + vars->philos[i].t.tv_usec >=
				(vars->philos[i].last_meal.tv_sec * 1000000) +
				vars->philos[i].last_meal.tv_usec + vars->ttd)
		{
			printf("%ld %d died\n", (vars->philos[i].t.tv_sec * 1000000) +
					vars->philos[i].t.tv_usec, i);
			vars->philos[i].alive = 0;
			vars->play = 0;
		}
	}
}

static void	*fn_all(void *p_data)
{
	t_vars	*vars;
	int		i;

	vars = (t_vars *)p_data;
	while (vars->play)
	{
		i = -1;
		while (++i < vars->nb_philos && vars->play)
		{
			if (vars->philos[i].eat && vars->philos[i].thi)
				ft_eat(vars, i);
			else if (vars->philos[i].sle && vars->philos[i].feat)
				ft_sleep(vars, i);
			ft_check_for_dead(vars, i);
		}
	}
	i = -1;
	while (++i < vars->nb_philos)
		vars->philos[i].alive = 0;
}

static void	ft_wait(int ttw)
{
	struct timeval	start;
	struct timeval	t;
	int				ret;

	ret = gettimeofday(&start, NULL);
	ret = gettimeofday(&t, NULL);
	while ((t.tv_sec * 1000000) + t.tv_usec <
			(start.tv_sec * 1000000) + start.tv_usec + ttw)
		ret = gettimeofday(&t, NULL);
}

static void	*fn_philo(void *p_data)
{
	t_philo	*philo;

	philo = (t_philo *)p_data;
	while (philo->alive)
	{
		if (philo->thi == 1)
			philo->eat = 1;
		else if (philo->feat == 1)
		{
			ft_wait(philo->tte);
			philo->ret = gettimeofday(&philo->last_meal, NULL);
			philo->sle = 1;
		}
		else if (philo->fsle == 1)
		{
			ft_wait(philo->tts);
			philo->ret = gettimeofday(&philo->t, NULL);
			printf("%ld %d is thinking\n", (philo->t.tv_sec * 1000000) +
					philo->t.tv_usec, philo->id);
			philo->fsle = 0;
			philo->thi = 1;
		}
	}
}

static void	ft_init(t_vars *vars, char **argv, int argc)
{
	int	i;

	vars->play = 1;
	vars->nb_philos = atoi(argv[1]);
	vars->ttd = atoi(argv[2]);
	vars->tte = atoi(argv[3]);
	vars->tts = atoi(argv[4]);
	if (argc == 6)
		vars->nb_must_eat = atoi(argv[5]);
	vars->philos = malloc(sizeof(t_philo) * vars->nb_philos);
	vars->forks = malloc(sizeof(t_fork) * vars->nb_philos);
	i = -1;
	while (++i < vars->nb_philos)
	{
		vars->forks[i].use = 0;
		vars->philos[i].id = i;
		vars->philos[i].alive = 1;
		vars->philos[i].thi = 1;
		vars->philos[i].fsle = 1;
		vars->philos[i].tte = vars->tte;
		vars->philos[i].tts = vars->tts;
		vars->philos[i].ret = gettimeofday(&vars->philos[i].last_meal, NULL);
		printf("%ld %d is thinking\n", (vars->philos[i].last_meal.tv_sec *
					1000000) + vars->philos[i].last_meal.tv_usec, i);
	}
}

int	main(int argc, char **argv)
{
	t_vars	all;
	int		i;
	int		ret;

	if (argc < 5)
		return (0);
	ft_init(&all, argv, argc);
	ret = pthread_create(&all.th_all, NULL, fn_all, &all);
	if (!ret)
	{
		i = -1;
		while (++i < all.nb_philos)
			ret = pthread_create(&all.philos[i].th_philo, NULL, fn_philo,
					&all.philos[i]);
	}
	i = -1;
	while (++i < all.nb_philos)
		pthread_join(all.philos[i].th_philo, NULL);
	pthread_join(all.th_all, NULL);
	return (0);
}

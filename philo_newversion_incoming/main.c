/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:33:38 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/07 17:18:53 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_exit(t_vars *vars, int code)
{
	if (code == 0)
		return (0);
	free(vars->philos);
	free(vars->forks);
	if (code == 1)
		printf("Error : failed creating thread\n");
	else if (code == 2)
		printf("Error : failed joining thread\n");
	return (0);
}

static int	ft_create_thread(t_vars *vars)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < vars->nb_philos)
	{
		vars->philos[i].thi = 0;
		vars->philos[i].eat = 0;
		vars->philos[i].feat = 0;
		vars->philos[i].sle = 0;
		vars->philos[i].fsle = 0;
		vars->philos[i].alive = 1;
		vars->philos[i].tte = vars->tte;
		vars->philos[i].tts = vars->tts;
		vars->philos[i].ttd = vars->ttd;
		ret = pthread_create(&vars->philos[i].th_philo, NULL, thread_philo,
				&vars->philos[i]);
		if (ret != 0)
			return (1);
	}
	return (0);
}

static void	ft_init(t_vars *vars, char **argv, int argc)
{
	vars->nb_arg = argc;
	vars->play = 1;
	vars->nb_philos = ft_atoi(argv[1]);
	vars->ttd = ft_atoi(argv[2]) * 1000;
	vars->tte = ft_atoi(argv[3]) * 1000;
	vars->tts = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		vars->nb_must_eat = atoi(argv[5]);
	else
		vars->nb_must_eat = 2147483647;
	vars->philos = malloc(sizeof(t_philo) * vars->nb_philos);
	vars->forks = malloc(sizeof(t_fork) * vars->nb_philos);
}

int	main(int argc, char **argv)
{
	t_vars	all;
	int		i;
	int		ret;

	if (argc < 5)
		return (0);
	ft_init(&all, argv, argc);
/*	if (ret != 0)
		return (ft_exit(&all, 1));
*/	if (ft_create_thread(&all))
		return (ft_exit(&all, 1));
	ret = pthread_create(&all.th_all, NULL, thread_monitoring, &all);
	i = -1;
	while (++i < all.nb_philos)
	{
		ret = pthread_join(all.philos[i].th_philo, NULL);
		if (ret != 0)
			return (ft_exit(&all, 2));
	}
	ret = pthread_join(all.th_all, NULL);
	if (ret != 0)
		return (ft_exit(&all, 2));
	return (ft_exit(&all, 3));
}

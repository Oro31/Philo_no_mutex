/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:55:32 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/07 17:56:40 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo {
	pthread_t		th_philo;
	struct timeval	i_tt;
	struct timeval	last_meal;
	struct timeval	start_sleep;
	struct timeval	t;
	int				nb_eat;
	int				tte;
	int				tts;
	int				ttd;
	int				alive;
	int				eat;
	int				feat;
	int				thi;
	int				sle;
	int				fsle;
	int				id;
	int				ret;
}				t_philo;

typedef struct s_fork {
	pthread_mutex_t	mutex;
	int				id;
	int				use;
}				t_fork;

typedef struct s_vars {
	t_philo			*philos;
	t_fork			*forks;
	pthread_t		th_all;
	pthread_mutex_t	mutex;
	struct timeval	initial_tmstmp;
	int				nb_arg;
	int				play;
	int				set;
	int				id_philo;
	int				nb_philos;
	int				ttd;
	int				tte;
	int				tts;
	int				nb_must_eat;
}				t_vars;

int		ft_atoi(const char *nptr);

long	ft_timediff(struct timeval t0, struct timeval t1);

void	ft_eat(t_vars *vars, int i);
void	ft_sleep(t_vars *vars, int i);
void	ft_check_for_dead(t_vars *vars, int i);
void	ft_check_if_satiated(t_vars *vars);
void	*thread_monitoring(void *p_data);

void	ft_wait(struct timeval start, int ttw);
void	ft_philo_eating(t_philo *philo);
void	ft_philo_sleeping(t_philo *philo);
void	*thread_philo(void *p_data);
void	ft_init_philos(t_vars *vars, int argc);

#endif

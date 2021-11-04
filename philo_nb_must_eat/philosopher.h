/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:55:32 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/04 11:58:08 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_philo {
	pthread_t		th_philo;
	struct timeval	last_meal;
	struct timeval	start;
	struct timeval	t;
	int				nb_eat;
	int				tte;
	int				tts;
	int				alive;
	int				eat;
	int				feat;
	int				thi;
	int				sle;
	int				fsle;
	int				id;
	int				ret;
}				t_philo;

typedef struct	s_fork {
	pthread_mutex_t	mutex;
	int				id;
	int				use;
}				t_fork;

typedef struct	s_vars {
	t_philo			*philos;
	t_fork			*forks;
	pthread_t		th_all;
	pthread_mutex_t	mutex;
	int				play;
	int				set;
	int				id_philo;
	int				nb_philos;
	int				ttd;
	int				tte;
	int				tts;
	int				nb_must_eat;
}				t_vars;

#endif

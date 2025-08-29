/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 07:12:38 by nando             #+#    #+#             */
/*   Updated: 2025/08/29 12:45:51 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_limit;
	int				*eat_count;
	pthread_mutex_t	*forks;
	long			*last_meal_times;
	int				*stop_flag;
	long			start_time;
	pthread_mutex_t	*state_mtx;
}					t_philo;

typedef struct s_ctx
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	long			*last_meal;
	long			start_time;
	int				*eat_count;
	int				stop_flag;
	int				is_failed;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_limit;
	pthread_mutex_t	*state_mtx;
}					t_ctx;

int					ft_atoi(const char *nptr);
long				now_ms(void);
int					is_running(t_philo *p);
void				log_death(int id, t_philo *p, long detect_ts);
void				log_actions(int id, char *msg, t_philo *philo);
void				monitoring(t_philo *p);
void				*philosopher(void *arg);
int					create_thread(t_philo *p, pthread_t *threads, int *created);
void				cleaning(t_philo *philo, pthread_t *threads,
						pthread_mutex_t *forks);
void				cleaning_create_error_case(t_philo *philo,
						pthread_t *threads, pthread_mutex_t *forks,
						int create_count);

#endif
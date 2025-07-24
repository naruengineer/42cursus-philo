/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 07:12:38 by nando             #+#    #+#             */
/*   Updated: 2025/07/24 14:13:21 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_limit;
	int				time_to_die;
	int				*eat_count;
	pthread_mutex_t	*forks;
	long			*last_meal_times;
	int				*stop_flag;
}					t_philo;

int					ft_atoi(const char *nptr);
long				now_ms(void);
void				log_death(int id);
void				log_actions(int id, char *log);
void				monitoring(t_philo *p);
void				*philosopher(void *arg);
void				cleaning(t_philo *philo, pthread_t *threads,
						pthread_mutex_t *forks);

#endif

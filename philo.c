/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 07:12:12 by nando             #+#    #+#             */
/*   Updated: 2025/07/24 14:01:33 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo	*p;
	int		left;
	int		right;

	p = (t_philo *)arg;
	left = p->id;
	right = (p->id + 1) % p->philo_count;
	while (*(p->stop_flag))
	{
		// forks lock
		if (p->id % 2 == 0)
		{
			pthread_mutex_lock(&p->forks[left]);
			log_actions(p->id, "has taken a fork");
			pthread_mutex_lock(&p->forks[right]);
			log_actions(p->id, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&p->forks[right]);
			log_actions(p->id, "has taken a fork");
			pthread_mutex_lock(&p->forks[left]);
			log_actions(p->id, "has taken a fork");
		}
		// eating
		log_actions(p->id, "is eating");
		p->last_meal_times[p->id] = now_ms();
		p->eat_count[p->id]++;
		usleep(p->time_to_eat * 1000);
		// forks unlock
		pthread_mutex_unlock(&p->forks[left]);
		pthread_mutex_unlock(&p->forks[right]);
		// sleeping
		log_actions(p->id, "is sleeping");
		usleep(p->time_to_sleep * 1000);
		// thinking
		log_actions(p->id, "is thinking");
	}
	return (NULL);
}

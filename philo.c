/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 07:12:12 by nando             #+#    #+#             */
/*   Updated: 2025/07/30 19:20:16 by nando            ###   ########.fr       */
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
	if (p->id % 2 == 1)
		usleep(p->time_to_eat * 1000 / 2);
	while (*(p->stop_flag))
	{
		// forks lock
		if (p->id % 2 == 0)
		{
			pthread_mutex_lock(&p->forks[left]);
			log_actions(p->id, "has taken a fork", p);
			pthread_mutex_lock(&p->forks[right]);
			log_actions(p->id, "has taken a fork", p);
		}
		else
		{
			pthread_mutex_lock(&p->forks[right]);
			log_actions(p->id, "has taken a fork", p);
			pthread_mutex_lock(&p->forks[left]);
			log_actions(p->id, "has taken a fork", p);
		}
		// eating
		log_actions(p->id, "is eating", p);
		p->last_meal_times[p->id] = now_ms();
		p->eat_count[p->id]++;
		usleep(p->time_to_eat * 1000);
		// forks unlock
		pthread_mutex_unlock(&p->forks[left]);
		pthread_mutex_unlock(&p->forks[right]);
		// sleeping
		log_actions(p->id, "is sleeping", p);
		usleep(p->time_to_sleep * 1000);
		// thinking
		log_actions(p->id, "is thinking", p);
		if (p->id % 2 == 1)
			usleep(p->time_to_eat * 1000 / 2);
	}
	//printf("philo %d exit\n", p->id);
	return (NULL);
}

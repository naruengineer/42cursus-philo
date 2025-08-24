/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 07:12:12 by nando             #+#    #+#             */
/*   Updated: 2025/08/24 16:28:32 by nando            ###   ########.fr       */
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
	if (p->philo_count == 1)
	{
		log_actions(p->id, "is thinking", p);
		pthread_mutex_lock(&p->forks[left]);
		log_actions(p->id, "has taken a fork", p);
		while (*(p->stop_flag))
			usleep(1000);
		pthread_mutex_unlock(&p->forks[left]);
		return (NULL);
	}
	while (*(p->stop_flag))
	{
		// thinking
		log_actions(p->id, "is thinking", p);
		usleep(100);
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
			usleep(500);
			pthread_mutex_lock(&p->forks[right]);
			log_actions(p->id, "has taken a fork", p);
			pthread_mutex_lock(&p->forks[left]);
			log_actions(p->id, "has taken a fork", p);
		}
		// eating
		log_actions(p->id, "is eating", p);
		p->last_meal_times[p->id] = now_ms();
		usleep(p->time_to_eat * 1000);
		p->eat_count[p->id]++;
		// forks unlock
		pthread_mutex_unlock(&p->forks[left]);
		pthread_mutex_unlock(&p->forks[right]);
		// sleeping
		log_actions(p->id, "is sleeping", p);
		usleep(p->time_to_sleep * 1000);
	}
	return (NULL);
}
